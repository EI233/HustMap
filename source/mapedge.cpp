#include "mapedge.h"

MapEdge::MapEdge() = default;

void MapEdge::AddNext(MapPoint *to, double distance) {
	Next = new MapEdge;
	Next->To = to;
	Next->EdgeDistance = distance;
}

MapEdge*& MapEdge::GetNext() {
    return Next;
}

MapPoint*& MapEdge::GetTo() {
    return To;
}

double& MapEdge::GetEdgeDistance() {
    return EdgeDistance;
}
