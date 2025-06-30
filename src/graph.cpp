#include"../include/graph.hpp"

Graph::Graph(int v){
    graph = vector<list<Node>>(v);
}

void Graph::makeEdge(Node node1, Node node2){
    if(_ruleForEdge(node1, node2)){
        graph[node1.id].push_back(node2);
    }
}

void Graph::printGraph(){
    int i = 0;
    for(auto it1 : graph){
        cout << i << ": ";
        for(auto it2 : it1){
            cout << it2.id << " | ";
        }
        cout << endl;
        i++;
    }
}

int Graph::shortestPath(Node start, Node end){
    vector<int> visited(graph.size(), 0);
    vector<int> size_path(graph.size(), 0);
    list<Node> next_node;

    if(!graph[start.id].empty()){
        for(auto it : graph[start.id]){
            next_node.push_back(it);
            visited[it.id] = 1;
            size_path[it.id]++;
        }
    }
    visited[start.id] = 1;
    
    while(!next_node.empty()){
        Node node = next_node.front();
        next_node.pop_front();

        if(node.id == end.id) return size_path[node.id];
     
        if(!graph[node.id].empty()){
            for(auto it : graph[node.id]){
                if(!visited[it.id]){
                    next_node.push_back(it);
                    visited[it.id] = 1;
                    size_path[it.id] = size_path[node.id] + 1;
                }
            }
        }
    }

    return -1;
}

int Graph::greatestPath(){
    vector<int> size_path_local(graph.size(), 0);
    vector<int> size_path_global(graph.size(), 0);
    bool every_node_visited = false;
    long unsigned int i = 0;

    //k (k = numero componentes conexos)
    while(!every_node_visited){
        //vc+ec
        size_path_local = _sizePaths(i);
        int max = 1;
        //v
        for(long unsigned int j = 0; j < size_path_local.size(); j++){
            if(max < size_path_local[j]){
                max = size_path_local[j];
                i = j;
            }
        }
        //vc+ec (vc = vertices do componente conexo; ec = arestas componente conexo)
        size_path_local = _sizePaths(i);

        // v
        for(long unsigned int k = 0; k < size_path_local.size(); k++){
            if(size_path_local[k] != 0) size_path_global[k] = size_path_local[k];
        }

        //v
        every_node_visited = true;
        for(i = 0; i < size_path_global.size(); i++){
            if(!size_path_global[i]){
                every_node_visited = false;
                break;
            }
        }
    }

    //v
    int max = 0;
    for(i = 0; i < size_path_global.size(); i++){
        if(max < size_path_global[i]){
            max = size_path_global[i];
        }
    }

    return max;
}

set<long unsigned int> Graph::cutNodes(){
    vector<int> time(graph.size(), 0);
    vector<int> low(graph.size(), -1);
    vector<int> childs(graph.size(), 0);
    vector<int> parents(graph.size(), -1);
    
    //k, onde k é o número de componentes conexos
    int i = 0;
    while(i >= 0){
        vector<pair<int, int>> mst(graph.size(), pair<int, int>(0, -1));
        list<Node> mst_order;

        //O(v + e)
        _DFStree(i, mst, mst_order);

        //O(v)
        for(long unsigned int j = 0; j < mst.size(); j++){
            if(mst[j].second != -1){
                childs[mst[j].second]++;
                parents[j] = mst[j].second;
            }
        }

        //O(v)
        for(long unsigned int j = 0; j < mst.size(); j++){
            if(mst[j].first != 0) time[j] = mst[j].first;
        }

        //O(Vi) onde Vi é o numero de vertices na componente conexo i = 1, 2, ... , k
        for(auto it : mst_order){
            low[it.id] = time[it.id];
        }

        //O(Vi + Ei) onde Ei é o numero de arestas que ligam algum v do total de Vi a algum outro vertice. i = 1, 2, ... , k
        for(auto it1 : mst_order){
            for(auto it2 : graph[it1.id]){
                if(mst[it1.id].second != it2.id) low[it1.id] = min(low[it1.id], time[it2.id]);
            }
            low[mst[it1.id].second] = min(low[mst[it1.id].second], low[it1.id]);
        }

        //O(v)
        i = -1;
        for(long unsigned int k = 0; k < time.size(); k++){
            if(time[k] == 0){
                i = (int) k;
                break;
            }
        }
    }

    //O(v)
    set<long unsigned int> cut_nodes;
    for(long unsigned int j = 0; j < parents.size(); j++){
        if(parents[j] == -1 && childs[j] >=2) cut_nodes.insert(j+1);
        else if(parents[j] != -1 && parents[parents[j]] != -1 && low[j] >= time[parents[j]]){
            cut_nodes.insert(parents[j]+1);
        }
    }

    return cut_nodes;
}


//-----Private Methods-----

bool Graph::_ruleForEdge(Node node1, Node node2){
    float a = (float) node1.abrigo.r;
    float b = (float) node2.abrigo.r;
    float c = (float) sqrt(pow(abs(node1.abrigo.position.x - node2.abrigo.position.x),2) +
                   pow(abs(node1.abrigo.position.y - node2.abrigo.position.y),2));
    if(a + b < c) return false;
    return true;
}

vector<int> Graph::_sizePaths(long unsigned int idx){
    vector<int> visited(graph.size(), 0);
    vector<int> size_path(graph.size(), 0);
    list<Node> next_node;
    
    if(!graph[idx].empty()){
        for(auto it : graph[idx]){
            next_node.push_back(it);
            visited[it.id] = 1;
            size_path[it.id]++;
        }
    }
    visited[idx] = 1;
    size_path[idx] = -1;
    
    while(!next_node.empty()){
        Node node = next_node.front();
        next_node.pop_front();
     
        if(!graph[node.id].empty()){
            for(auto it : graph[node.id]){
                if(!visited[it.id]){
                    next_node.push_back(it);
                    visited[it.id] = 1;
                    size_path[it.id] = size_path[node.id] + 1;
                }
            }
        }
    }

    return size_path;
}

void Graph::_DFStree(Node fnode, vector<pair<int, int>> &visited, list<Node> &mst_order){
    int time = 1;
    list<Node> next_node;

    if(!graph[fnode.id].empty()){
        for(auto it : graph[fnode.id]){
            next_node.push_front(it);
            visited[it.id].second = fnode.id;
        }
    }
    mst_order.push_front(fnode);
    visited[fnode.id].first = time;
    
    while(!next_node.empty()){
        Node node = next_node.front();
        next_node.pop_front();

        if(!visited[node.id].first){
            visited[node.id].first = ++time;
            mst_order.push_front(node);
        }
     
        if(!graph[node.id].empty()){
            for(auto it : graph[node.id]){
                if(!visited[it.id].first){
                    next_node.push_front(it);
                    visited[it.id].second = node.id;
                }
            }
        }
    }
}
