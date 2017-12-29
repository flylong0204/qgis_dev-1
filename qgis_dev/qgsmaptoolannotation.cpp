/***************************************************************************
                              qgsmaptoolannotation.cpp
                              ----------------------------
  begin                : February 9, 2010
  copyright            : (C) 2010 by Marco Hugentobler
  email                : marco dot hugentobler at hugis dot net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsmaptoolannotation.h"
#include <qgsmapcanvas.h>
#include "qgstextannotationdialog.h"
#include "qgstextannotationitem.h"
#include <qgsproject.h>
#include <QDialog>
#include <QMouseEvent>

QgsMapToolAnnotation::QgsMapToolAnnotation( QgsMapCanvas* canvas )
    : QgsMapTool( canvas )
    , mCurrentMoveAction( QgsAnnotationItem::NoAction )
    , mLastMousePosition( 0, 0 )
{
  mCursor = QCursor( Qt::ArrowCursor );
}

QgsMapToolAnnotation::~QgsMapToolAnnotation()
{
}

QgsAnnotationItem* QgsMapToolAnnotation::createItem( QMouseEvent *e )
{
	QgsPoint mapCoord = toMapCoordinates( e->pos() );
	QgsTextAnnotationItem* textItem = new QgsTextAnnotationItem( mCanvas );
	textItem->setMapPosition( toMapCoordinates( e->pos() ) );
	textItem->setFrameSize( QSizeF( 200, 100 ) );
	textItem->setSelected( true );
	QgsProject::instance()->setDirty( true );
	return textItem;
}

QDialog* QgsMapToolAnnotation::createItemEditor( QgsAnnotationItem *item )
{
  if ( !item )
  {
    return nullptr;
  }

  QgsTextAnnotationItem* tItem = dynamic_cast<QgsTextAnnotationItem*>( item );
  if ( tItem )
  {
    return new QgsTextAnnotationDialog( tItem );
  }

  return nullptr;
}

void QgsMapToolAnnotation::canvasReleaseEvent( QgsMapMouseEvent* e )
{
  Q_UNUSED( e );

  mCurrentMoveAction = QgsAnnotationItem::NoAction;
  mCanvas->setCursor( mCursor );
}

void QgsMapToolAnnotation::canvasPressEvent( QgsMapMouseEvent* e )
{
  if ( !mCanvas )
  {
    return;
  }

  QgsAnnotationItem* sItem = selectedItem();
  if ( sItem )
  {
    mCurrentMoveAction = sItem->moveActionForPosition( e->posF() );
    if ( mCurrentMoveAction != QgsAnnotationItem::NoAction )
    {
      return;
    }
  }

  if ( !sItem || mCurrentMoveAction == QgsAnnotationItem::NoAction )
  {
    //select a new item if there is one at this position
    mCanvas->scene()->clearSelection();
    QgsAnnotationItem* existingItem = itemAtPos( e->posF() );
    if ( existingItem )
    {
      existingItem->setSelected( true );
    }
    else
    {
      //otherwise create new one
      createItem( e );
    }
  }
}

void QgsMapToolAnnotation::keyPressEvent( QKeyEvent* e )
{
  if ( e->key() == Qt::Key_T && e->modifiers() == Qt::ControlModifier )
  {
    toggleTextItemVisibilities();
  }

  QgsAnnotationItem* sItem = selectedItem();
  if ( sItem )
  {
    if ( e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Delete )
    {
      if ( mCanvas && mCanvas->scene() )
      {
        QCursor neutralCursor( sItem->cursorShapeForAction( QgsAnnotationItem::NoAction ) );
        mCanvas->scene()->removeItem( sItem );
        delete sItem;
        mCanvas->setCursor( neutralCursor );
        QgsProject::instance()->setDirty( true ); // TODO QGIS3: Rework the whole annotation code to be MVC compliant, see PR #2506

        // Override default shortcut management in MapCanvas
        e->ignore();
      }
    }
  }
}

void QgsMapToolAnnotation::canvasMoveEvent( QgsMapMouseEvent* e )
{
  QgsAnnotationItem* sItem = selectedItem();
  if ( sItem && ( e->buttons() & Qt::LeftButton ) )
  {
    if ( mCurrentMoveAction == QgsAnnotationItem::MoveMapPosition )
    {
      sItem->setMapPosition( toMapCoordinates( e->pos() ) );
      sItem->update();
      QgsProject::instance()->setDirty( true );
    }
    else if ( mCurrentMoveAction == QgsAnnotationItem::MoveFramePosition )
    {
      if ( sItem->mapPositionFixed() )
      {
        sItem->setOffsetFromReferencePoint( sItem->offsetFromReferencePoint() + ( e->posF() - mLastMousePosition ) );
      }
      else
      {
        QPointF newCanvasPos = sItem->pos() + ( e->posF() - mLastMousePosition );
        sItem->setMapPosition( toMapCoordinates( newCanvasPos.toPoint() ) );
      }
      sItem->update();
      QgsProject::instance()->setDirty( true );
    }
    else if ( mCurrentMoveAction != QgsAnnotationItem::NoAction )
    {
      //handle the frame resize actions
      QSizeF size = sItem->frameSize();
      double xmin = sItem->offsetFromReferencePoint().x();
      double ymin = sItem->offsetFromReferencePoint().y();
      double xmax = xmin + size.width();
      double ymax = ymin + size.height();

      if ( mCurrentMoveAction == QgsAnnotationItem::ResizeFrameRight ||
           mCurrentMoveAction == QgsAnnotationItem::ResizeFrameRightDown ||
           mCurrentMoveAction == QgsAnnotationItem::ResizeFrameRightUp )
      {
        xmax += e->posF().x() - mLastMousePosition.x();
      }
      if ( mCurrentMoveAction == QgsAnnotationItem::ResizeFrameLeft ||
           mCurrentMoveAction == QgsAnnotationItem::ResizeFrameLeftDown ||
           mCurrentMoveAction == QgsAnnotationItem::ResizeFrameLeftUp )
      {
        xmin += e->posF().x() - mLastMousePosition.x();
      }
      if ( mCurrentMoveAction == QgsAnnotationItem::ResizeFrameUp ||
           mCurrentMoveAction == QgsAnnotationItem::ResizeFrameLeftUp ||
           mCurrentMoveAction == QgsAnnotationItem::ResizeFrameRightUp )
      {
        ymin += e->posF().y() - mLastMousePosition.y();
      }
      if ( mCurrentMoveAction == QgsAnnotationItem::ResizeFrameDown ||
           mCurrentMoveAction == QgsAnnotationItem::ResizeFrameLeftDown ||
           mCurrentMoveAction == QgsAnnotationItem::ResizeFrameRightDown )
      {
        ymax += e->posF().y() - mLastMousePosition.y();
      }

      //switch min / max if necessary
      double tmp;
      if ( xmax < xmin )
      {
        tmp = xmax;
        xmax = xmin;
        xmin = tmp;
      }
      if ( ymax < ymin )
      {
        tmp = ymax;
        ymax = ymin;
        ymin = tmp;
      }

      sItem->setOffsetFromReferencePoint( QPointF( xmin, ymin ) );
      sItem->setFrameSize( QSizeF( xmax - xmin, ymax - ymin ) );
      sItem->update();
      QgsProject::instance()->setDirty( true );
    }
  }
  else if ( sItem )
  {
    QgsAnnotationItem::MouseMoveAction moveAction = sItem->moveActionForPosition( e->posF() );
    if ( mCanvas )
    {
      mCanvas->setCursor( QCursor( sItem->cursorShapeForAction( moveAction ) ) );
    }
  }
  mLastMousePosition = e->posF();
}

void QgsMapToolAnnotation::canvasDoubleClickEvent( QgsMapMouseEvent* e )
{
  QgsAnnotationItem* item = itemAtPos( e->posF() );
  if ( !item )
  {
    return;
  }
  QDialog* itemEditor = createItemEditor( item );
  if ( itemEditor )
  {
    if ( itemEditor->exec() )
      QgsProject::instance()->setDirty( true );
    delete itemEditor;
  }
}

QgsAnnotationItem* QgsMapToolAnnotation::itemAtPos( QPointF pos )
{
  if ( !mCanvas )
  {
    return nullptr;
  }

  QList<QGraphicsItem *> graphicItems = mCanvas->items( pos.toPoint() );
  QList<QGraphicsItem *>::iterator gIt = graphicItems.begin();
  for ( ; gIt != graphicItems.end(); ++gIt )
  {
    QgsAnnotationItem* annotationItem = dynamic_cast<QgsAnnotationItem*>( *gIt );
    if ( annotationItem )
    {
      return annotationItem;
    }
  }
  return nullptr;
}

QgsAnnotationItem* QgsMapToolAnnotation::selectedItem()
{
  if ( !mCanvas || !mCanvas->scene() )
  {
    return nullptr;
  }
  QList<QGraphicsItem *> gItemList = mCanvas->scene()->selectedItems();
  QList<QGraphicsItem *>::iterator it = gItemList.begin();
  for ( ; it != gItemList.end(); ++it )
  {
    QgsAnnotationItem* aItem = dynamic_cast<QgsAnnotationItem*>( *it );
    if ( aItem )
    {
      return aItem;
    }
  }
  return nullptr;
}

QList<QgsAnnotationItem*> QgsMapToolAnnotation::annotationItems()
{
  QList<QgsAnnotationItem*> annotationItemList;
  if ( !mCanvas || !mCanvas->scene() )
  {
    return annotationItemList;
  }

  QList<QGraphicsItem *>  itemList = mCanvas->scene()->items();
  QList<QGraphicsItem *>::iterator it = itemList.begin();
  for ( ; it != itemList.end(); ++it )
  {
    QgsAnnotationItem* aItem = dynamic_cast<QgsAnnotationItem*>( *it );
    if ( aItem )
    {
      annotationItemList.push_back( aItem );
    }
  }

  return annotationItemList;
}

void QgsMapToolAnnotation::toggleTextItemVisibilities()
{
  QList<QgsAnnotationItem*> itemList = annotationItems();
  QList<QgsAnnotationItem*>::iterator itemIt = itemList.begin();
  for ( ; itemIt != itemList.end(); ++itemIt )
  {
    QgsTextAnnotationItem* textItem = dynamic_cast<QgsTextAnnotationItem*>( *itemIt );
    if ( textItem )
    {
      textItem->setVisible( !textItem->isVisible() );
    }
  }
}
