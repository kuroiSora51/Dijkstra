/*****************************************

 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 * Edgar Gonzalez German
 * Tin Htoo Naing(Mike)
 * The following is a list of those students
 * I had worked together in preparing this project:
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <cmath>
#include <functional>
#include "Exception.h"

// include whatever classes you want

struct Vertex;

// An edge e connects two vertices from -> to 
struct Edge {
   Vertex* from;
   Vertex* to;
   double weight;

   Edge(Vertex* v, Vertex* u, double w) : from(v), to(u), weight(w) {} 
   Edge() = default;
};

//A vertex is the basic unit for a graph, it's connected to some other vertices through edges
struct Vertex {
   int val; //this can be removed at the end
   double dist = std::numeric_limits<double>::infinity();
   std::vector<Edge> adj;

   Vertex(int value) : val(value) {}
   Vertex() = default;
};

// Our graph is undirected
class Weighted_graph {
	private:
		static const double INF;
        std::vector<Vertex*> vertices;
        std::vector<std::vector<double>> min_dist; // d[a][b] will provide the smallest distance for a -> b
        bool is_current; // checks if min_dist is up to date
        int edges;
	public:
		Weighted_graph(int n = 50) : is_current(false), edges(0) {
			if (n <= 0) {
		        n = 1; //handle bad input, based on the instructions
		    }
			
            vertices.resize(n);
            min_dist.resize(n, std::vector<double>(n, INF));
            
            for (int i = 0; i < n; i++) {
				vertices[i] = new Vertex(i);
			}
        }
		~Weighted_graph() {
            for (auto& v: vertices) {
                delete v;
            }
        }
		// Returns the degree of vertex n.
		// Throws illegal_argument if n is invalid.
		int degree( int n ) const {
		
		    if (n < 0 || static_cast<std::size_t>(n) >= vertices.size()) {
		        throw illegal_argument();
		    }
		
		    return vertices[n]->adj.size();
		}
		
		/*
		 * Returns the total number of edges in the graph.
		 */
		int edge_count() const {
		    return edges;
		}
		double adjacent( int m, int n ) const {
			if (m < 0 || n < 0 ||
				static_cast<std::size_t>(m) >= vertices.size() ||
				static_cast<std::size_t>(n) >= vertices.size()) {
				throw illegal_argument();
			}

			for (const Edge& e : vertices[m]->adj) {
				if (e.to == vertices[n]) {
					return e.weight;
				}
			}

			return INF;
		}

		double distance(int m, int n) {
            if (m < 0 || n < 0 ||
				static_cast<std::size_t>(m) >= vertices.size() ||
				static_cast<std::size_t>(n) >= vertices.size()
            ) {
				throw illegal_argument(); //bad input
			}
            // if is not current we need to update
            if (!is_current) { 
                precompute_distances();
                is_current = true;
            }
            return min_dist[m][n];
        }

        //this makes current = false everytime
		void insert( int m, int n, double w ) {
			if (m < 0 || n < 0 || m == n ||
				static_cast<std::size_t>(m) >= vertices.size() ||
				static_cast<std::size_t>(n) >= vertices.size() ||
				w <= 0 || std::isinf(w)) {
		
				throw illegal_argument(); //bad input
			}
		
            bool found = false; //refering 

			for (std::size_t i = 0; i < vertices[m]->adj.size(); i++) {
				if (vertices[m]->adj[i].to == vertices[n]) {
					vertices[m]->adj[i].weight = w;
                    found = true;
                    break;
                }
            }
            is_current = false;
            if (found) {
                for (std::size_t j = 0; j < vertices[n]->adj.size(); j++) {
                    if (vertices[n]->adj[j].to == vertices[m]) {
                        vertices[n]->adj[j].weight = w;
                        break;
                    }
                }
            }
            else {
                vertices[m]->adj.push_back(Edge(vertices[m], vertices[n], w));
                vertices[n]->adj.push_back(Edge(vertices[n], vertices[m], w));
                edges++;
            }
		}
        // computes min distance for a single vertex using priproty queue
        void dijkstra (Vertex* start) {
            using P = std::pair<double, Vertex*>;
            std::priority_queue<P, std::vector<P>, std::greater<P>> queue;
            
            for (Vertex* v: vertices) {
                v->dist = INF; //initialize distance
            }

            start->dist = 0; //min_dist[start][start] = 0
            // the ordered pair is stored by the distance on ascending order
            // we travel through the adjacent vertices of each vertex in the queue
            queue.push({0, start}); 
            
            while (!queue.empty()) {
                P current = queue.top();
                double d = current.first;
                Vertex* v = current.second;
                queue.pop();

                if (d != v->dist) continue;

                for (Edge& e: v->adj) {
                    Vertex* to = e.to;
                    if (v->dist + e.weight >= to->dist) continue;

                    to->dist = v->dist + e.weight;
                    queue.push({to->dist, to});
                }
            }
            std::size_t n = min_dist.size();
            for (std::size_t i = 0; i < n; i++) {
                min_dist[start->val][i] = vertices[i]->dist; 
            }
        } 
    
        void precompute_distances() {
            for(Vertex* v: vertices) {
                dijkstra(v);
            }
        }

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	(void) graph;
	return out;
}

// Is an error showing up in CIS22B.h or elsewhere?
// Did you forget a closing '}' ?

#endif
