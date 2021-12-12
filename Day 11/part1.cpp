/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 11 - Part 1 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <list>
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

void increaseAndFlash(vector<vector<int>> &vOctopusMap)
{
    list<Point> vFlashingPoints;
    list<Point> vFlashedPoints;

    for (size_t iRow = 0; iRow < vOctopusMap.size(); iRow++)
    {
        for (size_t iCol = 0; iCol < vOctopusMap[iRow].size(); iCol++)
        {
            vOctopusMap[iRow][iCol]++;

            if (vOctopusMap[iRow][iCol] > 9)
            {
                vFlashingPoints.push_back(Point(iRow, iCol));
            }
        }
    }
    
    while (!vFlashingPoints.empty())
    {
        Point p = vFlashingPoints.front();

        /* Up-left */
        if (p.X > 0 && p.Y > 0 && find_if(vFlashingPoints.begin(), vFlashingPoints.end(), [p](Point pt){return (p.X-1)==pt.X && (p.Y-1)==pt.Y;})==vFlashingPoints.end()) {
            vOctopusMap[p.X-1][p.Y-1]++;
            if (vOctopusMap[p.X-1][p.Y-1] > 9)
                vFlashingPoints.push_back(Point(p.X-1, p.Y-1));
        }

        /* Up */
        if (p.X > 0 && find_if(vFlashingPoints.begin(), vFlashingPoints.end(), [p](Point pt){return (p.X-1)==pt.X && p.Y==pt.Y;})==vFlashingPoints.end()) {
            vOctopusMap[p.X-1][p.Y]++;
            if (vOctopusMap[p.X-1][p.Y] > 9)
                vFlashingPoints.push_back(Point(p.X-1, p.Y));
        }
        
        /* Up-right */
        if (p.X > 0 && p.Y < vOctopusMap[0].size()-1 && find_if(vFlashingPoints.begin(), vFlashingPoints.end(), [p](Point pt){return (p.X-1)==pt.X && (p.Y+1)==pt.Y;})==vFlashingPoints.end()) {
            vOctopusMap[p.X-1][p.Y+1]++;
            if (vOctopusMap[p.X-1][p.Y+1] > 9)
                vFlashingPoints.push_back(Point(p.X-1, p.Y+1));
        }

        /* Right */
        if (p.Y < vOctopusMap[0].size()-1 && find_if(vFlashingPoints.begin(), vFlashingPoints.end(), [p](Point pt){return (p.X)==pt.X && (p.Y+1)==pt.Y;})==vFlashingPoints.end()) {
            vOctopusMap[p.X][p.Y+1]++;
            if (vOctopusMap[p.X][p.Y+1] > 9)
                vFlashingPoints.push_back(Point(p.X, p.Y+1));
        }

        /* Down-right */
        if (p.X < vOctopusMap.size()-1 && p.Y < vOctopusMap[0].size()-1 && find_if(vFlashingPoints.begin(), vFlashingPoints.end(), [p](Point pt){return (p.X+1)==pt.X && (p.Y+1)==pt.Y;})==vFlashingPoints.end()) {
            vOctopusMap[p.X+1][p.Y+1]++;
            if (vOctopusMap[p.X+1][p.Y+1] > 9)
                vFlashingPoints.push_back(Point(p.X+1, p.Y+1));
        }

        /* Down */
        if (p.X < vOctopusMap.size()-1 && find_if(vFlashingPoints.begin(), vFlashingPoints.end(), [p](Point pt){return (p.X+1)==pt.X && p.Y==pt.Y;})==vFlashingPoints.end()) {
            vOctopusMap[p.X+1][p.Y]++;
            if (vOctopusMap[p.X+1][p.Y] > 9)
                vFlashingPoints.push_back(Point(p.X+1, p.Y));
        }

        /* Down-left */
        if (p.X < vOctopusMap.size()-1 && p.Y > 0 && find_if(vFlashingPoints.begin(), vFlashingPoints.end(), [p](Point pt){return (p.X+1)==pt.X && (p.Y-1)==pt.Y;})==vFlashingPoints.end()) {
            vOctopusMap[p.X+1][p.Y-1]++;
            if (vOctopusMap[p.X+1][p.Y-1] > 9)
                vFlashingPoints.push_back(Point(p.X+1, p.Y-1));
        }

        /* Left */
        if (p.Y > 0 && find_if(vFlashingPoints.begin(), vFlashingPoints.end(), [p](Point pt){return (p.X)==pt.X && (p.Y-1)==pt.Y;})==vFlashingPoints.end()) {
            vOctopusMap[p.X][p.Y-1]++;
            if (vOctopusMap[p.X][p.Y-1] > 9)
                vFlashingPoints.push_back(Point(p.X, p.Y-1));
        }

        vOctopusMap[p.X][p.Y] = 0;
        vFlashedPoints.push_back(p);
        vFlashingPoints.pop_front();
    }

    for (auto &&point : vFlashedPoints)
    {
        vOctopusMap[point.X][point.Y] = 0;
    }
    
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> vOctopusMap;
    int iFlashes = 0;
    
    if (!siReadAndProcessInput("input.txt", vOctopusMap))
    {
        for (size_t i = 0; i <= 100; i++)
        {
            for (auto &&line : vOctopusMap)
            {
                for (auto &&elem : line)
                {
                    if(elem == 0)
                    {
                        iFlashes++;
                        cout << RED_COLOR << elem << RESET_COLOR;
                    }
                    else
                    {
                        cout << elem;
                    }
                }
                cout << endl;
            }
            cout << endl;

            increaseAndFlash(vOctopusMap);
        }

        cout << "Total flashes are " << iFlashes << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}