#include <cstring>
#include <vector>

using namespace std;

const long double eps = 1e-12;
const long double infl = 1e20;

template <class T>
inline int sgn(const T & x)
{
	return (x > eps) - (x < -eps);
}

template <class T>
class Dijkstra
{
public:
	static const int maxn = 100000;

	class Edge
	{
	public:
		int u, v;
		T w;

		Edge(void) : u(0), v(0), w(0)
		{

		}

		Edge(const int & u, const int & v, const T & w) : u(u), v(v), w(w)
		{

		}
	};

	class Node
	{
	public:
		int u;
		T d;

		Node(void) : u(0), d(0)
		{

		}

		Node(const int & u, const T & d) : u(u), d(d)
		{

		}

		bool operator < (const Node & rhs) const
		{
			return d > rhs.d;
		}
	};

	int n;
	vector<Edge> E[maxn];
	T d[maxn];

	Dijkstra(void)
	{

	}

	void resize(const int & n)
	{
		for (int i = 0; i < this->n; i++)
			E[i].clear();
		this->n = n;
	}

	void add_edge(const int & u, const int & v, const T & w)
	{
		E[u].emplace_back(u, v, w);
	}

	void dijkstra(const int & s)
	{
		fill(d, d + n, infl);
		d[s] = 0;
		priority_queue<Node> que;
		for (que.emplace(s, 0); !que.empty(); )
		{
			Node node = que.top();
			int u = node.u;
			que.pop();
			if (sgn(node.d - d[u]) > 0)
				continue;
			for (const auto & edge : E[u])
			{
				int v = edge.v;
				T w = edge.w;
				if (sgn(d[v] - d[u] - w) > 0)
				{
					d[v] = d[u] + w;
					que.emplace(v, d[v]);
				}
			}
		}
	}
};
