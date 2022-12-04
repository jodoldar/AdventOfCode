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
            int iPos = oReturnGraph[iLineX].size() - iInitialYSize;
            int iStartSize = oReturnGraph[iLineX].size();

            while (iPos < iStartSize)
            {
               oReturnGraph[iLineX].push_back(oReturnGraph[iLineX][iPos]);
               oReturnGraph[iLineX].back().weight++;
               oReturnGraph[iLineX].back().Y = iPos + iInitialYSize;
               if (oReturnGraph[iLineX].back().weight>9)
                oReturnGraph[iLineX].back().weight = 1;
               iPos++;
            }
        }
    }

    /* Expand X 4 times */
    for (size_t i = 0; i < 4; i++)
    {
        int iPos = oReturnGraph.size() - iInitialXSize;
        int iStartSize = oReturnGraph.size();

        for (size_t iLineX = iPos; iLineX < iStartSize; iLineX++)
        {
            oReturnGraph.push_back({});

            for (auto &&pt : oReturnGraph[iLineX])
            {
                oReturnGraph.back().push_back(pt);
                oReturnGraph.back().back().X = iLineX+iInitialXSize;
                oReturnGraph.back().back().weight<9 ? oReturnGraph.back().back().weight++ : oReturnGraph.back().back().weight=1;
            }
        }
    }

    return oReturnGraph;
}

int main(int argc, char const *argv[])
{
    vector<vector<Point>> oGraph;
    vector<vector<Point>> oGraphBig;
    queue<Point> qPointsToCheck;
    Point pLocal;
    string spaces{80, ' '};
    int ATTEMPTS = 3;

    if (!siReadAndProcessInput("input.txt", oGraph))
    {
        for (auto &&line : oGraph)
        {
            for (auto &&elem : line)
                cout << elem.weight;
            cout << endl;
        }

        oGraph = expandGraph(oGraph);
        cout << "New graph size is " << oGraph.size() << "x" << oGraph[0].size() << endl;

        oGraph[0][0].distance = 0;
        qPointsToCheck.push(oGraph[0][0]);

        for (size_t i = 0; i < ATTEMPTS; i++)
        {
            for (size_t iX = 0; iX < oGraph.size(); iX++)
            {
                for (size_t iY = 0; iY < oGraph[iX].size(); iY++)
                {
                    cout << "\r" << spaces << "\rIn position: " << iX << "," << iY << flush;

                    if (iY < oGraph[iX].size()-1 && oGraph[iX][iY].distance + oGraph[iX][iY+1].weight < oGraph[iX][iY+1].distance)
                        oGraph[iX][iY+1].distance = oGraph[iX][iY].distance + oGraph[iX][iY+1].weight;

                    if (iX < oGraph.size()-1 && oGraph[iX][iY].distance + oGraph[iX+1][iY].weight < oGraph[iX+1][iY].distance)
                        oGraph[iX+1][iY].distance = oGraph[iX][iY].distance + oGraph[iX+1][iY].weight;

                    if (iX > 0 && oGraph[iX][iY].distance + oGraph[iX-1][iY].weight < oGraph[iX-1][iY].distance)
                        oGraph[iX-1][iY].distance = oGraph[iX][iY].distance + oGraph[iX-1][iY].weight;

                    if (iY > 0 && oGraph[iX][iY].distance + oGraph[iX][iY-1].weight < oGraph[iX][iY-1].distance)
                        oGraph[iX][iY-1].distance = oGraph[iX][iY].distance + oGraph[iX][iY-1].weight;
                }
            }
        }

        cout << "\nDistance is " << oGraph.back().back().distance << endl;
        cout << "At start is " << oGraph[0][0].distance << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}