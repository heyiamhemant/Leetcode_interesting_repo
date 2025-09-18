#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int numberOfIslands(vector<vector<int>> islands) {
    int m = islands.size();
    int n = islands[0].size();
    int count = 0;
    for(int i = 0 ; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(islands[i][j] == 1) {
                // increase count when you start bfs
                count++;
                queue<pair<int,int>> Q;
                Q.push({i,j});
                // do bfs
                while(!Q.empty()) {
                    pair<int,int> node = Q.front();
                    // mark as visited
                    int p = node.first ;
                    int q = node.second;
                    islands[p][q] = 0;
                    // add neighbours with 1 
                    vector<pair<int,int>> dim = {{0,1}, {1,0}, {-1,0}, {0,-1}};
                    for(pair<int,int> d : dim) {
                        int index1 = p + d.first;
                        int index2 = p + d.second;
                        if(index1 < m && index1 >= 0 && index2 >= 0 &&index 2 < n && islands[index1][index2] == 1)
                            Q.push({index1, index2});
                    }

                }
            }
        }
    }
    return count;
}

Node* CloneGraph(Node* start) {
    std::map<Node *, Node *> cloneMap;
    std::queue Q;
    std::set<Node *> visited;
    Q.push(start);
    while(!Q.empty()) {
        Node *cur = Q.front();
        std::vector<Node *> neighbours = cur->neighbours;
        Q.pop();
        Node* clone = new Node(cur->val);
        cloneMap[cur] = clone;
        visited.insert(cur);
        for (int i = 0; i < neighbours.size(); i++)
        {
            if(visited.find(neighbours[i]) == visited.end()) {
                Q.push(neighbours[i]);
                clone->neighbours.push_back(new Node(neighbours[i]->val));
            }
        }
    }
    return cloneMap[start];
}