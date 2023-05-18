class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> paths;
        stack<int> nodes;
        for(int i: graph[0])
            nodes.push(i);

        vector<int> k;
        k.push_back(0);
        vector<bool> visited(graph.size(),false);
        visited[0]=true;

        while(nodes.size()!=0){
            int idx=nodes.top();
            nodes.pop();
            if(idx==graph.size()-1){
                k.push_back(idx);
                paths.push_back(k);
                k.pop_back();
                continue;
            }
            if(visited[idx]){
                visited[idx]=false;
                k.pop_back();
            }
            else{
                visited[idx]=true;
                k.push_back(idx);
                nodes.push(idx);
                for(int i: graph[idx]){
                    if(!visited[i]){
                        nodes.push(i);
                    }
                }
            }
        }
        return paths;
    }
};
