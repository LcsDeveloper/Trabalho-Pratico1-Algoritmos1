#include<iostream>
#include<list>
#include<vector>
#include<set>
#include<cmath>
#include<utility>

#include"../include/node.hpp"
#include"../include/graph.hpp"

using namespace std;

//distancia euclidiana
float dist(Position posi1, Position posi2){
	return (float) sqrt(pow(abs(posi1.x-posi2.x), 2)+pow(abs(posi1.y-posi2.y), 2));
}

int main(){
    Position ana;
    Position bernado;
    int n;

    cin >> ana.x; cin >> ana.y;
    cin >> bernado.x; cin >> bernado.y;
    cin >> n;

	Graph graph(n);
    vector<Node> nodes;

	//pegando os abrigos e atribuindo eles aos nodes
    for(int i = 0; i < n; i++){
        Node node(i);
        cin >> node.abrigo.r; cin >> node.abrigo.position.x; cin >> node.abrigo.position.y;
        nodes.push_back(node);
    }

	//criando as arestas do grafo que representa as barracas e suas interseções
	for(long unsigned int i = 0; i < nodes.size(); i++){
		for(long unsigned int j = 0; j < nodes.size(); j++){
			if(i != j) graph.makeEdge(nodes[i], nodes[j]);
		}
	}

	//nodes que estão mais próximos a posição inicial de ana e bernado
	Node node_ana = nodes[0];
	Node node_bernado = nodes[0];

	for(auto it : nodes){
		if(dist(node_ana.abrigo.position, ana) > dist(it.abrigo.position, ana)){
			node_ana = it;
		}
		if(dist(node_bernado.abrigo.position, bernado) > dist(it.abrigo.position, bernado)){
			node_bernado = it;
		}
	}

	cout << "Parte 1: " << graph.shortestPath(node_ana, node_bernado) << endl;
	cout << "Parte 2: " << graph.greatestPath() << endl;
	set<long unsigned int> cut = graph.cutNodes();
	cout << "Parte 3: " << cut.size() << " ";
	for(auto it : cut) cout << it << " ";
	cout << endl;
	
    return 0;
}