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

using namespace std;
// include whatever classes you want

struct Vertex;

struct Edge {
   Vertex* from;
   Vertex* to;
   double weight;

   Edge(Vertex* v, Vertex* u, double w) : from(v), to(u), weight(w) {} 
   Edge() = default;
};

struct Vertex {
   int val; //this can be removed at the end
   double dist = std::numeric_limits<double>::infinity();
   vector<Edge> adj;
};

class Weighted_graph {
	private:
		// your implementation here
		//  you can add both private member variables and private member functions
        //static int n; // the number of vertices
		static const double INF;
        vector<Vertex*> vertices;
	public:
		Weighted_graph(int n = 50) {
            vertices.resize(n);
            for (int i = 0; i < n; i++) 
                vertices[i]->val = i;
        }
		~Weighted_graph() {
            for (auto& v: vertices) {
                delete v;
            }
        }

        // returns 
		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int );

		void insert( int, int, double );

        void dijkstra (Vertex* start) {
            using P = pair<double, Vertex*>;
            priority_queue<P, vector<P>, greater<P>> queue;
            
            start->dist = 0;
            // the ordered pair is stored by the distance on ascending order
            // we travel through the adjacent vertices of each vertex in the queue
            queue.push({0, start}); 
            
            while (!queue.empty()) {
                auto [d, v] = queue.top(); //decompose into distance d and vertex v of distance d
                queue.pop();

                if (d != v->dist) continue;

                for (Edge& e: v->adj) {
                    Vertex* from = e.from;
                    if (v->dist + e.weight >= from->dist) continue;

                    from->dist = v->dist + e.weight;
                    queue.push({from->dist, from});
                }
            }

}

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in CIS22B.h or elsewhere?
// Did you forget a closing '}' ?

#endif
