#include "mappoint.h"

MapPoint::MapPoint() = default;

void MapPoint::AddDirectEdge(MapPoint* p, double distance) {
    if (!DirectEdgeFirst) {
		DirectEdgeFirst = new MapEdge;
		DirectEdgeFirst->GetTo() = p;
		DirectEdgeFirst->GetEdgeDistance() = distance;
        return;
    }
    MapEdge* ep = DirectEdgeFirst;
    while (ep->GetNext()) {
        ep = ep->GetNext();
    }
	ep->AddNext(p, distance);
}

void MapPoint::AddEveryEdge(MapPoint* p) {
    if (!EveryEdgeFirst) {
		EveryEdgeFirst = new MapEdge;
		EveryEdgeFirst->GetTo() = p;
        return;
    }
    MapEdge* ep = EveryEdgeFirst;
    while (ep->GetNext()) {
        ep = ep->GetNext();
    }
	ep->AddNext(p);
}

void MapPoint::SetPointPos(int x, int y) {
    this->PointX = x;
    this->PointY = y;
}

std::pair<int, int> MapPoint::GetPointPos() {
    return std::make_pair(PointX, PointY);
}

int MapPoint::GetPointIndex() const {
    return PointIndex;
}

MapEdge* MapPoint::GetDirectEdgeFirst() {
    return DirectEdgeFirst;
}

MapEdge* MapPoint::GetEveryEdgeFirst() {
    return EveryEdgeFirst;
}

double calculateDistance(MapPoint a, MapPoint b) {
    return sqrt((a.GetPointPos().first - b.GetPointPos().first) * (a.GetPointPos().first - b.GetPointPos().first)
        + (a.GetPointPos().second - b.GetPointPos().second) * (a.GetPointPos().second - b.GetPointPos().second));
}
