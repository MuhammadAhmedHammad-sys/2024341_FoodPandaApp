#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <queue>
#include <fstream>
using namespace std;

struct Location
{
    int code;
    string name;
};

class LocationGraph
{
private:
    map<int, Location> locations;  // Map of location code to Location
    map<int, list<int>> adjList; // Adjacency list for the graph
    string locationFile;
    string edgeFile;

public:
    LocationGraph(string locationFile = "locations/location_codes.txt", string edgeFile = "locations/location_edges.txt")
    {
        this->locationFile = locationFile;
        this->edgeFile = edgeFile;

        // Read locations from file
        ifstream locFile(locationFile);
        int code;
        string name;
        while (locFile >> code >> name)
        {
            locations[code] = {code, name};
        }
        locFile.close();

        // Read edges from file
        ifstream edgeFileHandle(edgeFile);
        int from, to;
        while (edgeFileHandle >> from >> to)
        {
            adjList[from].push_back(to);
        }
    }

    bool addLocation(int code, string name)
    {
        if (locations.find(code) != locations.end())
        {
            return false;
        }
        locations[code] = {code, name};
        return true;
    }

    void addEdge(int from, int to, bool directed = false)
    {
        adjList[from].push_back(to);
        if (!directed)
            adjList[to].push_back(from); // Assuming undirected graph
    }

    void saveToFile()
    {
        // Save locations to file
        ofstream locFile(locationFile);
        for (const auto &loc : locations)
        {
            locFile << loc.first << " " << loc.second.name << endl;
        }
        locFile.close();

        // Save edges to file
        ofstream edgeFileHandle(edgeFile);
        for (const auto &pair : adjList)
        {
            int from = pair.first;
            for (int to : pair.second)
            {
                edgeFileHandle << from << " " << to << endl;
            }
        }
        edgeFileHandle.close();
    }

    void printGraph()
    {
        for (const auto &pair : adjList)
        {
            cout << "Location " << pair.first << " (" << locations[pair.first].name << "): ";
            for (int neighbor : pair.second)
            {
                cout << neighbor << " (" << locations[neighbor].name << ") ";
            }
            cout << endl;
        }
    }

    list<int> findPath(int start, int end)
    {
        list<int> path;
        // Simple BFS for pathfinding
        map<int, int> parent;
        map<int, bool> visited;
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            if (current == end)
                break;

            for (int neighbor : adjList[current])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        // Reconstruct path
        int current = end;
        while (current != start)
        {
            path.push_front(current);
            current = parent[current];
        }
        path.push_front(start);

        return path;
    }

    ~LocationGraph()
    {
        saveToFile();
    }
};

#endif