/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 13 - Part 1 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <list>
#include <numeric>
#include <map>
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

enum class Mode { X_LINE, Y_LINE };

class Fold
{
public:
    int pos;
    Mode mod;

    Fold(){};
    Fold(int p, Mode m): pos(p), mod(m) {};
};

short int siReadAndProcessInput(string sFileName, vector<vector<char>> &vFoldMap, vector<Fold> &vFoldOps)
{
    ifstream fInputFile;
    string sLine, sPosX, sPosY;
    size_t zPos;
    int iMaxX = 0, iMaxY = 0;
    vector<Point> vStartPoints;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        /* Block 1 - read dots */
        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
                break;

            zPos = sLine.find(',');
            sPosX = sLine.substr(0,zPos);
            sPosY = sLine.erase(0, zPos+1);

            if (stoi(sPosX) > iMaxX)
                iMaxX = stoi(sPosX);

            if (stoi(sPosY) > iMaxY)
                iMaxY = stoi(sPosY);

            vStartPoints.push_back(Point(stoi(sPosX), stoi(sPosY)));
            //cout << "Added new point " << vStartPoints.back().X << "," << vStartPoints.back().Y << endl;
        }

        cout << "The map size will be " << iMaxX << "x" << iMaxY << endl;
        /* Create an all-dot map */
        vFoldMap.empty();
        for (size_t iRow = 0; iRow <= iMaxX; iRow++)
        {
            vFoldMap.push_back({});
            for (size_t iCol = 0; iCol <= iMaxY; iCol++)
            {
                vFoldMap.back().push_back('.');
            }
        }

        /* Fill the points */
        for (auto &&point : vStartPoints)
        {
            //cout << "Adding point " << point.X << "," << point.Y << " to the map." << endl;
            vFoldMap[point.X][point.Y] = '#';
        }

        /* Block 2 - read folds */
        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
                continue;

            zPos = sLine.find('=');
            sPosX = sLine.substr(zPos-1,1);
            sPosY = sLine.erase(0, zPos+1);

            if (sPosX == "x") {
                vFoldOps.push_back(Fold(stoi(sPosY), Mode::X_LINE));
            } else {
                vFoldOps.push_back(Fold(stoi(sPosY), Mode::Y_LINE));
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

int main(int argc, char const *argv[])
{
    vector<vector<char>> vFoldMap;
    vector<Fold> vFoldOps;

    if (!siReadAndProcessInput("input.txt", vFoldMap, vFoldOps))
    {
        for (size_t iY = 0; iY < vFoldMap[0].size(); iY++)
        {
            for (size_t iX = 0; iX < vFoldMap.size(); iX++)
            {
                cout << vFoldMap[iX][iY];
            }
            cout << endl;
        }

        cout << vFoldOps.size() << " fold operations to perform." << endl;

        Fold fl = vFoldOps.front();
        int line = fl.pos - 1;

        if (fl.mod == Mode::X_LINE)
        {
            while (line >= 0 && (fl.pos+(fl.pos-line)<vFoldMap.size()))
            {
                for (size_t iCol = 0; iCol < vFoldMap[0].size(); iCol++)
                {
                    if (vFoldMap[fl.pos+(fl.pos-line)][iCol] == '#')
                        vFoldMap[line][iCol] = '#';
                }

                line--;
            }

            int iToDel = vFoldMap.size()-fl.pos;
            cout << "To be removed x" << iToDel << " times." << endl;

            for (size_t i = 0; i < iToDel; i++)
            {
                vFoldMap.pop_back();
            }
        }
        else
        {
            while (line >= 0 && (fl.pos+(fl.pos-line)<vFoldMap[0].size()))
            {
                for (size_t iRow = 0; iRow < vFoldMap.size(); iRow++)
                {
                    if (vFoldMap[iRow][fl.pos+(fl.pos-line)] == '#') {
                        //cout << "Moving # from [" << fl.pos+(fl.pos-line) << "," << iRow << "] to [" << line << "," << iRow << "]" << endl;
                        vFoldMap[iRow][line] = '#';
                    }
                }

                line--;
            }

            int iToDel = vFoldMap[0].size()-fl.pos;
            cout << "To be removed x" << iToDel << " times." << endl;

            for (auto &&vert : vFoldMap)
            {
                for (size_t i = 0; i < iToDel; i++)
                {
                    vert.pop_back();
                }
            }
        }

/*        fl = vFoldOps[1];
        line = fl.pos - 1;

        cout << fl.pos << "+" << int(fl.mod) << endl;

        if (fl.mod == Mode::X_LINE)
        {
            while (line >= 0 && (fl.pos+(fl.pos-line)<vFoldMap.size()))
            {
                for (size_t iCol = 0; iCol < vFoldMap[0].size(); iCol++)
                {
                    if (vFoldMap[fl.pos+(fl.pos-line)][iCol] == '#')
                        vFoldMap[line][iCol] = '#';
                }

                line--;
            }

            int iToDel = vFoldMap.size()-fl.pos;
            cout << "To be removed x" << iToDel << " times." << endl;

            for (size_t i = 0; i < iToDel; i++)
            {
                vFoldMap.pop_back();
            }
        }
        else
        {
            while (line >= 0 && (fl.pos+(fl.pos-line)<vFoldMap[0].size()))
            {
                for (size_t iRow = 0; iRow < vFoldMap.size(); iRow++)
                {
                    if (vFoldMap[iRow][fl.pos+(fl.pos-line)] == '#') {
                        //cout << "Moving # from [" << fl.pos+(fl.pos-line) << "," << iRow << "] to [" << line << "," << iRow << "]" << endl;
                        vFoldMap[iRow][line] = '#';
                    }
                }

                line--;
            }

            int iToDel = vFoldMap[0].size()-fl.pos;
            cout << "To be removed x" << iToDel << " times." << endl;

            for (auto &&vert : vFoldMap)
            {
                for (size_t i = 0; i < iToDel; i++)
                {
                    vert.pop_back();
                }
            }
        }
*/
        int iDots = 0;
        for (size_t iY = 0; iY < vFoldMap[0].size(); iY++)
        {
            for (size_t iX = 0; iX < vFoldMap.size(); iX++)
            {
                if (vFoldMap[iX][iY] == '#')
                    iDots++;
                cout << vFoldMap[iX][iY];
            }
            cout << endl;
        }

        cout << "Number of # in the map: " << iDots << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}