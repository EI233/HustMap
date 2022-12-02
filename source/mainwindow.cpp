#include "mainwindow.h"
#include "MyWindow.h"
#include "BusMap.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->MinTrans, &QCheckBox::clicked, this, &MainWindow::ChangeState);
	connect(ui->Nearest, &QCheckBox::clicked, this, &MainWindow::ChangeState);
	connect(ui->SearchButton, &QPushButton::clicked, this, &MainWindow::findPoint);
	connect(ui->FindButton, &QPushButton::clicked, this, &MainWindow::Func);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::ChangeState()
{
	QObject *S = this->sender();
	if (S->objectName() == QString("Nearest"))
	{
		ui->MinTrans->setChecked(false);
		a = true;
	}
	else
	{
		ui->Nearest->setChecked(false);
		a = false;
	}
}
void MainWindow::findPoint()
{
	findPointByName(ui->LineEdit->text());
}

void MainWindow::findPointByName(const QString &s)
{
	string pointName = s.toStdString();
	if (pointName.empty())
		return;
	else
	{
		int maxCnt;
		int ansIndex = 0;
		int max = 0;
		for (int i = 1; i <= ui->Map->PBusMap->GetOrganizationsCnt(); ++i)
		{
			maxCnt = StringMatch(ui->Map->PBusMap->GetOrganizationNames()[i], pointName);
			if (maxCnt > max)
			{
				max = maxCnt;
				ansIndex = i;
			}
		}
		if (ansIndex == 0)
			return;
		if (!ui->Map->LIsClicked)
		{
			ui->Map->killTimer(ui->Map->TimerId);
			ui->Map->LIsClicked = true;
			ui->Map->StartPos.setX(ui->Map->PBusMap->GetOrganizationPos()[ansIndex].first);
			ui->Map->StartPos.setY(ui->Map->PBusMap->GetOrganizationPos()[ansIndex].second);
			MapPoint startPointTemp;
			startPointTemp.SetPointPos(ui->Map->StartPos.x(), ui->Map->StartPos.y());
			double minDistance = 9999999.99;
			for (int i = 1; i <= ui->Map->PBusMap->GetBusStopCnt(); ++i)
			{
				double temp = calculateDistance(startPointTemp, *ui->Map->PBusMap->GetBusStops()[i]);
				if (temp < minDistance)
				{
					minDistance = temp;
					ui->Map->StartPointIndex = i;
				}
			}
			repaint(ui->Map->contentsRect());
		}
		else
		{
			ui->Map->RIsClicked = true;
			ui->Map->EndPos.setX(ui->Map->PBusMap->GetOrganizationPos()[ansIndex].first);
			ui->Map->EndPos.setY(ui->Map->PBusMap->GetOrganizationPos()[ansIndex].second);
			MapPoint endPointTemp;
			endPointTemp.SetPointPos(ui->Map->EndPos.x(), ui->Map->EndPos.y());
			double minDistance = 9999999.99;
			for (int i = 1; i <= ui->Map->PBusMap->GetBusStopCnt(); ++i)
			{
				double temp = calculateDistance(endPointTemp, *ui->Map->PBusMap->GetBusStops()[i]);
				if (temp < minDistance)
				{
					minDistance = temp;
					ui->Map->EndPointIndex = i;
				}
			}
			if (a)
				ui->Map->Ans = ui->Map->PBusMap->findDirectPath(ui->Map->StartPointIndex);
			else
				ui->Map->Ans = ui->Map->PBusMap->findEveryPath(ui->Map->StartPointIndex, ui->Map->EndPointIndex);
			repaint(ui->Map->contentsRect());
			ui->Map->TimerId = ui->Map->startTimer(5000);
			ui->Map->StartPointIndex = 0;
			ui->Map->EndPointIndex = 0;
			ui->Map->LIsClicked = false;
			ui->Map->RIsClicked = false;
		}
	}
}

void MainWindow::Func()
{
	ui->Map->LIsClicked = false;
	ui->Map->RIsClicked = false;
	findPointByName(ui->StartListingTag->currentText());
	findPointByName(ui->EndListingTag->currentText());
}
int StringMatch(string basicString, string targetString)
{
	int cnt = 0;
	for (int i = 0; i < targetString.length(); i += 3)
	{
		for (int j = 0; j < basicString.length(); j += 3)
		{
			bool flag = true;
			if (i + 2 < targetString.length() && j + 2 < basicString.length())
			{
				for (int k = 0; k < 3; ++k)
				{
					if (basicString[j + k] != targetString[i + k])
					{
						flag = false;
						break;
					}
				}
			}
			if (flag)
			{
				cnt++;
				break;
			}
		}
	}
	return cnt;
}