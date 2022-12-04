/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 10 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <string>
#include <vector>

#include "../Common/utils.hpp"

using namespace std;

short int siReadAndProcessInput(string sFileName, vector<string> &sLines)
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

            sLines.push_back(sLine);
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

long getScoreFromLine(string sLine, map<char,char> mTokens)
{
    stack<char> stStack;
    long iScoreLine = 0;

    for (auto &&ch : sLine)
    {
        switch (ch)
        {
        case '(':
        case '[':
        case '{':
        case '<':
            stStack.push(ch);
            break;
        default:
            if (stStack.top() == mTokens[ch])
            {
                stStack.pop();
            }
            else
            {
                return -1;
            }
            break;
        }
    }

    if (!stStack.empty())
    {       
        while (!stStack.empty())
        {
            iScoreLine *= 5;
            switch (stStack.top())
            {
            case '(':
                iScoreLine += 1;
                break;
            case '[':
                iScoreLine += 2;
                break;
            case '{':
                iScoreLine += 3;
                break;
            case '<':
                iScoreLine += 4;
                break;
            default:
                break;
            }
            stStack.pop();
        }

        return iScoreLine;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char const *argv[])
{
    vector<string> vLines;
    vector<long> vScores;
    long iScore = 0;

    map<char,char> finishers;
    finishers[')'] = '(';
    finishers[']'] = '[';
    finishers['}'] = '{';
    finishers['>'] = '<';

    if (!siReadAndProcessInput("input.txt", vLines))
    {
        for (auto &&sLine : vLines)
        {
            if((iScore=getScoreFromLine(sLine, finishers)) > 0)
            {
                vScores.push_back(iScore);
            }
        }

        sort(vScores.begin(), vScores.end());
        auto median_it = vScores.begin() + vScores.size() / 2;
        cout << "Middle score from the file is " << *median_it << endl;
    }
    else
    {
        return 1;
    }
    return 0;
}
