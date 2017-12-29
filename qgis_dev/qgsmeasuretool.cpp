#include "qgsmeasuretool.h"


QgsMeasureTool::QgsMeasureTool(QgsMapCanvas* canvas)
	: QgsMapTool(canvas)
	, mDialog(nullptr)
	, mRubberBand(nullptr)
	, mRubberBandPoints(nullptr)
{
	mRubberBand = new QgsRubberBand(canvas, QGis::Line);
	mRubberBandPoints = new QgsRubberBand(canvas, QGis::Point);

	QPixmap myCrossHairQPixmap = QPixmap(( const char ** ) cross_hair_cursor );
	mCursor = QCursor( myCrossHairQPixmap, 8, 8 );

	mDone = true;	// 设置为完成则下次按键重新开始

	// 将点添加到列表里
	mPoints.append(QgsPoint(0, 0));

	mDialog = new QgsMeasureDialog(this);
	mDialog->setWindowFlags(mDialog->windowFlags() | Qt::Tool);
}

QgsMeasureTool::~QgsMeasureTool()
{
	delete mDialog;
	delete mRubberBand;
	delete mRubberBandPoints;
}

void QgsMeasureTool::activate()
{
	mDialog->show();
	QgsMapTool::activate();

	// ensure that we have correct settings
	updateSettings();

	// If we suspect that they have data that is projected, yet the
	// map CRS is set to a geographic one, warn them.
	if ( mCanvas->mapSettings().destinationCrs().geographicFlag() &&
		( mCanvas->extent().height() > 360 ||
		mCanvas->extent().width() > 720 ) )
	{
		QMessageBox::warning( nullptr, tr( "Incorrect measure results" ),
			tr( "<p>This map is defined with a geographic coordinate system "
			"(latitude/longitude) "
			"but the map extents suggests that it is actually a projected "
			"coordinate system (e.g., Mercator). "
			"If so, the results from line or area measurements will be "
			"incorrect.</p>"
			"<p>To fix this, explicitly set an appropriate map coordinate "
			"system using the <tt>Settings:Project Properties</tt> menu." ) );
	}
}

void QgsMeasureTool::deactivate()
{
	mDialog->hide();
	QgsMapTool::deactivate();
}

void QgsMeasureTool::restart()
{
	mPoints.clear();

	mRubberBand->reset(QGis::Line);
	mRubberBandPoints->reset(QGis::Point);

	mDone = true;
}

void QgsMeasureTool::updateSettings()
{
	// 设置点线颜色
	int myRed = 222, myGreen = 155, myBlue = 67;
	mRubberBand->setColor(QColor(myRed, myGreen, myBlue, 100));
	mRubberBand->setWidth(3);
	mRubberBandPoints->setIcon( QgsRubberBand::ICON_CIRCLE );
	mRubberBandPoints->setIconSize( 10 );
	mRubberBandPoints->setColor( QColor( myRed, myGreen, myBlue, 150 ) );
}

void QgsMeasureTool::canvasPressEvent( QgsMapMouseEvent* e )
{
	Q_UNUSED( e );
}

void QgsMeasureTool::canvasMoveEvent( QgsMapMouseEvent* e )
{
	if ( ! mDone )
	{
		QgsPoint point = snapPoint( e->pos() );

		mRubberBand->movePoint( point );
		mDialog->mouseMove( point );
	}
	Q_UNUSED(e);
}


void QgsMeasureTool::canvasReleaseEvent( QgsMapMouseEvent* e )
{
	QgsPoint point = snapPoint( e->pos() );

	if ( mDone ) // 如果完成测量则重新开始测量
	{
		mDialog->restart();
	}

	if ( e->button() == Qt::RightButton ) // 点击右键停止测量
	{
		mDone = true;
	}
	else if ( e->button() == Qt::LeftButton )
	{
		mDone = false;
	}

	// 将点击的点显示在canvas中
	addPoint( point );
	mDialog->show();

}

void QgsMeasureTool::undo()
{
	if ( mRubberBand )
	{
		if ( mPoints.size() < 1 )
		{
			return;
		}

		if ( mPoints.size() == 1 )
		{
			// 如果只有一个则移除后重新开始
			restart();
			mDialog->restart();
		}
		else
		{
			// 否则移除倒数第二个点以及最后一条线
			mRubberBand->removePoint( -2, true );
			mRubberBandPoints->removePoint( -1, true );
			mPoints.removeLast();

			mDialog->removeLastPoint();
		}

	}
}

void QgsMeasureTool::keyPressEvent( QKeyEvent* e )
{
	if (( e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Delete ) )
	{
		if ( !mDone )
		{
			undo();
		}

		e->ignore();
	}
}


void QgsMeasureTool::addPoint( const QgsPoint &point )
{
	// 不加入重复点
	if ( !mPoints.isEmpty() && mPoints.last() == point )
	{
		return;
	}

	QgsPoint pnt( point );
	mPoints.append( pnt );

	mRubberBand->addPoint( point );
	mRubberBandPoints->addPoint( point );
	if ( ! mDone )    // 通知提示框有点被添加
	{
		mDialog->addPoint( point );
	}
}


QgsPoint QgsMeasureTool::snapPoint( const QPoint& p )
{
	QgsPointLocator::Match m = mCanvas->snappingUtils()->snapToMap( p );
	return m.isValid() ? m.point() : mCanvas->getCoordinateTransform()->toMapCoordinates( p );
}


