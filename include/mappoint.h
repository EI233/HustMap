#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include "mapedge.h"
#include "Global.h"

class MapEdge;

class MapPoint
{

private:
	int PointX = 0;
	int PointY = 0;
	int PointIndex = 0;
	MapEdge* DirectEdgeFirst = nullptr;
	MapEdge* EveryEdgeFirst = nullptr;

public:
	MapPoint();

	MapPoint(int pointX, int pointY, int pointIndex) : PointX(pointX), PointY(pointY), PointIndex(pointIndex)
	{
	};

	// getters:
	int GetPointIndex() const;

	MapEdge* GetDirectEdgeFirst();

	MapEdge* GetEveryEdgeFirst();

	std::pair<int, int> GetPointPos();

	// setters:
	void SetPointPos(int x, int y);

	void AddDirectEdge(MapPoint* p, double distance);

	void AddEveryEdge(MapPoint* p);

};

double calculateDistance(MapPoint a, MapPoint b);

#endif // MAPPOINT_H
