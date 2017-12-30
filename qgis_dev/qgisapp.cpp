#include "qgisapp.h"
#include <stdio.h>

QgisApp::QgisApp(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),
	  mMapCanvas(nullptr),
	  mLayerTreeCanvasBridge(nullptr),
	  mPan(nullptr),
	  mZoomIn(nullptr),
	  mZoomOut(nullptr),
	  mPopMenu(nullptr),
	  mIdentify(nullptr),
	  mMeasure(nullptr)
{
	ui.setupUi(this);
	init();
}

QgisApp::~QgisApp()
{
	mMapCanvas->stopRendering();
	closeProject();

	delete mPan;
	delete mZoomIn;
	delete mZoomOut;
	delete mMeasure;
	delete mIdentify;
	delete mMapCanvas;
	delete mPopMenu;
	delete mLayerTreeCanvasBridge;

	QgsApplication::exitQgis();
	delete QgsProject::instance();
}

void QgisApp::init()
{
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));	// �������ı���

	QWidget *centralWidget = this->centralWidget();
	QGridLayout *centralLayout = new QGridLayout( centralWidget );
	centralWidget->setLayout( centralLayout );
	centralLayout->setContentsMargins( 0, 0, 0, 0 );

	mMapCanvas = new QgsMapCanvas( centralWidget, "theMapCanvas" );
	mMapCanvas->enableAntiAliasing(true);	// ���������
	mMapCanvas->setVisible(true);
	mMapCanvas->setCanvasColor(QColor(220, 255, 255));
	centralLayout->addWidget(mMapCanvas, 0, 0, 1, 1);

	mLayerTreeCanvasBridge = new QgsLayerTreeMapCanvasBridge(
		QgsProject::instance()->layerTreeRoot(), mMapCanvas, this);
	mLayerTreeCanvasBridge->setAutoEnableCrsTransform(true);
	connect(QgsProject::instance(), SIGNAL(writeProject(QDomDocument&)), mLayerTreeCanvasBridge, SLOT(writeProject(QDomDocument&)));
	connect(QgsProject::instance(), SIGNAL(readProject(QDomDocument)), mLayerTreeCanvasBridge, SLOT(readProject(QDomDocument)));

	// ��ʼ��������ͼ����
	mPan = new QgsMapToolPan(mMapCanvas);
	mZoomOut = new QgsMapToolZoom(mMapCanvas, true);
	mZoomIn = new QgsMapToolZoom(mMapCanvas, false);
	mMeasure = new QgsMeasureTool(mMapCanvas);
	mIdentify = new QgsMapToolIdentifyAction(mMapCanvas);
	mAnnotation = new QgsMapToolAnnotation(mMapCanvas);

	// ���ø������ߵĲ˵�����ť����
	mToolGroup = new QActionGroup(this);
	mToolGroup->addAction(ui.actionUnset_Tool);
	mToolGroup->addAction(ui.actionPan_Map);
	mToolGroup->addAction(ui.actionZoom_In);
	mToolGroup->addAction(ui.actionZoom_Out);
	mToolGroup->addAction(ui.actionMeasure);
	mToolGroup->addAction(ui.actionAnnotation);

	mToolGroup->setExclusive(true);

	// ���ò˵�����ť���źŲ�
	connect(ui.actionNew_Project, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui.actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
	connect(ui.actionSave_Project_As, SIGNAL(triggered()), this, SLOT(saveProjectAs()));
	connect(ui.actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
	connect(ui.actionUnset_Tool, SIGNAL(triggered()), this, SLOT(unsetMapTool));
	connect(ui.actionPan_Map, SIGNAL(triggered()), this, SLOT(pan()));
	connect(ui.actionZoom_Out, SIGNAL(triggered()), this, SLOT(zoomOut()));
	connect(ui.actionZoom_In, SIGNAL(triggered()), this, SLOT(zoomIn()));
	connect(ui.actionMeasure, SIGNAL(triggered()), this, SLOT(measure()));
	connect(ui.actionShow_Layers, SIGNAL(triggered()), this, SLOT(showLayersWindow()));
	connect(ui.actionAdd_Vector_Layer, SIGNAL(triggered()), this, SLOT(addVectorLayer()));
	//action����û��
	connect(ui.actionAddRaster, SIGNAL(triggered()), this, SLOT(addRasterLayer()));
	connect(ui.actionAddWFS, SIGNAL(triggered()), this, SLOT(addWFSLayer()));
	connect(ui.actionAddWCS, SIGNAL(triggered()), this, SLOT(addWCSLayer()));
	connect(ui.actionAddWMS, SIGNAL(triggered()), this, SLOT(addWMSLayer()));
	/////////////////����
	connect(ui.actionDelete_Layer, SIGNAL(triggered()), this, SLOT(deleteLayer()));
	connect(ui.actionIdentify, SIGNAL(triggered()), this, SLOT(identify()));
	connect(ui.actionAnnotation, SIGNAL(triggered()), this, SLOT(addAnnotation()));

	// ��Ŀ���޸�ʱ��Ŀ�����Ϊ���ࡱ״̬
	connect(mMapCanvas, SIGNAL(layersChanged()), this, SLOT(markDirty()));

	// ͼ�������
	connect(ui.layerList, SIGNAL( itemSelectionChanged()), this, SLOT(layerSelectionChanged()));
	connect(QgsMapLayerRegistry::instance(), SIGNAL(layersAdded(QList<QgsMapLayer*>)),
			this, SLOT(addToManagerWindow(QList<QgsMapLayer*>)));

	// ��д��ע��زۺ���
	connect(QgsProject::instance(), SIGNAL(readProject(const QDomDocument&)), 
			this, SLOT(loadAnnotationItemsFromProject(const QDomDocument&)));
	connect(QgsProject::instance(), SIGNAL(writeProject(QDomDocument&)),
			this, SLOT(writeAnnotationItemsToProject(QDomDocument&)));


	// ����ͼ����������Ҽ��˵�
	mPopMenu = new QMenu(ui.layerList);
	mPopMenu->addMenu(ui.menuAdd_Layer);
	mPopMenu->addAction(ui.actionDelete_Layer);
	connect(ui.layerList, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showPopMenu(const QPoint&)));
}

void QgisApp::enableMenu()
{
	if(ui.menuMap->isEnabled())
		return;

	ui.actionSave_Project->setEnabled(true);
	ui.actionSave_Project_As->setEnabled(true);
	ui.menuMap->setEnabled(true);
	ui.menuLayer->setEnabled(true);
}

void QgisApp::setTitle()
{
	QString caption = "QGIS Dev";
	QString fileName = QgsProject::instance()->fileName();

	if(fileName.isNull())
		caption += " - " + tr("δ����");
	else
		caption += " - " + QFileInfo(fileName).completeBaseName();

	this->setWindowTitle(caption);
}

void QgisApp::newProject()
{
	enableMenu();
	closeProject();
	QgsProject* prj = QgsProject::instance();
	prj->clear();
	prj->layerTreeRegistryBridge()->setNewLayersVisible(true);
	mLayerTreeCanvasBridge->clear();

	/*mMapCanvas->setSelectionColor(QColor(255, 255, 0, 255));
	mMapCanvas->setCanvasColor(QColor(255, 255, 255));*/
	prj->setDirty(false);					// �½���ĿӦΪδ�޸�״̬
	
	mMapCanvas->freeze(false);
	mMapCanvas->refresh();
	mMapCanvas->clearExtentHistory();
	prj->setDirty(false);

	setTitle();
}

bool QgisApp::saveProject()
{
	// ���û����Ŀ�ļ�·������ʾ�û�ѡ��·��
	if(QgsProject::instance()->fileName().isNull())
	{
		QFileInfo fullPath;
		QString path = QFileDialog::getSaveFileName(
						this,
						tr("ѡ��QGis��Ŀ�ı���λ��"),
						NULL,
						tr("QGIS files") + " (*.qgs *.QGS)");

		if(path.isEmpty())
			return false;

		fullPath.setFile(path);
		if ("qgs" != fullPath.suffix().toLower())
		{
			fullPath.setFile(fullPath.filePath() + ".qgs");
		}

		QgsProject::instance()->setFileName(fullPath.filePath());
	}
	else
	{
		QFileInfo fi(QgsProject::instance()->fileName());

		// ����Ƿ��д
		if(fi.exists() && !fi.isWritable())
		{
			QMessageBox::critical(this, tr("����"), tr("�޷�������Ŀ�ļ���"));
			return false;
		}
	}

	setTitle();
	// д�ļ�
	return QgsProject::instance()->write();
}

void QgisApp::saveProjectAs()
{
	// ����Ŀ�ļ���null��Ȼ�����saveProject����ʵ�����Ϊ
	QString fileNameBak = QgsProject::instance()->fileName();
	bool dirtyBak = QgsProject::instance()->isDirty();

	QgsProject::instance()->setFileName(NULL);
	if(!saveProject())		// δ�ɹ����Ϊ��ָ��ļ���
	{
		QgsProject::instance()->setFileName(fileNameBak);
		QgsProject::instance()->setDirty(dirtyBak);
	}
	setTitle();
}

void QgisApp::openProject()
{
	saveDirty();

	QFileInfo fullPath;
	QString path = QFileDialog::getOpenFileName(
					this,
					tr("ѡ��һ��QGis��Ŀ�ļ�"),
					NULL,
					tr("QGIS files") + " (*.qgs *.QGS)");
	if(path.isEmpty())
		return ;


	enableMenu();

	fullPath.setFile(path);
	qApp->processEvents();
	QApplication::setOverrideCursor( Qt::WaitCursor );
	closeProject();

	if(!QgsProject::instance()->read(fullPath))
		QMessageBox::critical(this, tr("����"), tr("�޷�������Ŀ�ļ���"));

	setTitle();
	
	mMapCanvas->freeze(false);
	mMapCanvas->updateScale();
	mMapCanvas->refresh();

	QgsProject::instance()->setDirty(false);
	QApplication::restoreOverrideCursor();
}

void QgisApp::closeProject()
{
	saveDirty();

	mMapCanvas->freeze(true);
	removeAnnotationItems();
	QList<QgsMapCanvasLayer> emptyList;
	mMapCanvas->setLayerSet(emptyList);
	mMapCanvas->clearCache();
	QgsMapLayerRegistry::instance()->removeAllMapLayers();
	ui.layerList->clear();
}

void QgisApp::removeAnnotationItems()
{
	if (!mMapCanvas)
		return;

	QGraphicsScene* scene = mMapCanvas->scene();
	if (!scene)
	{
		return;
	}
	QList<QgsAnnotationItem*> itemList = annotationItems();
	QList<QgsAnnotationItem*>::iterator itemIt = itemList.begin();
	for ( ; itemIt != itemList.end(); ++itemIt)
	{
		if (*itemIt)
		{
			scene->removeItem(*itemIt);
			delete *itemIt;
		}
	}
}

QList<QgsAnnotationItem*> QgisApp::annotationItems()
{
	QList<QgsAnnotationItem*> itemList;

	if (!mMapCanvas)
	{
		return itemList;
	}

	if (mMapCanvas)
	{
		QList<QGraphicsItem*> graphicsItems = mMapCanvas->items();
		QList<QGraphicsItem*>::iterator gIt = graphicsItems.begin();
		for ( ; gIt != graphicsItems.end(); ++gIt)
		{
			QgsAnnotationItem* currentItem = dynamic_cast<QgsAnnotationItem*>(*gIt);
			if (currentItem)
			{
				itemList.push_back(currentItem);
			}
		}
	}
	return itemList;
}

void QgisApp::writeAnnotationItemsToProject( QDomDocument& doc )
{
	QList<QgsAnnotationItem*> items = annotationItems();
	QgsAnnotationItem* item;
	QListIterator<QgsAnnotationItem*> i( items );
	// save lowermost annotation (at end of list) first
	i.toBack();
	while ( i.hasPrevious() )
	{
		item = i.previous();

		if ( ! item )
		{
			continue;
		}
		item->writeXML( doc );
	}
}

bool QgisApp::loadAnnotationItemsFromProject( const QDomDocument& doc )
{
	if ( !mMapCanvas )
	{
		return false;
	}

	removeAnnotationItems();

	if ( doc.isNull() )
	{
		return false;
	}

	QDomNodeList textItemList = doc.elementsByTagName( "TextAnnotationItem" );
	for ( int i = 0; i < textItemList.size(); ++i )
	{
		QgsTextAnnotationItem* newTextItem = new QgsTextAnnotationItem( mMapCanvas );
		newTextItem->readXML( doc, textItemList.at( i ).toElement() );
	}

	return true;
}

void QgisApp::markDirty()
{
	QgsProject::instance()->setDirty(true);
}

void QgisApp::saveDirty()
{
	bool dirty = QgsProject::instance()->isDirty();
	mMapCanvas->freeze(true);
	QMessageBox::StandardButton answer(QMessageBox::Discard);
	if(dirty)
	{
		answer = QMessageBox::information(
			this, 
			tr("���棿"),
			tr("��Ŀ�ѱ��޸ģ��Ƿ񱣴��޸ģ�"),
			QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard,
			QMessageBox::Save );
		if(QMessageBox::Save == answer)
			saveProject();
	}
	mMapCanvas->freeze(false);
}

void QgisApp::addToManagerWindow(QList<QgsMapLayer*> layers)
{
	for(auto it=layers.begin(); it!=layers.end(); it++)
	{
		QListWidgetItem *item = new QListWidgetItem(ui.layerList);
		item->setText((*it)->name());
		//item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
		//item->setCheckState(Qt::Checked);
		ui.layerList->addItem(item);
	}
}

void QgisApp::addToManagerWindow(QgsMapLayer* layer)
{
	addToManagerWindow(QList<QgsMapLayer*>() << layer);
}

void QgisApp::layerSelectionChanged()
{
	auto item = ui.layerList->selectedItems();
	if(item.isEmpty())
		return;
	auto layers = QgsMapLayerRegistry::instance()->mapLayersByName(item[0]->text());

	if(!layers.isEmpty())
	{
		mMapCanvas->setCurrentLayer(layers[0]);
	}
}

void QgisApp::showLayersWindow()
{
	if(ui.layersWindow->isHidden())
		ui.layersWindow->show();
}

void QgisApp::showPopMenu(const QPoint &pos)
{
	mPopMenu->exec(QCursor::pos());
}

void QgisApp::pan()
{
	setMapTool(mPan);
}

void QgisApp::zoomIn()
{
	setMapTool(mZoomIn);
}

void QgisApp::zoomOut()
{
	setMapTool(mZoomOut);
}

void QgisApp::measure()
{
	setMapTool(mMeasure);
}

void QgisApp::addAnnotation()
{
	setMapTool(mAnnotation);
}

void QgisApp::identify()
{
	mMapCanvas->setMapTool(mIdentify);
}

void QgisApp::setMapTool(QgsMapTool *tool)
{
	if(mMapCanvas->mapTool() == tool)
		unsetMapTool();
	else
		mMapCanvas->setMapTool(tool);
}

void QgisApp::unsetMapTool()
{
	auto tool = mMapCanvas->mapTool();
	if(tool)
	{
		mMapCanvas->unsetMapTool(tool);
		ui.actionUnset_Tool->setChecked(true);
	}
}

// ���դ��ͼ��
void QgisDev::addRasterLayer()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("���դ��ͼ��"), "", "*.jpg");
	if(filename.isEmpty()) 
		return;

	QStringList temp = filename.split(QDir::separator());
	QString basename = temp.at(temp.size() - 1);
	QgsRasterLayer* rasLayer = new QgsRasterLayer(filename, basename, "ogr", false);
	if(!rasLayer->isValid())
	{
		QMessageBox::critical(this, "error", "layer is invalid");
		return;
	}

	mMapCanvas->freeze(true);
	QgsMapLayerRegistry::instance()->addMapLayer(rasLayer);
	
	if(mMapCanvas->isFrozen())
	{
		mMapCanvas->freeze(false);
		mMapCanvas->refresh();
	}
}

// ���WFSͼ��
void QgisDev::addWFSLayer()
{
 if ( !mMapCanvas ) 
	 return;

    QDialog *wfs = dynamic_cast<QDialog*>( QgsProviderRegistry::instance()->selectWidget( QString( "WFS" ), this ) );
    if ( !wfs )
    {
        QMessageBox::warning( this, tr( "WFS" ), tr( "Cannot get WFS select dialog from provider." ) );
        return;
    }
    connect( wfs, SIGNAL( addWfsLayer( QString, QString ) ),
             this, SLOT( addWfsLayer( const QString, const QString ) ) );

    //re-enable wfs with extent setting: pass canvas info to source select
    wfs->setProperty( "MapExtent", mMapCanvas->extent().toString() );
    if ( mMapCanvas->mapSettings().hasCrsTransformEnabled() )
    {
        //if "on the fly" reprojection is active, pass canvas CRS
        wfs->setProperty( "MapCRS", mMapCanvas->mapSettings().destinationCrs().authid() );
    }

    bool bkRenderFlag = mMapCanvas->renderFlag();
    mMapCanvas->setRenderFlag( false );
    wfs->exec();
    mMapCanvas->setRenderFlag( bkRenderFlag );
    delete wfs;   
}



// ���WCSͼ��
void QgisDev::addWCSLayer()
{
	QDialog *wcs = dynamic_cast<QDialog*>( QgsProviderRegistry::instance()->selectWidget( QString( "wcs" ), this ) );
    if ( !wcs )
    {
        //QgisApp::instance()->statusBar()->showMessage( tr( "cannot add wms layer." ), 10 );
    }

    connect( wcs, SIGNAL( addRasterLayer( QString const &, QString const &, QString const & ) ),
             this, SLOT( addOpenSourceRasterLayer( QString const &, QString const &, QString const & ) ) );

    wcs->exec();

    delete wcs;
}

// ���WMSͼ��
void QgisDev::addWMSLayer()
{
	QDialog *wms = dynamic_cast<QDialog*>( QgsProviderRegistry::instance()->selectWidget( QString( "wms" ), this ) );
    if ( !wms )
    {
        //QgisApp::instance()->statusBar()->showMessage( tr( "cannot add wms layer." ), 10 );
    }

    connect( wms, SIGNAL( addRasterLayer( QString const &, QString const &, QString const & ) ),
             this, SLOT( addOpenSourceRasterLayer( QString const &, QString const &, QString const & ) ) );

    wms->exec();

    delete wms;
}

void QgisApp::addVectorLayer()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("���ʸ��ͼ��"), "", "*.shp");
	if(filename.isEmpty()) return;

	QStringList temp = filename.split(QDir::separator());
	QString basename = temp.at(temp.size() - 1);
	QgsVectorLayer* vecLayer = new QgsVectorLayer(filename, basename, "ogr", false);
	if(!vecLayer->isValid())
	{
		QMessageBox::critical(this, "error", "layer is invalid");
		return;
	}

	mMapCanvas->freeze(true);
	QgsMapLayerRegistry::instance()->addMapLayer(vecLayer);
	
	if(mMapCanvas->isFrozen())
	{
		mMapCanvas->freeze(false);
		mMapCanvas->refresh();
	}
}

void QgisApp::deleteLayer()
{
	auto currentItem = ui.layerList->selectedItems()[0];
	if(currentItem)
	{
		QMessageBox::StandardButton answer = QMessageBox::information(
			this, 
			tr("�Ƿ�ɾ��ͼ��"),
			tr("�Ƿ�ɾ������ͼ�㣺\n")+currentItem->text(),
			QMessageBox::Ok | QMessageBox::Cancel,
			QMessageBox::Cancel );
		if(answer == QMessageBox::Ok)
		{
			this->setWindowTitle(mMapCanvas->currentLayer()->name());
			if(mMapCanvas->currentLayer())
				QgsMapLayerRegistry::instance()->removeMapLayer(mMapCanvas->currentLayer());
			ui.layerList->removeItemWidget(currentItem);
			delete currentItem;
		}
	}
}
