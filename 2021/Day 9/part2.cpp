/**
 * @file part2.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 9 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
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

    Point(){};
    Point(int x, int y): X(x), Y(y) {};
};

class Basin
{
public:
    vector<Point> points;
    bool isComplete;

    Basin(){};
    Basin(Point p){
        points.push_back(p);
        isComplete = false;
    }

    bool isInBasin(Point p);
    void expand(vector<vector<int>> vGroundMap);
    friend bool operator>(const Basin& l, const Basin& r);
};

bool Basin::isInBasin(Point p)
{
    return (find_if(points.begin(), points.end(), [p](Point pIn){return p.X==pIn.X && p.Y==pIn.Y;}) != points.end());
}

void Basin::expand(vector<vector<int>> vGroundMap)
{
    int iStartPoints = points.size();

    for (size_t i = 0; i < iStartPoints; i++)
    {
        auto oPoint = points[i];

        /* Go up */
        if ((oPoint.X > 0) && (vGroundMap[oPoint.X-1][oPoint.Y]!=9) && !this->isInBasin(Point(oPoint.X-1, oPoint.Y)))
            points.push_back(Point(oPoint.X-1, oPoint.Y));

        /* Go down */
        if ((oPoint.X < vGroundMap.size()-1) && (vGroundMap[oPoint.X+1][oPoint.Y]!=9) && !this->isInBasin(Point(oPoint.X+1, oPoint.Y)))
            points.push_back(Point(oPoint.X+1, oPoint.Y));
        
        /* Go left */
        if ((oPoint.Y > 0) && (vGroundMap[oPoint.X][oPoint.Y-1]!=9) && !this->isInBasin(Point(oPoint.X, oPoint.Y-1)))
            points.push_back(Point(oPoint.X, oPoint.Y-1));
        
        /* Go right */
        if ((oPoint.Y < vGroundMap[0].size()-1) && (vGroundMap[oPoint.X][oPoint.Y+1]!=9) && !this->isInBasin(Point(oPoint.X, oPoint.Y+1)))
            points.push_back(Point(oPoint.X, oPoint.Y+1));        
    }

    if (points.size() == iStartPoints)
        isComplete = true;
}

bool operator>(const Basin& l, const Basin& r)
{
    return l.points.size() > r.points.size();
}

short int siReadAndProcessInput(string sFileName, vector<vector<int>> &vGroundMap)
{
    ifstream fInputFile;
    string sLine;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
                continue;

            vGroundMap.push_back(vector<int>());

            for (auto &&letter : sLine)
            {
                vGroundMap.back().push_back(letter - '0');
            }
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

vector<Point> getAllMinimums(vector<vector<int>> vGroundMap)
{
    vector<Point> vTempPoints;
    int iMaxRow = vGroundMap.size()-1;
    int iMaxCol = vGroundMap[0].size()-1;

    /* Check corners */
    if ((vGroundMap[0][0] < vGroundMap[0][1]) && (vGroundMap[0][0] < vGroundMap[1][0]))
        vTempPoints.push_back(Point(0, 0));

    if ((vGroundMap[iMaxRow][0] < vGroundMap[iMaxRow][1]) && (vGroundMap[iMaxRow][0] < vGroundMap[iMaxRow-1][0]))
        vTempPoints.push_back(Point(iMaxRow, 0));

    if ((vGroundMap[0][iMaxCol] < vGroundMap[0][iMaxCol-1]) && (vGroundMap[0][iMaxCol] < vGroundMap[1][iMaxCol]))
        vTempPoints.push_back(Point(0, iMaxCol));

    if ((vGroundMap[iMaxRow][iMaxCol] < vGroundMap[iMaxRow-1][iMaxCol]) && (vGroundMap[iMaxRow][iMaxCol] < vGroundMap[iMaxRow][iMaxCol-1]))
        vTempPoints.push_back(Point(iMaxRow, iMaxCol));

    /* Check edges */
    for (size_t iCol = 1; iCol <= iMaxCol-1; iCol++) {
        if ((vGroundMap[0][iCol] < vGroundMap[0][iCol-1]) && (vGroundMap[0][iCol] < vGroundMap[0][iCol+1]) && (vGroundMap[0][iCol] < vGroundMap[1][iCol]))
            vTempPoints.push_back(Point(0, iCol));

        if ((vGroundMap[iMaxRow][iCol] < vGroundMap[iMaxRow][iCol-1]) && (vGroundMap[iMaxRow][iCol] < vGroundMap[iMaxRow][iCol+1]) && (vGroundMap[iMaxRow][iCol] < vGroundMap[iMaxRow-1][iCol]))
            vTempPoints.push_back(Point(iMaxRow, iCol));
    }

    for (size_t iRow = 1; iRow <= iMaxRow-1; iRow++) {
        if ((vGroundMap[iRow][0] < vGroundMap[iRow-1][0]) && (vGroundMap[iRow][0] < vGroundMap[iRow+1][0]) && (vGroundMap[iRow][0] < vGroundMap[iRow][1]))
            vTempPoints.push_back(Point(iRow, 0));

        if ((vGroundMap[iRow][iMaxCol] < vGroundMap[iRow-1][iMaxCol]) && (vGroundMap[iRow][iMaxCol] < vGroundMap[iRow+1][iMaxCol]) && (vGroundMap[iRow][iMaxCol] < vGroundMap[iRow][iMaxCol-1]))
            vTempPoints.push_back(Point(iRow, iMaxCol));
    }

    /* Check all */
    for (size_t iRow = 1; iRow <= iMaxRow-1; iRow++)
        for (size_t iCol = 1; iCol <= iMaxCol-1; iCol++)
            if ((vGroundMap[iRow][iCol] < vGroundMap[iRow-1][iCol]) && (vGroundMap[iRow][iCol] < vGroundMap[iRow+1][iCol]) && (vGroundMap[iRow][iCol] < vGroundMap[iRow][iCol-1]) && (vGroundMap[iRow][iCol] < vGroundMap[iRow][iCol+1]))
                vTempPoints.push_back(Point(iRow, iCol));

    return vTempPoints;
}

void printBasinsImage(vector<Basin> vAllBasins, vector<vector<int>> vGroundMap)
{
    static int iCalls = 0;
    stringstream filename;
    vector<vector<int>> vInternalGroundMap = vGroundMap;
    bool bFound = false;
    
    filename << "d9p2_" << iCalls++ << ".ppm";

    ofstream oImageFile;
    oImageFile.open(filename.str(), ios_base::binary | ios_base::out);

    if (oImageFile.is_open())
    {
        oImageFile << "P3\n" << vGroundMap.size() << " " << vGroundMap[0].size() << "\n255" << endl;

        for (size_t iRow = 0; iRow < vGroundMap.size(); iRow++)
        {
            for (size_t iCol = 0; iCol < vGroundMap[iRow].size(); iCol++)
            {
                if (vGroundMap[iRow][iCol] == 9)
                {
                    oImageFile << "0 0 0  ";
                }
                else
                {
                    bFound = false;

                    for (auto &&basin : vAllBasins)
                    {
                        if (basin.isInBasin(Point(iRow, iCol)))
                        {
                            oImageFile << "255 153 153  ";
                            bFound = true;
                            break;
                        }
                    }
                    
                    if (!bFound)
                    {
                        oImageFile << "255 255 255  ";
                    }
                }
            }
            oImageFile << endl;
        }

        oImageFile.close();
    }
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> vGroundMap;
    vector<Point> vMinimalPoints;
    vector<Basin> vAllBasins;

    int iRiskLevel = 0;

    if (!siReadAndProcessInput("input.txt", vGroundMap))
    {
        /* Get all minimal points */
        vMinimalPoints = getAllMinimums(vGroundMap);
        cout << "Extracted " << vMinimalPoints.size() << " minimal points." << endl;

        /* Initiate all basins */
        for (auto &&oPoint : vMinimalPoints)
        {
            vAllBasins.push_back(Basin(oPoint));
        }
        cout << "Created " << vAllBasins.size() << " basins." << endl;

        while (count_if(vAllBasins.begin(), vAllBasins.end(), [](Basin b){return b.isComplete;}) != vAllBasins.size())
        {
            for (auto &&oBasin : vAllBasins)
                if (!oBasin.isComplete)
                    oBasin.expand(vGroundMap);

            printBasinsImage(vAllBasins, vGroundMap);
        }

        sort(vAllBasins.begin(), vAllBasins.end(), greater<Basin>());
        /*cout << "Final basins size are: ";
        for (auto &&basin : vAllBasins)
        {
            cout << " " << basin.points.size();
        }
        cout << endl;*/
        cout << "Score is " << vAllBasins[0].points.size()*vAllBasins[1].points.size()*vAllBasins[2].points.size() << endl;
    }
    else
    {
        return 1;
    }
    return 0;
}
