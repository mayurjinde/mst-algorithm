#include<iostream>
#include<vector>
#include<queue>
#include <stack>
#include <map>
#include <algorithm>
#include<unordered_map>
using namespace std;

vector<pair<int, int>>adj[50];
int adj_mat[50][50] = { 0 };
typedef pair<int, int> pd;

struct myComp {
    constexpr bool operator()(pair<int, int> const& a, pair<int, int> const& b)
        const noexcept
    {
        return a.second < b.second;
    }
};
priority_queue<pd, vector<pd>, myComp> max_degree;
unordered_map<int, int>max_deg_temp;

void dfs_cycle(int u, int p, int color[], int mark[], int par[], int& cyclenumber)
{

    // already (completely) visited vertex.
    if (color[u] == 2) {
        return;
    }

    // seen vertex, but was not completely visited -> cycle detected.
    // backtrack based on parents to find the complete cycle.
    if (color[u] == 1) {

        cyclenumber++;
        int cur = p;
        mark[cur] = cyclenumber;

        // backtrack the vertex which are
        // in the current cycle thats found
        while (cur != u) {
            cur = par[cur];
            mark[cur] = cyclenumber;
        }
        return;
    }
    par[u] = p;

    // partially visited.
    color[u] = 1;

    // simple dfs on graph
    for (auto v : adj[u]) {

        // if it has not been visited previously
        if (v.first == par[u]) {
            continue;
        }
        dfs_cycle(v.first, u, color, mark, par, cyclenumber);
    }

    // completely visited.
    color[u] = 2;
}
bool node_member_cycle(int edges, int mark[], int& cyclenumber, int z, vector<int>cycles[], vector<int>& temp)
{

    // push the edges that into the
    // cycle adjacency list
    for (int i = 1; i <= edges; i++) {
        if (mark[i] != 0)
            cycles[mark[i]].push_back(i);
    }
    int flag = 0;
    // print all the vertex with same cycle
    for (int i = 1; i <= cyclenumber; i++) {
        for (int x : cycles[i]) {
            if (x == z) { flag = 1; }
            temp.push_back(x);
        }


    }
    //cout<<"printing vector\n";
    for (auto x : temp) {
        //cout<<x<<" ";
    }
    //cout<<"\n";
    return flag;
}

// bool node_member_cycle(int node)
// {

// }


void remove_edge(int u, int v)
{
    for (int i = 0; i < adj[u].size(); i++) {
        if (adj[u][i].first == v) {
            adj[u].erase(adj[u].begin() + i);
            break;
        }
    }

    // Traversing through the second vector list
    // and removing the first element from it
    for (int i = 0; i < adj[v].size(); i++) {
        if (adj[v][i].first == u) {
            adj[v].erase(adj[v].begin() + i);
            break;
        }
    }
}

// int node_member_cycle1(int node,int parent,int vis[])
// {
//     stack<pair<int,int>>st;
//     int vis[50]={0};
//     st.push({node,parent});
//     while(!st.empty())
//     {
//         int a=st.top().first;
//         int b=st.top().second;
//         vis[a]++;
//         for(auto x:adj[a])
//         {
//             if(vis[x.first]==1 && x.first!=b)return 1;
//             vis[x.first]=1;

//         }
//     }
// }

void MST_Algo(int e, int v){
    // set<int>s;
    //cout<<"check2\n";
    int t = 25; //e>v-1
    while (e > (v - 1))
    {
        int node = max_degree.top().first;
        int deg = max_degree.top().second;
        //cout<<"check3\n";
        //cout<<node<<" "<<deg<<" "<<e<<endl;
        // e--;
        // max_degree.pop();
        int k = 1;
        while (1)
        {
            //cout<<"check4\n";
            int color[1000] = { 0 };
            int par[1000] = { 0 };
            int mark[1000] = { 0 };
            int cno = 0;
            vector<int>cycles[1000];
            dfs_cycle(1, 0, color, mark, par, cno);
            //cout<<"check7\n";
            vector<int>temp;
            // cout<<node_member_cycle(e,mark,cno,node,cycles)<<"\n";
            // int m_val=INT_MIN;
            // for(auto x:adj[node])if(x.second>m_val)m_val=x.second;
            // cout<<"\nmval="<<node<<" "<<m_val;
            bool myv = node_member_cycle(e, mark, cno, node, cycles, temp);
            //cout<<"Print cycle:"<<myv<<"\n";
            if (myv)
            {
                //cout<<"check5\n";
                int i;
                // int m_val=*max_element(adj_mat[node],adj_mat[node]+v);
                int m_val = INT_MIN;
                for (auto x : adj[node])if (x.second > m_val)m_val = x.second;
                priority_queue<pd, vector<pd>, myComp>tie;
                for (auto x : adj[node])
                {
                    if (x.second == m_val)
                        tie.push({ x.first,max_deg_temp[x.first] });
                }


                remove_edge(node, tie.top().first);
                //cout<<"Now the graph is\n";
                for (int i = 1; i <= v; i++)
                {
                    for (auto x : adj[i])
                    {
                        //cout<<i<<" "<<x.first<<" "<<x.second<<"\n";
                    }
                }
                //cout<<"Graph ends here\n";
                max_deg_temp[node]--;
                max_deg_temp[tie.top().first]--;
                //cout<<"e="<<e<<"\n";
                e--;
            }
            else
            {
                //cout<<"check6\n";
                // s.insert(node);
                max_degree.pop();
                break;
            }

        }
    }
}


int main()
{
#ifndef _CRT_SECURE_NO_WARNINGS
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    int e, v; // e=#Edges, v=#vertices
    cout << "Enter the number of Vertices and Edges in the Graph:\n";
    cin >> v >> e;
    int a, b, wt;
    cout << "Enter the vertices with their corresponding edge weight:\n";
    for (int i = 0; i < e; i++)
    {
        cin >> a >> b >> wt;
        adj[a].push_back({ b,wt });
        adj[b].push_back({ a,wt });
        // adj_mat[a][b]=wt;
        // adj_mat[b][a]=wt;
        max_deg_temp[a]++;
        max_deg_temp[b]++;
    }
    //cout<<"check1\n";

    for (auto x : max_deg_temp)
    {
        // cout<<x.first<<" "<<x.second<<"\n";
        max_degree.push({ x.first,x.second });
    }

    // while (!max_degree.empty()) {
    //     cout << max_degree.top().first
    //          << " " << max_degree.top().second
    //          << endl;
    //     max_degree.pop();
    // }
    // cout << endl;

    MST_Algo(e, v);

    cout << "\n\n\nResultant MST of the Graph:\n";
    for (int i = 1; i <= v; i++)
    {
        for (auto x : adj[i])
        {
            cout << i << " " << x.first << " " << x.second << "\n";
        }
    }
}

/*
4 5
1 2 1
2 3 2
3 4 5
4 1 4
1 3 3
*/


/*
// if(tie.size()>1)
                // {
                //     adj_mat[node][tie.top().first]=0;
                //     adj_mat[tie.top().first][node]=0;
                //     max_deg_temp[node]--;
                //     max_deg_temp[tie.top().first]--;
                // }
                // adj_mat[node][tie.top().first]=0;
                // adj_mat[tie.top().first][node]=0;
                // max_deg_temp[node]--;
                // max_deg_temp[tie.top().first]--;
*/