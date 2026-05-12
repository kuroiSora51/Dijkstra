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
   Vertex* v;
   Vertex* u;
   double w;

   Edge(Vertex* v_, Vertex* u_, double w_) : v(v_), u(u_), w(w_) {} 
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

        void dijkstra (Vertex* x) {
            using P = pair<double, Vertex*>;
            priority_queue<P, vector<P>, greater<P>> q;
            
            x->dist = 0;
            q.push({0, x});
            
            while (!q.empty()) {
                auto [d, v] = q.top();
                q.pop();

                if (d != v->dist) continue;

                for (Edge& e: v->adj) {
                    Vertex* u = e.u;
                    if (v->dist + e.w >= u->dist) continue;

                    u->dist = v->dist + e.w;
                    q.push({u->dist, u});
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
