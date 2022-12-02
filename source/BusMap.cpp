#include "BusMap.h"

BusMap::BusMap(const string& busStopsFile, const string& busLinesFile, const string& organizationsFile)
{
	ifstream fp(busStopsFile);
	if (!fp.is_open())
		throw ("File open error!");
	fp >> BusStopCnt;
	BusStops = new MapPoint* [BusStopCnt + 1];
	Path = new int[BusStopCnt + 1];
	ALLPATH = new int** [2];
	CopyPath = new int[BusStopCnt + 1];
	for (int i = 0; i <= 1; i++)
		ALLPATH[i] = new int* [BusStopCnt + 1];
	for (int i = 0; i <= 1; i++)
		for (int j = 0; j <= BusStopCnt; ++j)
			ALLPATH[i][j] = new int[BusStopCnt + 1];
	for (int i = 1, Pa, b; i <= BusStopCnt; ++i)
	{
		fp >> Pa >> b;
		BusStops[i] = new MapPoint(Pa, b, i);
	}
	fp.close();
	fp.open(busLinesFile);
	if (!fp.is_open())
	{
		throw ("File open error!");
	}
	fp >> BusLineCnt;
	BusLines = new int* [BusLineCnt + 1];
	EachBusLineNum = new int[BusLineCnt + 1];
	for (int i = 1; i <= BusLineCnt; ++i)
	{
		fp >> EachBusLineNum[i];
		BusLines[i] = new int[EachBusLineNum[i] + 1];
	}
	for (int i = 1; i <= BusLineCnt; ++i)
		for (int j = 1; j <= EachBusLineNum[i]; ++j)
			fp >> BusLines[i][j];
	for (int i = 1; i <= BusLineCnt; ++i)
		for (int j = 1; j <= EachBusLineNum[i]; ++j)
			for (int k = j + 1; k <= EachBusLineNum[i]; ++k)
			{
				BusStops[BusLines[i][j]]->AddEveryEdge(BusStops[BusLines[i][k]]);
				BusStops[BusLines[i][k]]->AddEveryEdge(BusStops[BusLines[i][j]]);
			}
	for (int i = 1; i <= BusLineCnt; ++i)
		for (int j = 1; j <= EachBusLineNum[i] - 1; ++j)
		{
			double dis = calculateDistance(*BusStops[BusLines[i][j]], *BusStops[BusLines[i][j + 1]]);
			BusStops[BusLines[i][j]]->AddDirectEdge(BusStops[BusLines[i][j + 1]], dis);
			BusStops[BusLines[i][j + 1]]->AddDirectEdge(BusStops[BusLines[i][j]], dis);
		}
	Path[0] = 0;
	fp.close();
	fp.open(organizationsFile);
	if (!fp.is_open())
		throw ("File open error!");
	string temp;
	while (fp >> temp)
	{
		OrganizationNames[++OrganizationsCnt] = temp;
		fp >> OrganizationPos[OrganizationsCnt].first;
		fp.get();
		fp >> OrganizationPos[OrganizationsCnt].second;
	}
	fp.close();
	for (int i = 0; i <= 1; i++)
	{
		if (i == 1)
			a = false;
		for (int j = 1; j <= BusStopCnt; ++j)
		{
			int* path = FindPath(j);
			for (int k = 1; k <= BusStopCnt; ++k)
				ALLPATH[i][j][k] = path[k];
		}
		a = true;
	}
}

int* BusMap::FindPath(int start_index)
{
	queue<pair<int, int>> myQueue;
	int* dis = new int[BusStopCnt + 1];
	for (int i = 1; i <= BusStopCnt; i++)
		dis[i] = 0x3f3f3f3f;
	dis[start_index] = 0;
	CopyPath[start_index] = 0;
	myQueue.push(make_pair(0, start_index));
	while (!myQueue.empty())
	{
		int disNow = myQueue.front().first;
		int indNow = myQueue.front().second;
		myQueue.pop();
		if (dis[indNow] != disNow)
			continue;
		if (a)
			for (MapEdge* ep = BusStops[indNow]->GetDirectEdgeFirst(); ep; ep = ep->GetNext())
			{
				int idx = ep->GetTo()->GetPointIndex();
				if (dis[idx] > dis[indNow] + ep->GetEdgeDistance())
				{
					dis[idx] = dis[indNow] + ep->GetEdgeDistance();
					myQueue.push(make_pair(dis[idx], idx));
					CopyPath[idx] = indNow;
				}
			}
		else
			for (MapEdge* ep = BusStops[indNow]->GetEveryEdgeFirst(); ep; ep = ep->GetNext())
			{
				int idx = ep->GetTo()->GetPointIndex();
				if (dis[idx] > dis[indNow] + ep->GetEdgeDistance())
				{
					dis[idx] = dis[indNow] + ep->GetEdgeDistance();
					myQueue.push(make_pair(dis[idx], idx));
					CopyPath[idx] = indNow;
				}
			}
	}
	delete[] dis;
	return CopyPath;
}

int* BusMap::findDirectPath(int start_index)
{
	return ALLPATH[0][start_index];
}

int* BusMap::findEveryPath(int start_index, int end_index)
{
	int* path = ALLPATH[1][start_index];
	auto* busLinesSet = new set<int>[BusLineCnt + 1];
	for (int i = 1; i <= BusLineCnt; ++i)
		for (int j = 1; j <= EachBusLineNum[i]; ++j)
			busLinesSet[i].insert(BusLines[i][j]);
	int pointIndex = end_index;
	while (path[pointIndex])
	{
		for (int i = 1; i <= BusLineCnt; ++i)
		{
			if (busLinesSet[i].count(path[pointIndex]) && busLinesSet[i].count(pointIndex))
			{
				int start = 1;
				int end = 1;
				while (BusLines[i][start] != path[pointIndex])
					++start;
				while (BusLines[i][end] != pointIndex)
					++end;
				if (start < end)
					for (int j = end; j > start; --j)
						Path[BusLines[i][j]] = BusLines[i][j - 1];
				else
					for (int j = end; j < start; ++j)
						Path[BusLines[i][j]] = BusLines[i][j + 1];
			}
		}
		pointIndex = path[pointIndex];
	}
	Path[start_index] = 0;
	return Path;
}

BusMap::~BusMap()
{
	for (int i = 1; i <= EachBusLineNum[i]; ++i)
	{
		delete[] BusLines[i];
	}
	delete[] EachBusLineNum;
	delete[] BusLines;
	delete[] BusStops;
	delete[] Path;
}
