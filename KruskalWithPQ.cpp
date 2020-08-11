#include<bits/stdc++.h>
using namespace std;

typedef struct edge{
    int p,q,weight;
    edge(int p,int q,int w):p(p),q(q),weight(w){};
}edge;

class compareEdges{
    public:
        bool operator()(edge a,edge b){
            if(a.weight >= b.weight){
                return 1;
            }
            return 0;
        }
};   

int get_root(int p,vector<int>& arr){
    //Store the value of root for later traversal
    int root = p;
    while(root != arr[root]){
        //We speed up the traversal by checking with grandparent instead of parent.
        root = arr[arr[root]];
    }
    //Consider that during a connect operation a smaller tree gets connected to larger tree.
    //So the next time a node belonging to smaller tree is needed we have to adjust its root to the root of larger tree.
    while(p != root){
        int node_in_way = arr[p];
        arr[p] = root;
        p = node_in_way;
    }
    return root;
}

void connect(int proot,int qroot,vector<int>& sz, vector<int>& arr){

    //If proot is the larger tree then qroot (smaller tree) will get appended to it.
    if(sz[proot] > sz[qroot]){
        //Parent of qroot changes to proot
        arr[qroot] = proot;
        //Adjust the size of proot since more children were added to it.
        sz[proot] += sz[qroot];
    }
    //If qroot is the larger tree.
    else{
        arr[proot] = qroot;
        sz[qroot] += sz[proot];
    }
}

int main(void){
    int v,e;
    cin >> v >> e;
    vector<int> arr(v);
    vector<int> sz(e,1);
    for(int i = 0;i < v;i++){
        arr[i] = i;
    }

    priority_queue<edge,vector<edge>,compareEdges> edges;
    vector<int> loop_node(v,INT_MAX);
    for(int i = 0;i < e;i++){
        int p,q,w;
        cin >> p >> q >> w;
        //If it is a loop node then dont add it to the main edges array.
        if(p == q){
            if(w < loop_node[p]){
                loop_node[p] = w;
            }
        }else if(p != q){
            edge e(p,q,w);
            edges.push(e);
        }
    }
    int count_edges = 0;
    queue<pair<pair<int,int>,int>> mst;
    while(!edges.empty() && count_edges < v - 1){
        auto i = edges.top();
        int r1 = get_root(i.p,arr);
        int r2 = get_root(i.q,arr);
        edges.pop();
        //If they have same roots then continue.
        if(r1 == r2){
            continue;
        }
        //Add the new edge.
        else{
            connect(r1,r2,sz,arr);
            count_edges += 1;
            mst.push(make_pair(make_pair(i.p,i.q),i.weight));
        }

    }
    
    //Print the mst.
    while(!mst.empty()){
        auto e = mst.front();
        cout << "Edge: (" << e.first.first << ',' << e.first.second << ") Weight: " << e.second << '\n';
        mst.pop();
    }
}