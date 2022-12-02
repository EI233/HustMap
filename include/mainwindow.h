#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Global.h"
#include "BusMap.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;

private:
	Ui::MainWindow *ui;
	void ChangeState();
	void Func();
	void findPointByName(const QString &s);
	void findPoint();
};
int StringMatch(string a, string b);
#endif // MAINWINDOW_H
