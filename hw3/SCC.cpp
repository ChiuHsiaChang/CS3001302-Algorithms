#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h> 
#define N 500
using namespace std;
struct Edge {
	int to, next;
};
Edge edges[N];
int pos[N];
int n;
int scc[N];
int cnt;
int dfn[N];
int low[N];
int timetag;

vector<int> SCC;
vector<vector<int>> ans;

void addedge(int from, int to) {
	cnt++;//edge counts
	edges[cnt].to = to;
	edges[cnt].next = pos[from];
	//std::cout<< " edges[" << cnt << "].next:" << edges[cnt].next << std::endl ;
	//edges[cnt] = (struct Edge){ to, pos[from] };
	pos[from] = cnt;
}
void init() {
	memset(edges, 0, sizeof(edges));
	memset(pos, 0, sizeof(pos));
	memset(scc, 0, sizeof(scc));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	cnt = 0;
	timetag = 0;
	
	int from, to;
	char fromc,toc;
	string str[2];
	char ch;
	getline(std::cin, str[0], ';');
	getline(std::cin, str[1]);
	n = stoi(str[0]);
	stringstream ss(str[1]);
	while (ss) {
		ss >> fromc;
		from = fromc - '`';
		ss >> ch;
		ss >> toc;
		to = toc - '`';
		addedge(from, to);
		ss >> ch;
	}
	memset(scc, 0, sizeof(scc));
}

stack<int> s;

void tarjan(int v) {
	s.push(v);
	timetag++;
	dfn[v] = low[v] = timetag;
	int x = pos[v];
	while (x) {
		if (!scc[edges[x].to]) {
			if (!dfn[edges[x].to]) {
				tarjan(edges[x].to);
				low[v] = min(low[v], low[edges[x].to]);
			}
			else {
				low[v] = min(low[v], dfn[edges[x].to]);
			}
		}
		x = edges[x].next;
	}
	if (low[v] == dfn[v]) {
		int x = s.top();
		////printf("int x:%d", x);
		s.pop();
		while (x != v) {
			scc[x] = v;
			//printf("scc[x]:%d ", scc[x]);
			SCC.push_back(x);
			x = s.top();
			s.pop();
		}
		scc[v] = v;
		SCC.push_back(v);
		sort(SCC.begin(), SCC.end());
		ans.push_back(SCC);
		//printf("scc[v]:%d", scc[v]);
		//printf("\n");
		SCC.clear();
	}
	sort(ans.begin(), ans.end());
}
int main() {
	init();
	while (!s.empty()) s.pop();
	for (int i = 1;i <= n;i++) {
		if (!scc[i]) {
			//printf("scc[i]:%d", scc[i]);
			//printf("\n");
			tarjan(i);//
		}
	}
		for (int i = 0; i < ans.size(); i++)
	{
		if (i != 0)cout << ';';
		for (int j = 0; j < ans[i].size(); j++)
		{
			if (j != 0)cout << ',';
			printf("%c", ans[i][j] + '`');
		}
	}
	return 0;
}