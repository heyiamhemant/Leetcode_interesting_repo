
#include<iostream>
using namespace std;

void bfs(Node* top,vector<Node*> neighbours){
    Queue<Node*> Q;
    set<int> visited;
    while(Q) {
        int curr = Q.front()->val;
        visited.insert(curr);
        cout << curr <<endl;
        for(Node* neighbour : neighbours[curr] ) {
            if(visited.find(neighbour->val) == visited.end())
            Q.push(neighbour);
        }
    }
    return;

}
void dfs(Node* top, set<int> visited, vector<Node*> neighbours) {
    int cur = top->val;
    visited.insert(cur);
    for(Node* neighbour : neighbours[curr]) {
        if(visited.find(neighbour->val)) == visited.end())
            dfs(neighbour, visited, neighbours);
    }
        
}

vector<vector<int>> levelOrderTraversal(Node* root) {
    Queue<Node*> Q;
    Q.push(root);
    vector<vector<int>> result;
    while(!Q.empty()){
        int size = Q.size();
        vector<int> level;
        for(int i= 0 ; i < size ; i++) {
            Node* node = Q.front();
            level.push_back(node->val);
            Q.pop();
            if(node->left)
                Q.push(node->left);
            if(node->right)
                Q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}

