#ifndef BusMap_H
#define BusMap_H
#include <string>
#include <fstream>
#include <queue>
#include "mappoint.h"
#include "Global.h"

using namespace std;

class BusMap
{

private:
    int BusStopCnt = 0;                  // ������վ����
    int BusLineCnt = 0;                  // ��������·��
    int OrganizationsCnt = 0;            // ������λ��
    string OrganizationNames[100];       // ������λ��
    pair<int, int> OrganizationPos[100]; // ��֯
    int *EachBusLineNum = nullptr;
    int **BusLines = nullptr;
    MapPoint **BusStops = nullptr;
    int *Path = nullptr;
    int *CopyPath = nullptr;
    int ***ALLPATH;

public:
    BusMap(const string &busStopsFile, const string &busLinesFile, const string &organizationsFile);
    int GetBusLineCnt() const
    {
        return BusLineCnt;
    }

    int **GetBusLines()
    {
        return BusLines;
    }

    int *GetEachBusLineNum()
    {
        return EachBusLineNum;
    }

    int GetBusStopCnt() const
    {
        return BusStopCnt;
    }

    MapPoint **GetBusStops()
    {
        return BusStops;
    }

    int GetOrganizationsCnt() const
    {
        return OrganizationsCnt;
    }

    string *GetOrganizationNames()
    {
        return OrganizationNames;
    }

    pair<int, int> *GetOrganizationPos()
    {
        return OrganizationPos;
    }
    int *findDirectPath(int start_index);
    int *FindPath(int start_index);
    int *findEveryPath(int start_index, int end_index);
    ~BusMap();
};

#endif // BusMap_H
