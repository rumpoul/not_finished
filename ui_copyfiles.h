/********************************************************************************
** Form generated from reading UI file 'copyfiles.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYFILES_H
#define UI_COPYFILES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_copyfiles
{
public:
    QWidget *centralWidget;
    QPushButton *Button_Test;
    QPushButton *pushButton;
    QPushButton *ButSetPathTo;
    QCheckBox *checkBox_autorun;
    QTextBrowser *textBrowser;
    QPushButton *ButSetPathFrom;
    QLabel *label_TO;
    QLabel *label_FROM;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *ButtonSettingsFile;
    QPushButton *ButtonSaveSettingsIntoFle;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox_systemtray;
    QTimeEdit *timeEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QCheckBox *checkBox_remove_after_copy;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_for_radioButtons;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_freshDate;
    QRadioButton *radioButton_allFiles;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *copyfiles)
    {
        if (copyfiles->objectName().isEmpty())
            copyfiles->setObjectName(QStringLiteral("copyfiles"));
        copyfiles->resize(591, 515);
        QIcon icon;
        icon.addFile(QStringLiteral("glass.png"), QSize(), QIcon::Normal, QIcon::Off);
        copyfiles->setWindowIcon(icon);
        centralWidget = new QWidget(copyfiles);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Button_Test = new QPushButton(centralWidget);
        Button_Test->setObjectName(QStringLiteral("Button_Test"));
        Button_Test->setGeometry(QRect(10, 90, 93, 28));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 130, 93, 28));
        ButSetPathTo = new QPushButton(centralWidget);
        ButSetPathTo->setObjectName(QStringLiteral("ButSetPathTo"));
        ButSetPathTo->setGeometry(QRect(10, 50, 93, 28));
        checkBox_autorun = new QCheckBox(centralWidget);
        checkBox_autorun->setObjectName(QStringLiteral("checkBox_autorun"));
        checkBox_autorun->setGeometry(QRect(10, 170, 161, 20));
        checkBox_autorun->setChecked(false);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 230, 501, 151));
        ButSetPathFrom = new QPushButton(centralWidget);
        ButSetPathFrom->setObjectName(QStringLiteral("ButSetPathFrom"));
        ButSetPathFrom->setGeometry(QRect(11, 11, 93, 28));
        label_TO = new QLabel(centralWidget);
        label_TO->setObjectName(QStringLiteral("label_TO"));
        label_TO->setGeometry(QRect(110, 60, 381, 16));
        label_FROM = new QLabel(centralWidget);
        label_FROM->setObjectName(QStringLiteral("label_FROM"));
        label_FROM->setGeometry(QRect(110, 20, 381, 16));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 90, 95, 65));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ButtonSettingsFile = new QPushButton(layoutWidget);
        ButtonSettingsFile->setObjectName(QStringLiteral("ButtonSettingsFile"));

        verticalLayout->addWidget(ButtonSettingsFile);

        ButtonSaveSettingsIntoFle = new QPushButton(layoutWidget);
        ButtonSaveSettingsIntoFle->setObjectName(QStringLiteral("ButtonSaveSettingsIntoFle"));

        verticalLayout->addWidget(ButtonSaveSettingsIntoFle);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(260, 140, 251, 82));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        checkBox_systemtray = new QCheckBox(layoutWidget1);
        checkBox_systemtray->setObjectName(QStringLiteral("checkBox_systemtray"));
        checkBox_systemtray->setChecked(false);

        verticalLayout_2->addWidget(checkBox_systemtray);

        timeEdit = new QTimeEdit(layoutWidget1);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setTime(QTime(4, 30, 0));

        verticalLayout_2->addWidget(timeEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(layoutWidget1);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(12);
        spinBox->setValue(2);

        horizontalLayout->addWidget(spinBox);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);


        verticalLayout_2->addLayout(horizontalLayout);

        checkBox_remove_after_copy = new QCheckBox(centralWidget);
        checkBox_remove_after_copy->setObjectName(QStringLiteral("checkBox_remove_after_copy"));
        checkBox_remove_after_copy->setGeometry(QRect(10, 200, 171, 20));
        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(110, 410, 188, 47));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_for_radioButtons = new QLabel(layoutWidget2);
        label_for_radioButtons->setObjectName(QStringLiteral("label_for_radioButtons"));

        verticalLayout_3->addWidget(label_for_radioButtons);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioButton_freshDate = new QRadioButton(layoutWidget2);
        radioButton_freshDate->setObjectName(QStringLiteral("radioButton_freshDate"));
        radioButton_freshDate->setChecked(false);

        horizontalLayout_2->addWidget(radioButton_freshDate);

        radioButton_allFiles = new QRadioButton(layoutWidget2);
        radioButton_allFiles->setObjectName(QStringLiteral("radioButton_allFiles"));
        radioButton_allFiles->setChecked(true);

        horizontalLayout_2->addWidget(radioButton_allFiles);


        verticalLayout_3->addLayout(horizontalLayout_2);

        copyfiles->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(copyfiles);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        copyfiles->setStatusBar(statusBar);

        retranslateUi(copyfiles);

        QMetaObject::connectSlotsByName(copyfiles);
    } // setupUi

    void retranslateUi(QMainWindow *copyfiles)
    {
        copyfiles->setWindowTitle(QApplication::translate("copyfiles", "Backupper", nullptr));
        Button_Test->setText(QApplication::translate("copyfiles", "Test copiyng", nullptr));
        pushButton->setText(QApplication::translate("copyfiles", "Apply Settings", nullptr));
        ButSetPathTo->setText(QApplication::translate("copyfiles", "SetPathTo", nullptr));
        checkBox_autorun->setText(QApplication::translate("copyfiles", "Autorun with system", nullptr));
        textBrowser->setHtml(QApplication::translate("copyfiles", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Default text</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">only fresh files</span></p></body></html>", nullptr));
        ButSetPathFrom->setText(QApplication::translate("copyfiles", "SetPath From", nullptr));
        label_TO->setText(QApplication::translate("copyfiles", "Directory TO", nullptr));
        label_FROM->setText(QApplication::translate("copyfiles", "Directory FROM", nullptr));
        ButtonSettingsFile->setText(QApplication::translate("copyfiles", "Open settings", nullptr));
        ButtonSaveSettingsIntoFle->setText(QApplication::translate("copyfiles", "Saved settings", nullptr));
        checkBox_systemtray->setText(QApplication::translate("copyfiles", "SystemTray", nullptr));
        label->setText(QApplication::translate("copyfiles", "\320\243\320\264\320\260\320\273\321\217\321\202\321\214 \321\204\320\260\320\271\320\273\321\213 \321\201\321\202\320\260\321\200\321\210\320\265:", nullptr));
        label_2->setText(QApplication::translate("copyfiles", "\320\274\320\265\321\201\321\217\321\206\320\265\320\262", nullptr));
        checkBox_remove_after_copy->setText(QApplication::translate("copyfiles", "Remove files after copy", nullptr));
        label_for_radioButtons->setText(QApplication::translate("copyfiles", "At first time you wont copy:", nullptr));
        radioButton_freshDate->setText(QApplication::translate("copyfiles", "only fresh files", nullptr));
        radioButton_allFiles->setText(QApplication::translate("copyfiles", "all files", nullptr));
    } // retranslateUi

};

namespace Ui {
    class copyfiles: public Ui_copyfiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYFILES_H
