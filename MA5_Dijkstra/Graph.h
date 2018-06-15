#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <queue>
#include <functional>

#include "Vertex.h"
using namespace std;
class Graph
{
	unordered_map<int, Vertex> _vertices;

public:

	void addVertex(Vertex vertex)
	{
		_vertices[vertex.getId()] = vertex;
	}

	//MA #12 TODO: IMPLEMENT!
	unordered_map<Vertex, int> computeShortestPath(Vertex *start)
	{
		//holds known distances
		unordered_map<Vertex, int> distances;

		//underlying heap
		priority_queue<Vertex, vector<Vertex>, PathWeightComparer> dijkstra_queue{};

		//reset start's path weight
		start->setPathWeight(0);

		//make sure that the starting vertex is in the graph
		if (_vertices.find(start->getId()) != _vertices.end())
		{
			//push on starting vertex
			dijkstra_queue.push(_vertices.at(start->getId()));

			//while queue not empty
			while (!dijkstra_queue.empty())
			{
				//push on outgoing edges that haven't been discovered
				Vertex t = dijkstra_queue.top();
				dijkstra_queue.pop();

				//Top of heap not known (in distances)?
				if (distances.find(t) == distances.end())
				{
					//make known
					int newDistance = t.getPathWeight();
					distances[t] = newDistance;

					//push on outgoing edges
					for (auto item : t.getEdges())
					{
						Vertex *next = item.first;
						int weight = item.second;
						next->setPathWeight(weight + newDistance);

						if (distances.find(*next) == distances.end())
						{
							dijkstra_queue.push(*next);
						}
					}
				}
			}
			return distances;
		}
	}
};

#endif
