//
// Created by zxc02 on 2022/10/20.
// Time is 17:23
#include "Global.h"
#include "BusMap.h"
#include "MyLabel.h"

#ifndef HUSTMAP_UI_MAINWINDOW_H
#define HUSTMAP_UI_MAINWINDOW_H
QT_BEGIN_NAMESPACE
class Ui_MainWindow
{
public:
	QWidget* MyWidget{};
	QVBoxLayout* VLayout{}, * RightMenuVBox{}, * RightMenuVLayout{}, * RightMenuButtonsLayout{};
	QHBoxLayout* TipLayout{}, * HLayout{}, * SearchHBox{};
	QGridLayout* MainLayout{};
	QFrame* MapFrame{}, * RightMenuButtons{}, * RightMenu{}, * RightMenuTop{}, * RightMenuContainers{};
	QLabel* Tip{}, * SearchTip{}, * StartPlaceTip{}, * EndPlaceTip{};
	QLineEdit* LineEdit{};
	QCheckBox* MinTrans{}, * Nearest{};
	QPushButton* SearchButton{}, * FindButton{};
	QComboBox* StartListingTag{}, * EndListingTag{};
	MyLabel* Map{};
	void setupUi(QMainWindow* MainWindow);
};
namespace Ui
{
	class MainWindow : public Ui_MainWindow
	{
	};
} // namespace Ui

QT_END_NAMESPACE

#endif //HUSTMAP_UI_MAINWINDOW_H
