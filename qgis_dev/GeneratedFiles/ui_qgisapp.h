/********************************************************************************
** Form generated from reading UI file 'qgisapp.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGISAPP_H
#define UI_QGISAPP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QgisAppClass
{
public:
    QAction *actionNew_Project;
    QAction *actionOpen_Project;
    QAction *actionSave_Project;
    QAction *actionSave_Project_As;
    QAction *actionZoom_Out;
    QAction *actionZoom_In;
    QAction *actionPan_Map;
    QAction *actionMeasure;
    QAction *actionDelete_Layer;
    QAction *actionAnnotation;
    QAction *actionAdd_Vector_Layer;
    QAction *actionShow_Layers;
    QAction *actionIdentify;
    QAction *actionUnset_Tool;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuProject;
    QMenu *menuMap;
    QMenu *menuLayer;
    QMenu *menuAdd_Layer;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *layersWindow;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QListWidget *layerList;

    void setupUi(QMainWindow *QgisAppClass)
    {
        if (QgisAppClass->objectName().isEmpty())
            QgisAppClass->setObjectName(QString::fromUtf8("QgisAppClass"));
        QgisAppClass->resize(923, 511);
        QgisAppClass->setContextMenuPolicy(Qt::ActionsContextMenu);
        actionNew_Project = new QAction(QgisAppClass);
        actionNew_Project->setObjectName(QString::fromUtf8("actionNew_Project"));
        actionOpen_Project = new QAction(QgisAppClass);
        actionOpen_Project->setObjectName(QString::fromUtf8("actionOpen_Project"));
        actionSave_Project = new QAction(QgisAppClass);
        actionSave_Project->setObjectName(QString::fromUtf8("actionSave_Project"));
        actionSave_Project->setEnabled(false);
        actionSave_Project_As = new QAction(QgisAppClass);
        actionSave_Project_As->setObjectName(QString::fromUtf8("actionSave_Project_As"));
        actionSave_Project_As->setEnabled(false);
        actionZoom_Out = new QAction(QgisAppClass);
        actionZoom_Out->setObjectName(QString::fromUtf8("actionZoom_Out"));
        actionZoom_Out->setCheckable(true);
        actionZoom_In = new QAction(QgisAppClass);
        actionZoom_In->setObjectName(QString::fromUtf8("actionZoom_In"));
        actionZoom_In->setCheckable(true);
        actionPan_Map = new QAction(QgisAppClass);
        actionPan_Map->setObjectName(QString::fromUtf8("actionPan_Map"));
        actionPan_Map->setCheckable(true);
        actionMeasure = new QAction(QgisAppClass);
        actionMeasure->setObjectName(QString::fromUtf8("actionMeasure"));
        actionMeasure->setCheckable(true);
        actionDelete_Layer = new QAction(QgisAppClass);
        actionDelete_Layer->setObjectName(QString::fromUtf8("actionDelete_Layer"));
        actionAnnotation = new QAction(QgisAppClass);
        actionAnnotation->setObjectName(QString::fromUtf8("actionAnnotation"));
        actionAnnotation->setCheckable(true);
        actionAdd_Vector_Layer = new QAction(QgisAppClass);
        actionAdd_Vector_Layer->setObjectName(QString::fromUtf8("actionAdd_Vector_Layer"));
        actionShow_Layers = new QAction(QgisAppClass);
        actionShow_Layers->setObjectName(QString::fromUtf8("actionShow_Layers"));
        actionIdentify = new QAction(QgisAppClass);
        actionIdentify->setObjectName(QString::fromUtf8("actionIdentify"));
        actionIdentify->setCheckable(true);
        actionUnset_Tool = new QAction(QgisAppClass);
        actionUnset_Tool->setObjectName(QString::fromUtf8("actionUnset_Tool"));
        actionUnset_Tool->setCheckable(true);
        actionUnset_Tool->setChecked(true);
        actionUnset_Tool->setEnabled(true);
        centralWidget = new QWidget(QgisAppClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QgisAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QgisAppClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 923, 26));
        menuProject = new QMenu(menuBar);
        menuProject->setObjectName(QString::fromUtf8("menuProject"));
        menuMap = new QMenu(menuBar);
        menuMap->setObjectName(QString::fromUtf8("menuMap"));
        menuMap->setEnabled(false);
        menuLayer = new QMenu(menuBar);
        menuLayer->setObjectName(QString::fromUtf8("menuLayer"));
        menuLayer->setEnabled(false);
        menuAdd_Layer = new QMenu(menuLayer);
        menuAdd_Layer->setObjectName(QString::fromUtf8("menuAdd_Layer"));
        QgisAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QgisAppClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QgisAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QgisAppClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QgisAppClass->setStatusBar(statusBar);
        layersWindow = new QDockWidget(QgisAppClass);
        layersWindow->setObjectName(QString::fromUtf8("layersWindow"));
        layersWindow->setEnabled(true);
        layersWindow->setMouseTracking(false);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        layerList = new QListWidget(dockWidgetContents_2);
        layerList->setObjectName(QString::fromUtf8("layerList"));
        layerList->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout->addWidget(layerList);

        layersWindow->setWidget(dockWidgetContents_2);
        QgisAppClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), layersWindow);

        menuBar->addAction(menuProject->menuAction());
        menuBar->addAction(menuMap->menuAction());
        menuBar->addAction(menuLayer->menuAction());
        menuProject->addAction(actionOpen_Project);
        menuProject->addAction(actionNew_Project);
        menuProject->addAction(actionSave_Project);
        menuProject->addAction(actionSave_Project_As);
        menuMap->addAction(actionUnset_Tool);
        menuMap->addAction(actionZoom_Out);
        menuMap->addAction(actionZoom_In);
        menuMap->addAction(actionPan_Map);
        menuMap->addAction(actionMeasure);
        menuMap->addAction(actionIdentify);
        menuMap->addAction(actionAnnotation);
        menuLayer->addAction(actionShow_Layers);
        menuLayer->addAction(menuAdd_Layer->menuAction());
        menuLayer->addAction(actionDelete_Layer);
        menuAdd_Layer->addAction(actionAdd_Vector_Layer);

        retranslateUi(QgisAppClass);

        QMetaObject::connectSlotsByName(QgisAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *QgisAppClass)
    {
        QgisAppClass->setWindowTitle(QApplication::translate("QgisAppClass", "QGIS Dev", 0, QApplication::UnicodeUTF8));
        actionNew_Project->setText(QApplication::translate("QgisAppClass", "\346\226\260\345\273\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        actionOpen_Project->setText(QApplication::translate("QgisAppClass", "\346\211\223\345\274\200\351\241\271\347\233\256...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen_Project->setToolTip(QApplication::translate("QgisAppClass", "\346\211\223\345\274\200\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave_Project->setText(QApplication::translate("QgisAppClass", "\344\277\235\345\255\230\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        actionSave_Project_As->setText(QApplication::translate("QgisAppClass", "\351\241\271\347\233\256\345\217\246\345\255\230\344\270\272...", 0, QApplication::UnicodeUTF8));
        actionZoom_Out->setText(QApplication::translate("QgisAppClass", "\347\274\251\345\260\217\345\234\260\345\233\276", 0, QApplication::UnicodeUTF8));
        actionZoom_In->setText(QApplication::translate("QgisAppClass", "\346\224\276\345\244\247\345\234\260\345\233\276", 0, QApplication::UnicodeUTF8));
        actionPan_Map->setText(QApplication::translate("QgisAppClass", "\345\271\263\347\247\273\345\234\260\345\233\276", 0, QApplication::UnicodeUTF8));
        actionMeasure->setText(QApplication::translate("QgisAppClass", "\346\265\213\350\267\235", 0, QApplication::UnicodeUTF8));
        actionDelete_Layer->setText(QApplication::translate("QgisAppClass", "\345\210\240\351\231\244\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        actionAnnotation->setText(QApplication::translate("QgisAppClass", "\345\233\276\345\261\202\346\240\207\346\263\250", 0, QApplication::UnicodeUTF8));
        actionAdd_Vector_Layer->setText(QApplication::translate("QgisAppClass", "\346\267\273\345\212\240\347\237\242\351\207\217\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        actionShow_Layers->setText(QApplication::translate("QgisAppClass", "\346\230\276\347\244\272\345\233\276\345\261\202\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        actionIdentify->setText(QApplication::translate("QgisAppClass", "\345\233\276\345\205\203\350\257\206\345\210\253", 0, QApplication::UnicodeUTF8));
        actionUnset_Tool->setText(QApplication::translate("QgisAppClass", "\351\200\200\345\207\272\345\275\223\345\211\215\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        actionUnset_Tool->setIconText(QApplication::translate("QgisAppClass", "\344\270\215\344\275\277\347\224\250\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
        menuProject->setTitle(QApplication::translate("QgisAppClass", "\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        menuMap->setTitle(QApplication::translate("QgisAppClass", "\345\234\260\345\233\276\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        menuLayer->setTitle(QApplication::translate("QgisAppClass", "\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        menuAdd_Layer->setTitle(QApplication::translate("QgisAppClass", "\346\267\273\345\212\240\345\233\276\345\261\202...", 0, QApplication::UnicodeUTF8));
        layersWindow->setWindowTitle(QApplication::translate("QgisAppClass", "\345\233\276\345\261\202\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QgisAppClass: public Ui_QgisAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGISAPP_H
