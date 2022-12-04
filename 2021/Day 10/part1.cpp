/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 10 - Part 1 of the Advent of Code 2021
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

int getScoreFromLine(string sLine, map<char,char> mTokens)
{
    stack<char> stStack; 

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
                switch (ch)
                {
                case ')':
                    return 3;
                case ']':
                    return 57;
                case '}':
                    return 1197;
                case '>':
                    return 25137;
                default:
                    break;
                }
            }
            break;
        }
    }
    
    return 0;
}

int main(int argc, char const *argv[])
{
    vector<string> vLines;
    int iScore = 0;

    map<char,char> finishers;
    finishers[')'] = '(';
    finishers[']'] = '[';
    finishers['}'] = '{';
    finishers['>'] = '<';

    if (!siReadAndProcessInput("input.txt", vLines))
    {
        for (auto &&sLine : vLines)
        {
            iScore += getScoreFromLine(sLine, finishers);
        }

        cout << "Final score from the file is " << iScore << endl;
    }
    else
    {
        return 1;
    }
    return 0;
}
