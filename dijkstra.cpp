#include <iostream>
#include <vector>   /* vector */
#include <stdlib.h>
#include <assert.h> /* assert */
using std::vector;
using std::cout;

typedef int Node;
typedef int value;
typedef int prioriy;

class Graph{
	/*
	 * This class is to create a graph.
	 */
	//int v,e;
	//int nodes[v]; // Return the number of vertices in the graph
	//int edges[e]; // Return the number of edges in the graph
		// use vector to implement a matrix
	public:
		vector< vector<int> > vec; // Matrix used to store the value of edges
		vector< int > nodes; // Store the value for each node
		explicit Graph(int size);
		int get_number_nodes(Graph G); // Return the number of vertices
		int get_number_edges(Graph G); // Return the number of edges
		bool adjacent(Node x,Node y); //Test whether an edge from x to y
		vector<int> neighbors(Node x);	// List all neighbor nodes of x (is it really necessary?)
		int add(Node x); // Add x to graph
		int remove(Node x); // Delete x from grahp
		int get_node_value(Node x); // Return the value of x
		void set_node_value(Node x,value v); // Set the value of x
		int get_edge_value(Node x,Node y); // Return the value of edge from x to y
		void set_edge_value(Node x,Node y,value v); // Set the value of edge from x to y
};

Graph::Graph(int size)
{
	int N = size;
	vec.resize(N);
	for(int i = 0; i < N; ++i)
		vec[i].resize(N);
	nodes.resize(N);
};

void Graph::set_node_value(Node x,value v)
{
	this->nodes[x] = v;
};

int Graph::get_node_value(Node x)
{
	return this->nodes[x];

};

int Graph::get_edge_value(Node x,Node y)
{
	return this->vec[x][y];
};

void Graph::set_edge_value(Node x,Node y,value v)
{
	this->vec[x][y] = v; // For undirected graph, (v,w) and (w,v) edges are given the same weight
	this->vec[y][x] = v;
};

bool Graph::adjacent(Node x,Node y)
{
	if(this->vec[x][y] == 0)
		return false;
	else
		return true;
};

vector<int> Graph::neighbors(Node x)
{
	vector< int > neigh;
	assert( x < this->vec.size()); // check whether it exceeds the bound
	for(int i=0; i <=this->vec[x].size(); ++i)
	{
		if( this->adjacent(x,i))
			neigh.push_back(i);// add the index to the vector to store the value
	}
	
	for(int i=0; i<neigh.size(); ++i) // sort the neighbor nodes in terms of the increasing distance
		for(int j=i+1; j<neigh.size(); ++j)
		{	
			int temp;
			if( vec[x][neigh[i]] > vec[x][neigh[j]])
			{
				temp = neigh[i];
				neigh[i] = neigh[j];
				neigh[j] = temp;
			}
		} // ++j
	return neigh;
};


class PriorityQueue:public Graph
{
	public:
		explicit PriorityQueue(int x):Graph(x) {}; // inherit the constructor from Graph
		vector< int > PQ;
		void chgPriority(Node n,int val)
		{
			/*
			 * change the value of Node N
			 */
			this->PQ[n] = val;
		};

		void minPriority(PriorityQueue)
		{
			/*
			 * remove the first element in the queue
			 */
			this->PQ.erase(this->PQ.begin());
		};

		bool contains(Node n)
		{
			/*
			 *  check whether the node is contained within this PQ
			 */
			for(vector<int>::iterator it=this->PQ.begin();it != this->PQ.end();it++)
				if(*it == n)
					return true;
				else
					return false;
		};

		void insert(int val)
		{
			vector<int>::iterator it = this->PQ.begin();
			this->PQ.insert(it,val);
		};

		int top()
		{
			vector<int>::iterator it = this->PQ.begin();
			return *it;
		};

		int size()
		{
			return this->PQ.size();
		};
};

class ShortestPath//:public PriorityQueue
{
	public:
		/*PriorityQueue input;
		ShortestPath(PriorityQueue g)
		{
			this->input = g;
		};
		//explicit ShortestPath(int x):PriorityQueue(x) {};*/
		vector<int> nds;
		void vertices(Graph g)
		{
			this->nds = g.nodes;
		};

};


Graph creat_graph(double density,int range)
{
	/*
	 * Creat randomed graph
	 * Arguments:
	 * 	density: 0-100 integers used to represent the percentage
	 * 	range: length range for each edge
	 */
	int N = 6; 
	int total_of_edges = 0.5 * N * (N-1);
	int num_of_edges = 0;
	double D = 0; // density of the graph
	Graph g(N);
	while(D < density)
	{
		int i = rand() % N;
		int j = rand() % N;
		while(i ==j) { j = rand() % N;}
		if(g.get_edge_value(i,j) == 0)
		{
			int val = rand() % range +1;
			g.set_edge_value(i,j,val);
			num_of_edges += 1;
			D = num_of_edges / total_of_edges;
		};
	};/*
	PriorityQueue g(N);
	for(int i=0;i<g.vec.size();++i)
	{
		g.nodes[i] = 0;
		for(int j=0;j<N;++j)
			g.vec[i][j]=0; // initialize the vector
	}
	for(int i=0;i<g.vec.size();++i)
	{
		for (int j=0;j<N;++j)
		{
			if ((rand() % 100 + 1) > density)
				if (g.vec[i][j] == 0)
				{
					int val = rand() % range + 1;
					g.set_edge_value(i,j,val);
					//g.set_edge_value(j,i,val);
				}
		} //++ j
	} // ++i*/
	return g;
};


int main()
{
	Graph g = creat_graph(0.5,10);
	vector<int> test=g.neighbors(2);
	for(vector<int>::iterator it=test.begin();it!=test.end();++it)
		cout << ' ' << *it;
	cout << '\n';
	for(int i=0;i<g.vec.size();++i)
	{
		for(int j=0;j<g.vec.size();++j)
			cout << g.vec[i][j] << ' ';
		cout << '\n';
	};
	ShortestPath sp;
	sp.vertices(g);
	for(int i=0;i<sp.nds.size();++i)
		cout << "Node " << i <<'\n';
	return 0;
}


