//
// Created by zxc02 on 2022/10/20.
// Time is 17:26

#include "Global.h"
#include "MyWindow.h"


void Ui_MainWindow::setupUi(QMainWindow* MainWindow)
{
	if (MainWindow->objectName().isEmpty())
		MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
	MainWindow->setFixedSize(2000, 894);
	MainWindow->move(0, 0);
	MyWidget = new QWidget(MainWindow);
	QString qss;
	QFile qssFile("../src/myQss.qss");
	qssFile.open(QFile::ReadOnly);
	if (qssFile.isOpen())
	{
		qss = QLatin1String(qssFile.readAll());
		MyWidget->setStyleSheet(qss);
		qssFile.close();
	}
	MyWidget->setObjectName(QString::fromUtf8("MyWidget"));
	HLayout = new QHBoxLayout(MyWidget);
	TipLayout = new QHBoxLayout();
	MainLayout = new QGridLayout();
	MapFrame = new QFrame(MyWidget);
	MapFrame->setFixedSize(1676, 820);
	Map = new MyLabel(MapFrame);
	MainLayout->addWidget(MapFrame);
	VLayout = new QVBoxLayout();
	HLayout->addLayout(VLayout);
	Tip = new QLabel(MyWidget);
	Tip->setMaximumSize(1677777, 80);
	Tip->setText(
			QString("Tip: Please select the ending point (Red) and starting point (Blue) by clicking in the order of priority"));
	TipLayout->addWidget(Tip);
	RightMenu = new QFrame(MyWidget);
	RightMenu->setFrameShape(QFrame::NoFrame);
	RightMenu->setObjectName(QString("RightMenu"));
	RightMenuVBox = new QVBoxLayout(RightMenu);
	RightMenuTop = new QFrame(RightMenu);
	RightMenuTop->setMaximumSize(QSize(16777215, 3));
	RightMenuTop->setFrameShape(QFrame::NoFrame);
	RightMenuTop->setFrameShadow(QFrame::Raised);
	RightMenuTop->setObjectName(QString("RightMenuTop"));
	RightMenuVBox->addWidget(RightMenuTop);
	RightMenuContainers = new QFrame(RightMenu);
	RightMenuContainers->setObjectName(QString("RightMenuContainers"));
	RightMenuVLayout = new QVBoxLayout(RightMenuContainers);
	RightMenuVLayout->setObjectName(QString("RightMenuVLayout"));
	RightMenuButtons = new QFrame(RightMenuContainers);
	RightMenuButtons->setObjectName(QString("RightMenuButtons"));
	RightMenuButtonsLayout = new QVBoxLayout(RightMenuButtons);
	RightMenuButtonsLayout->setObjectName("RightMenuButtonsLayout");
	MinTrans = new QCheckBox(RightMenu);
	Nearest = new QCheckBox(RightMenu);
	Nearest->setChecked(true);
	Nearest->setObjectName(QString("Nearest"));
	MinTrans->setObjectName(QString("MinTrans"));
	MinTrans->setText(QString("MinTrans"));
	Nearest->setText(QString("Nearest"));
	MinTrans->setMinimumSize(50, 30);
	Nearest->setMinimumSize(50, 30);
	SearchTip = new QLabel(RightMenu);
	SearchTip->setObjectName("SearchTip");
	SearchTip->setText("????????????");
	SearchHBox = new QHBoxLayout();
	LineEdit = new QLineEdit(RightMenu);
	LineEdit->setMinimumSize(130, 30);
	SearchButton = new QPushButton(RightMenu);
	SearchButton->setMinimumSize(40, 30);
	SearchButton->setText("??????");
	SearchHBox->addWidget(LineEdit);
	SearchHBox->addWidget(SearchButton);
	StartPlaceTip = new QLabel(RightMenu);
	StartPlaceTip->setObjectName(QString("StartPlaceTip"));
	EndPlaceTip = new QLabel(RightMenu);
	EndPlaceTip->setObjectName(QString("EndPlaceTip"));
	StartPlaceTip->setText(QString("?????????"));
	EndPlaceTip->setText(QString("??????"));
	StartListingTag = new QComboBox(RightMenu);
	StartListingTag->addItem(QString("??????????????????"));
	StartListingTag->addItem(QString("????????????"));
	StartListingTag->addItem(QString("??????????????????"));
	StartListingTag->addItem(QString("???????????????"));
	EndListingTag = new QComboBox(RightMenu);
	EndListingTag->addItem(QString("??????????????????"));
	EndListingTag->addItem(QString("????????????"));
	EndListingTag->addItem(QString("??????????????????"));
	EndListingTag->addItem(QString("???????????????"));
	FindButton = new QPushButton();
	FindButton->setText(QString("??????"));
	RightMenuButtonsLayout->addWidget(MinTrans);
	RightMenuButtonsLayout->addWidget(Nearest);
	RightMenuButtonsLayout->addWidget(SearchTip);
	RightMenuButtonsLayout->addLayout(SearchHBox);
	RightMenuButtonsLayout->addWidget(StartPlaceTip);
	RightMenuButtonsLayout->addWidget(StartListingTag);
	RightMenuButtonsLayout->addWidget(EndPlaceTip);
	RightMenuButtonsLayout->addWidget(EndListingTag);
	RightMenuButtonsLayout->addWidget(FindButton, Qt::AlignmentFlag::AlignCenter);
	RightMenuVLayout->addWidget(RightMenuButtons, 0, Qt::AlignmentFlag::AlignTop);
	RightMenuVBox->addWidget(RightMenuContainers);
	VLayout->addLayout(TipLayout);
	VLayout->addLayout(MainLayout);
	HLayout->addWidget(RightMenu);
	MyWidget->setLayout(HLayout);
	MainWindow->setCentralWidget(MyWidget);
}