#include<bits/stdc++.h>
using namespace std;

int main(void){
    int v,e;
    cin >> v >> e;
    vector<int> arr(v);
    vector<int> sz(e,1);
    for(int i = 0;i < v;i++){
        arr[i] = i;
    }
    int inf = INT_MAX;
    vector<int> dist(v+1,inf);
    vector<bool> visited(v+1,false);
    vector<vector<pair<int,int>>> adj_list(v+1);
    vector<int> loop_node(v);
    for(int i = 0;i < e;i++){
        int p,q,w;
        cin >> p >> q >> w;
        if(p == q){
            if(w < loop_node[p]){
                loop_node[p] = w;
            }
        }else{
            adj_list[p].push_back(make_pair(w,q));
            adj_list[q].push_back(make_pair(w,p));
        }
    }
    int s;
    cin >> s;
    visited[s] = true;
    dist[s] = 0;
    set<pair<int,int>> pq;
    pq.insert(make_pair(0,s));
    int w = 0;
    while(!pq.empty()){
        auto i = *pq.begin();
        int temp_w = i.first;
        w += temp_w;
        int temp_s = i.second;
        visited[temp_s] = true;
        pq.erase(pq.begin());
        for(auto j = adj_list[temp_s].begin();j != adj_list[temp_s].end();j++){
            int temp_jw = j->first;
            int temp_js = j->second;
            if(!visited[temp_js]){
                if(dist[temp_js] > temp_jw){
                    if(dist[temp_js] != inf){
                        pq.erase(pq.find(make_pair(dist[temp_js],temp_js)));
                    }
                    dist[temp_js] = temp_jw;
                    pq.insert(make_pair(temp_jw,temp_js));
                }
            }
        }
    }
    cout << w << '\n';
}