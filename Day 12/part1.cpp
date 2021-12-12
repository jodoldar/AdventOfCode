/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 12 - Part 1 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-12
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

class Graph
{
public:
    map<string, list<string>> adjacent;

    Graph(){};
    void addVertex(string a, string b);
    void optimize();

    friend ostream& operator<<(ostream& os, const Graph g);
};

void Graph::addVertex(string a, string b)
{
    adjacent[a].push_back(b);
    adjacent[b].push_back(a);

    //cout << "Added edge from " << a << " to " << b << endl;
}

void Graph::optimize()
{
    /* Step 1 - Remove paths to start */
    for (auto &&node : adjacent)
        node.second.remove("start");

    /* Step 2 - Remove small-case pitfalls */
    for (auto &&node : adjacent)
        if (node.second.size()==1 && islower(node.second.front().front()))
            for (auto &&node2 : adjacent)
                node2.second.remove(node.first);

}

static void DFS(vector<string> vHistory, vector<vector<string>> &vPaths, Graph oGraph)
{
    vector<string> vLocalHistory = vHistory;

    for (auto &&adj : oGraph.adjacent[vHistory.back()])
    {
        vLocalHistory = vHistory;

        if (adj == "end") /* Final node */
        {
            vLocalHistory.push_back(adj);
            vPaths.push_back(vLocalHistory);
        }
        else if (islower(adj.front()) && find(vHistory.begin(), vHistory.end(), adj)!=vHistory.end()) /* Repeated small cave */
        {
            ;
        }
        else
        {
            vLocalHistory.push_back(adj);
            DFS(vLocalHistory, vPaths, oGraph);
        }
    }
}

ostream& operator<<(ostream& os, const Graph g)
{
    for (const auto &elem : g.adjacent)
    {
        os << "\t" << elem.first << " -> [";
        for (auto &&vertex : elem.second)
        {
            os << vertex << ",";
        }
        os << "\b]" << endl;
    }

    return os;
}

short int siReadAndProcessInput(string sFileName, Graph &oGraph)
{
    ifstream fInputFile;
    string sLine, sVerA, sVerB;
    size_t zPos;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
                continue;

            zPos = sLine.find('-');
            sVerA = sLine.substr(0,zPos);
            sVerB = sLine.erase(0, zPos+1);
            oGraph.addVertex(sVerA, sVerB);
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
    Graph oGraph;
    vector<vector<string>> vPaths;

    if (!siReadAndProcessInput("input.txt", oGraph))
    {
        cout << "Processed graph is:\n " << oGraph << endl;

        oGraph.optimize();
        cout << "Optimized graph is:\n" << oGraph << endl;

        DFS({"start"}, vPaths, oGraph);
        cout << "Number of paths are " << vPaths.size() << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}