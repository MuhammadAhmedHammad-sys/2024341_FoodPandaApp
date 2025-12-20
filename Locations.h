#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Location
{
    int code;
    string name;
    Location(int c, string n) : code(c), name(n) {};
};

struct LocationNode
{
    Location data;
    LocationNode *next;
    LocationNode(Location d, LocationNode *n) : data(d), next(n) {};
};

struct LocationList
{
    LocationNode *head;
    LocationList *next;
    LocationList() : head(nullptr) {};
    LocationList(LocationNode *h, LocationList *n) : head(h), next(n) {};
};

class LocationGraph
{
private:
    LocationList *locations_head; // Adjacency list for the graph
    string locationFile;
    string edgeFile;

public:
    LocationGraph(const string &locationFile = "locations/location_codes.txt", const string &edgeFile = "locations/location_edges.txt")
    {
        this->locations_head = nullptr;
        this->locationFile = locationFile;
        this->edgeFile = edgeFile;

        // Read locations from file
        readFromFile();
    }

    bool addLocation(int code, string name)
    {
        for (LocationList *locList = locations_head; locList != nullptr; locList = locList->next)
        {
            if (locList->head->data.code == code)
                return false; // Location already exists
        }
        LocationNode *newLocNode = new LocationNode(Location(code, name), nullptr);
        locations_head = new LocationList(newLocNode, locations_head);
        return true;
    }

    void addEdge(int from, int to, bool directed = false)
    {
        LocationList *fromList = nullptr;
        LocationList *toList = nullptr;
        for (LocationList *locList = locations_head; locList != nullptr; locList = locList->next)
        {
            if (locList->head->data.code == from)
                fromList = locList;
            if (locList->head->data.code == to)
                toList = locList;
        }
        if (fromList && toList)
        {
            fromList->head = new LocationNode(toList->head->data, fromList->head);
            if (!directed)
            {
                toList->head = new LocationNode(fromList->head->data, toList->head);
            }
        }
    }

    void readFromFile()
    {
        // format: code, name
        ifstream lFile(locationFile);
        int code;
        string name;
        while (lFile >> code && getline(lFile, name))
        {
            addLocation(code, name);
        }
        lFile.close();

        // format: from, to
        ifstream eFile(edgeFile);
        int from, to;
        while (eFile >> from >> to)
        {
            addEdge(from, to, true);
        }
    }

    void saveToFile()
    {
        ofstream lFile(locationFile);
        for (LocationList *locList = locations_head; locList != nullptr; locList = locList->next)
        {
            lFile << locList->head->data.code << " " << locList->head->data.name << "\n";
        }
        lFile.close();

        ofstream eFile(edgeFile);
        for (LocationList *locList = locations_head; locList != nullptr; locList = locList->next)
        {
            LocationNode *fromNode = locList->head;
            for (LocationNode *toNode = fromNode->next; toNode != nullptr; toNode = toNode->next)
            {
                eFile << fromNode->data.code << " " << toNode->data.code << "\n";
            }
        }
        eFile.close();
    }

    void printGraph()
    {
        for (LocationList *locList = locations_head; locList != nullptr; locList = locList->next)
        {
            cout << locList->head->data.code << " (" << locList->head->data.name << ") : ";
            for (LocationNode *node = locList->head->next; node != nullptr; node = node->next)
            {
                cout << node->data.code << " (" << node->data.name << ") -> ";
            }
            cout << "nullptr\n";
        }
    }

    bool dfs(int current, int end, LocationNode *&path, LocationNode *visited)
    {
        // mark visited
        visited = new LocationNode(Location(current, ""), visited);

        if (current == end)
        {
            path = new LocationNode(Location(current, ""), path);
            return true;
        }

        LocationList *curList = nullptr;
        for (LocationList *l = locations_head; l; l = l->next)
            if (l->head->data.code == current)
                curList = l;

        if (!curList)
            return false;

        for (LocationNode *n = curList->head->next; n; n = n->next)
        {
            int next = n->data.code;

            bool seen = false;
            for (LocationNode *v = visited; v; v = v->next)
                if (v->data.code == next)
                    seen = true;

            if (!seen && dfs(next, end, path, visited))
            {
                path = new LocationNode(Location(current, ""), path);
                return true;
            }
        }

        return false;
    }

    LocationList *findPath(int start, int end)
    {
        LocationNode *path = nullptr;
        LocationNode *visited = nullptr;

        if (dfs(start, end, path, visited))
            return new LocationList(path, nullptr);

        return nullptr;
    }

    ~LocationGraph()
    {
        saveToFile();
    }
};

#endif

int main()
{
    LocationGraph graph;
graph.printGraph();
    return 0;
}