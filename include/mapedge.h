#ifndef MAPEDGE_H
#define MAPEDGE_H
#include "mappoint.h"
#include "Global.h"
class MapPoint;

class MapEdge {

    MapPoint* To = nullptr;
    MapEdge* Next = nullptr;
    double EdgeDistance = 0.0;

public:
    MapEdge();

    // setters:
    void AddNext(MapPoint* to, double distance = 1.0);

    // getters:
    MapEdge*& GetNext();

    MapPoint*& GetTo();

    double& GetEdgeDistance();

};

#endif // MAPEDGE_H
