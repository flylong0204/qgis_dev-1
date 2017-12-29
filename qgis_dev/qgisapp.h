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
	// 新建项目
	void newProject();

	// 保存项目
	bool saveProject();

	// 另存为项目
	void saveProjectAs();

	// 打开项目
	void openProject();

	// 将项目标记为“脏”状态
	void markDirty();

	// 退出所有地图工具
	void unsetMapTool();

	// 平移地图
	void pan();

	// 缩小地图
	void zoomOut();

	// 放大地图
	void zoomIn();

	// 测距
	void measure();

	// 添加矢量图层
	void addVectorLayer();

	// 添加栅格图层
	void addRasterLayer();

	// 删除图层
	void deleteLayer();

	// 图元识别
	void identify();

	// 图层标注
	void addAnnotation();

	// 从项目中读取标注
	bool loadAnnotationItemsFromProject(const QDomDocument& doc);

	// 将标注写入到项目中
	void writeAnnotationItemsToProject(QDomDocument& doc);

	// 图层管理器里的选中图层发生变化
	void layerSelectionChanged();

	// 将图层添加到图层管理器
	void addToManagerWindow(QList<QgsMapLayer*> layers);

	// 显示图层管理器
	void showLayersWindow();

	// 显示右键菜单
	void showPopMenu(const QPoint &pos);

private:
	// 使菜单栏可用
	void enableMenu();

	// 设置窗体标题
	void setTitle();

	// 初始化界面
	void init();

	// 设置图层工具
	void setMapTool(QgsMapTool *tool);

	// 关闭项目
	void closeProject();

	// 移除所有标注
	void removeAnnotationItems();

	// 返回所有标注
	QList<QgsAnnotationItem*> annotationItems();

	// 保存修改处
	void saveDirty();

	// 将图层添加到图层管理窗体
	void addToManagerWindow(QgsMapLayer* layer);


private:
	Ui::QgisAppClass ui;

	// 工具组
	QActionGroup* mToolGroup;
	// 地图画布
	QgsMapCanvas* mMapCanvas;
	// 用以管理图层
	QgsLayerTreeMapCanvasBridge* mLayerTreeCanvasBridge;
	// 平移地图工具
	QgsMapToolPan* mPan;
	// 缩小地图工具
	QgsMapToolZoom* mZoomOut;
	// 放大地图工具
	QgsMapToolZoom* mZoomIn;
	// 测距工具
	QgsMeasureTool* mMeasure;
	// 图元识别工具
	QgsMapToolIdentifyAction* mIdentify;
	// 添加图层标注工具
	QgsMapTool* mAnnotation;
	// 右键弹出菜单
	QMenu* mPopMenu;

};

#endif // QGISAPP_H
