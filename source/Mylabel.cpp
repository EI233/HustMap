//
// Created by zxc02 on 2022/10/20.
// Time is 21:51
#include "Global.h"
#include "MyLabel.h"

MyLabel::MyLabel(QWidget* parent) : QLabel(parent)
{
	StartPos = QPoint(0, 0);
	EndPos = QPoint(0, 0);
	RIsClicked = false;
	LIsClicked = false;
	PBusMap = new BusMap("../src/stops.txt",
			"../src/lines.txt",
			"../src/Organization.txt");
	this->setFixedSize(1676, 820);
}

void MyLabel::paintEvent(QPaintEvent*)
{
	QPainter mapPainter(this);
	QRect MapRect = this->frameRect();
	mapPainter.drawImage(MapRect, QImage("../src/hustMap.bmp"));
	MapRect.translate(this->pos());
	QPen mapPen;
	mapPainter.setBrush(QColor(0, 0, 0));
	for (int i = 1; i <= PBusMap->GetBusStopCnt(); ++i)
	{
		MapPoint* _p = PBusMap->GetBusStops()[i];
		mapPen.setWidth(5);
		mapPainter.setPen(mapPen);
		mapPainter.drawEllipse(_p->GetPointPos().first - 5, _p->GetPointPos().second - 5, 10, 10);
	}
	mapPainter.setBrush(Qt::NoBrush);
	mapPen.setWidth(4);
	mapPen.setColor(Qt::darkCyan);
	mapPen.setStyle(Qt::DashDotDotLine);
	mapPainter.setPen(mapPen);
	for (int i = 1; i <= PBusMap->GetBusLineCnt(); ++i)
	{
		for (int j = 1; j < PBusMap->GetEachBusLineNum()[i]; ++j)
		{
			MapPoint* p1 = PBusMap->GetBusStops()[PBusMap->GetBusLines()[i][j]];
			MapPoint* p2 = PBusMap->GetBusStops()[PBusMap->GetBusLines()[i][j + 1]];
			mapPainter.drawLine(p1->GetPointPos().first, p1->GetPointPos().second, p2->GetPointPos().first,
					p2->GetPointPos().second);
		}
	}
	if (LIsClicked)
		mapPainter.drawImage(StartPos.x() - 16, StartPos.y() - 43, QImage("../src/Dot-Blue.png"));
	if (RIsClicked)
		mapPainter.drawImage(EndPos.x() - 16, EndPos.y() - 43, QImage("../src/Dot-Red.png"));
	int temp = EndPointIndex;
	if (!RIsClicked||!LIsClicked)
		return;
	mapPen.setWidth(5);
	mapPen.setColor(Qt::blue);
	mapPen.setStyle(Qt::DashDotDotLine);
	mapPainter.setPen(mapPen);
	mapPainter.setBrush(Qt::NoBrush);
	mapPainter.drawLine(EndPos.x(), EndPos.y(), PBusMap->GetBusStops()[temp]->GetPointPos().first,
			PBusMap->GetBusStops()[temp]->GetPointPos().second);
	while (Ans[temp])
	{
		mapPainter.drawLine(PBusMap->GetBusStops()[temp]->GetPointPos().first,
				PBusMap->GetBusStops()[temp]->GetPointPos().second,
				PBusMap->GetBusStops()[Ans[temp]]->GetPointPos().first,
				PBusMap->GetBusStops()[Ans[temp]]->GetPointPos().second);
		temp = Ans[temp];
	}
	mapPainter.drawLine(StartPos.x(), StartPos.y(), PBusMap->GetBusStops()[temp]->GetPointPos().first,
			PBusMap->GetBusStops()[temp]->GetPointPos().second);
	if (StartPos.x() != 0)
		mapPainter.drawImage(StartPos.x() - 16, StartPos.y() - 43, QImage("../src/Dot-Blue.png"));
	if (EndPos.y() != 0)
		mapPainter.drawImage(EndPos.x() - 16, EndPos.y() - 43, QImage("../src/Dot-Red.png"));
}

void MyLabel::timerEvent(QTimerEvent* event)
{
	StartPointIndex = 0;
	EndPointIndex = 0;
	StartPos.setX(0);
	StartPos.setY(0);
	EndPos.setX(0);
	EndPos.setY(0);
	killTimer(TimerId);
	update();
}

void MyLabel::mousePressEvent(QMouseEvent* event)
{
	bool flag = true;
	if (event->button() == Qt::RightButton)
	{
		RIsClicked = true;
		flag = false;
	}
	else LIsClicked = true;
	QPoint mousePoint = event->pos();
	MapPoint mousePointTemp;
	mousePointTemp.SetPointPos(mousePoint.x(), mousePoint.y());
	double minDistance = 9999999.99;
	for (int i = 1; i <= PBusMap->GetBusStopCnt(); ++i)
	{
		double temp = calculateDistance(mousePointTemp, *PBusMap->GetBusStops()[i]);
		if (temp < minDistance)
		{
			if (flag)
			{
				minDistance = temp;
				StartPointIndex = i;
			}
			else
			{
				minDistance = temp;
				EndPointIndex = i;
			}
		}
	}
	if (LIsClicked&&!RIsClicked)
	{
		StartPos = event->pos();
		repaint(this->topLevelWidget()->contentsRect());
		killTimer(TimerId);
	}
	else if (!LIsClicked&&RIsClicked)
	{
		EndPos = event->pos();
		repaint(this->topLevelWidget()->contentsRect());
		killTimer(TimerId);
	}
	else if (flag){
		StartPos = event->pos();
	}
	else EndPos = event->pos();
	if (LIsClicked && RIsClicked)
	{
		if (a)
			Ans = PBusMap->findDirectPath(StartPointIndex);
		else
			Ans = PBusMap->findEveryPath(StartPointIndex, EndPointIndex);
		repaint(this->topLevelWidget()->contentsRect());
		TimerId = startTimer(5000);
		StartPointIndex = 0;
		EndPointIndex = 0;
		StartPos.setX(0);
		StartPos.setY(0);
		EndPos.setX(0);
		EndPos.setY(0);
		RIsClicked = false;
		LIsClicked = false;
	}
}
