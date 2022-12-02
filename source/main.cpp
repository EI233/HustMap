#include "Global.h"
#include "mainwindow.h"
bool a = true;
int main(int argc, char* argv[])
{
	QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
	QApplication application(argc, argv);
	MainWindow w;
	w.setWindowIcon(QIcon("../src/hust.png"));
	w.setWindowTitle("Hust Map");
	w.show();
	return QApplication::exec();
}
