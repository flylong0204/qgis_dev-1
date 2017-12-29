/********************************************************************************
** Form generated from reading UI file 'qgsmeasuredialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGSMEASUREDIALOG_H
#define UI_QGSMEASUREDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QgsMeasureDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *restartButton;
    QSpacerItem *spacerItem;
    QPushButton *closeButton;
    QLabel *label;
    QLabel *totalDist;
    QLabel *unit;

    void setupUi(QDialog *QgsMeasureDialog)
    {
        if (QgsMeasureDialog->objectName().isEmpty())
            QgsMeasureDialog->setObjectName(QString::fromUtf8("QgsMeasureDialog"));
        QgsMeasureDialog->resize(400, 129);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QgsMeasureDialog->sizePolicy().hasHeightForWidth());
        QgsMeasureDialog->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(QgsMeasureDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 80, 351, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        restartButton = new QPushButton(layoutWidget);
        restartButton->setObjectName(QString::fromUtf8("restartButton"));

        hboxLayout->addWidget(restartButton);

        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        closeButton = new QPushButton(layoutWidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        hboxLayout->addWidget(closeButton);

        label = new QLabel(QgsMeasureDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 33, 51, 16));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        totalDist = new QLabel(QgsMeasureDialog);
        totalDist->setObjectName(QString::fromUtf8("totalDist"));
        totalDist->setGeometry(QRect(80, 30, 201, 21));
        totalDist->setFont(font);
        totalDist->setFrameShape(QFrame::Panel);
        totalDist->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        unit = new QLabel(QgsMeasureDialog);
        unit->setObjectName(QString::fromUtf8("unit"));
        unit->setGeometry(QRect(290, 33, 72, 15));
        unit->setFont(font);

        retranslateUi(QgsMeasureDialog);
        QObject::connect(closeButton, SIGNAL(clicked()), QgsMeasureDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(QgsMeasureDialog);
    } // setupUi

    void retranslateUi(QDialog *QgsMeasureDialog)
    {
        QgsMeasureDialog->setWindowTitle(QApplication::translate("QgsMeasureDialog", "\346\265\213\350\267\235", 0, QApplication::UnicodeUTF8));
        restartButton->setText(QApplication::translate("QgsMeasureDialog", "\351\207\215\346\226\260\345\274\200\345\247\213", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("QgsMeasureDialog", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QgsMeasureDialog", "Total", 0, QApplication::UnicodeUTF8));
        totalDist->setText(QApplication::translate("QgsMeasureDialog", "0.000 m", 0, QApplication::UnicodeUTF8));
        unit->setText(QApplication::translate("QgsMeasureDialog", "meters", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QgsMeasureDialog: public Ui_QgsMeasureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGSMEASUREDIALOG_H
