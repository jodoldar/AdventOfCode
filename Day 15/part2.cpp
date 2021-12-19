/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 15 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <cctype>
#include <climits>
#include <iostream>
#include <fstream>
#include <list>
#include <numeric>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "../Common/utils.hpp"

using namespace std;

const string RED_COLOR = "\033[31m";
const string RESET_COLOR = "\033[0m";

class Point
{
public:
    int X, Y;
    int weight, distance;
    bool bVisited;
    Point* orig;

    Point(){};
    Point(int x, int y, int w): X(x), Y(y), weight(w) {
        bVisited = false;
        distance = INT_MAX;
        orig = nullptr;
    };

    vector<Point> getAdjacents(vector<vector<Point>> oGraph);

    friend ostream& operator<<(ostream& os, const Point pt);
};

vector<Point> Point::getAdjacents(vector<vector<Point>> oGraph)
{
    vector<Point> vReturnVec;

    if (X < oGraph.size()-1)
        vReturnVec.push_back(oGraph[X+1][Y]);

    if (Y < oGraph[0].size()-1)
        vReturnVec.push_back(oGraph[X][Y+1]);

    return vReturnVec;
}

ostream& operator<<(ostream& os, const Point pt)
{
    os << "[" << pt.X << "," << pt.Y << "] -> " << pt.weight;
    return os;
}

short int siReadAndProcessInput(string sFileName, vector<vector<Point>> &oGraph)
{
    ifstream fInputFile;
    string sLine;
    int iLineX = 0, iLineY = 0;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
                continue;

            oGraph.push_back({});
            iLineY = 0;

            for (auto &&letter : sLine)
            {
                oGraph.back().push_back(Point(iLineX, iLineY++, letter - '0'));
            }

            iLineX++;
        }

        fInputFile.close();
    }
    else
    {
        cout << "Error opening " << sFileName << " file." << endl;
        return 1;
    }

    return 0;
}

vector<vector<Point>> expandGraph(vector<vector<Point>> oGraph)
{
    int iInitialXSize = oGraph.size();
    int iInitialYSize = oGraph[0].size();
    vector<vector<Point>> oReturnGraph = oGraph;

    /* Expand Y 4 times */
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t iLineX = 0; iLineX < iInitialXSize; iLineX++)
        {
            auto it = oGraph[iLineX].end() - iInitialYSize;

            while (it != oGraph[iLineX].end())
            {
               oReturnGraph[iLineX].push_back(*it);
               oReturnGraph[iLineX].back().weight<(9-i) ? oReturnGraph[iLineX].back().weight+=(i+1) : oReturnGraph[iLineX].back().weight=i;
               it++;
            }
        }
    }

    return oReturnGraph;
}

int main(int argc, char const *argv[])
{
    vector<vector<Point>> oGraph;
    vector<vector<Point>> oGraphBig;
    list<Point*> qPointsToCheck;
    Point* pLocal;

    if (!siReadAndProcessInput("input_sample.txt", oGraph))
    {
        oGraphBig = expandGraph(oGraph);

        for (auto &&line : oGraphBig)
        {
            for (auto &&elem : line)
                cout << elem.weight;
            cout << endl;
        }

        oGraph[0][0].distance = 0;
        qPointsToCheck.push_back(&oGraph[0][0]);

        while (!qPointsToCheck.empty())
        {
            pLocal = qPointsToCheck.front();
            //cout << "Processing point " << *pLocal << endl;

            for (auto &&point : (*pLocal).getAdjacents(oGraph))
            {
                //cout << "Checking for point " << point << endl;
                if (oGraph[pLocal->X][pLocal->Y].distance + point.weight < point.distance)
                {
                    oGraph[point.X][point.Y].distance = oGraph[pLocal->X][pLocal->Y].distance + point.weight;
                    //cout << "Point " << point << " new distance is " << oGraph[point.X][point.Y].distance << endl;
                    oGraph[point.X][point.Y].orig = &oGraph[pLocal->X][pLocal->Y];
                }

                if (find_if(qPointsToCheck.begin(), qPointsToCheck.end(), [point](Point* p){return p->X==point.X && p->Y==point.Y;}) == qPointsToCheck.end())
                {
                    //cout << "Added " << &oGraph[point.X][point.Y] << " to the queue" << endl;
                    qPointsToCheck.push_back(&oGraph[point.X][point.Y]);
                }
            }

            qPointsToCheck.pop_front();
        }

        cout << "Distance is " << oGraph.back().back().distance << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}