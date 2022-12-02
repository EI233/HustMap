//
// Created by zxc02 on 2022/10/20.
// Time is 21:42
#include "Global.h"
#include "BusMap.h"

#ifndef HUSTMAP_MYMAP_H
#define HUSTMAP_MYMAP_H
class MyLabel: public QLabel{
public:
	BusMap* PBusMap{};
	int StartPointIndex = 0;
	int EndPointIndex = 0;
	int* Ans{};
	int TimerId = 0;
	QPoint StartPos;
	QPoint EndPos;
	bool RIsClicked = false;
	bool LIsClicked=false;
	explicit MyLabel(QWidget *parent = nullptr);

private:
	void paintEvent(QPaintEvent *) override;
	void mousePressEvent(QMouseEvent* event) override;

	void timerEvent(QTimerEvent* event) override;

};
#endif //HUSTMAP_MYMAP_H
