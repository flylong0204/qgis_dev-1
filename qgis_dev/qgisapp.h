#ifndef QGISAPP_H
#define QGISAPP_H

#include "ui_qgisapp.h"

// qt include
#include <QtGui/QMainWindow>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>

// qgis include
#include <qgsmapcanvas.h>
#include <qgsmaplayerregistry.h>
#include <qgsproject.h>
#include <qgslayertreeregistrybridge.h>
#include <qgslayertreemapcanvasbridge.h>
#include <qgsvectorlayer.h>
#include <qgsmaptoolpan.h>
#include <qgsmaptoolzoom.h>
#include "qgsmeasuretool.h"
#include "qgsmaptoolidentifyaction.h"
#include "qgsmaptoolannotation.h"
#include <qgstextannotationitem.h>



class QgisApp : public QMainWindow
{
	Q_OBJECT

public:
	QgisApp(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QgisApp();

private slots:
	// �½���Ŀ
	void newProject();

	// ������Ŀ
	bool saveProject();

	// ���Ϊ��Ŀ
	void saveProjectAs();

	// ����Ŀ
	void openProject();

	// ����Ŀ���Ϊ���ࡱ״̬
	void markDirty();

	// �˳����е�ͼ����
	void unsetMapTool();

	// ƽ�Ƶ�ͼ
	void pan();

	// ��С��ͼ
	void zoomOut();

	// �Ŵ��ͼ
	void zoomIn();

	// ���
	void measure();

	// ���ʸ��ͼ��
	void addVectorLayer();

	// ���դ��ͼ��
	void addRasterLayer();

	// ɾ��ͼ��
	void deleteLayer();

	// ͼԪʶ��
	void identify();

	// ͼ���ע
	void addAnnotation();

	// ����Ŀ�ж�ȡ��ע
	bool loadAnnotationItemsFromProject(const QDomDocument& doc);

	// ����עд�뵽��Ŀ��
	void writeAnnotationItemsToProject(QDomDocument& doc);

	// ͼ����������ѡ��ͼ�㷢���仯
	void layerSelectionChanged();

	// ��ͼ����ӵ�ͼ�������
	void addToManagerWindow(QList<QgsMapLayer*> layers);

	// ��ʾͼ�������
	void showLayersWindow();

	// ��ʾ�Ҽ��˵�
	void showPopMenu(const QPoint &pos);

private:
	// ʹ�˵�������
	void enableMenu();

	// ���ô������
	void setTitle();

	// ��ʼ������
	void init();

	// ����ͼ�㹤��
	void setMapTool(QgsMapTool *tool);

	// �ر���Ŀ
	void closeProject();

	// �Ƴ����б�ע
	void removeAnnotationItems();

	// �������б�ע
	QList<QgsAnnotationItem*> annotationItems();

	// �����޸Ĵ�
	void saveDirty();

	// ��ͼ����ӵ�ͼ�������
	void addToManagerWindow(QgsMapLayer* layer);


private:
	Ui::QgisAppClass ui;

	// ������
	QActionGroup* mToolGroup;
	// ��ͼ����
	QgsMapCanvas* mMapCanvas;
	// ���Թ���ͼ��
	QgsLayerTreeMapCanvasBridge* mLayerTreeCanvasBridge;
	// ƽ�Ƶ�ͼ����
	QgsMapToolPan* mPan;
	// ��С��ͼ����
	QgsMapToolZoom* mZoomOut;
	// �Ŵ��ͼ����
	QgsMapToolZoom* mZoomIn;
	// ��๤��
	QgsMeasureTool* mMeasure;
	// ͼԪʶ�𹤾�
	QgsMapToolIdentifyAction* mIdentify;
	// ���ͼ���ע����
	QgsMapTool* mAnnotation;
	// �Ҽ������˵�
	QMenu* mPopMenu;

};

#endif // QGISAPP_H
