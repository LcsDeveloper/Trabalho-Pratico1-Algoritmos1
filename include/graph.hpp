#pragma once
#include<iostream>
#include<list>
#include<vector>
#include<set>
#include<cmath>
#include<utility>
#include"node.hpp"

using namespace std;

class Graph{
    public:
        Graph(int v); //constroí o grafo
        void makeEdge(Node node1, Node node2); //adiciona uma aresta entre dois nós (se possível)
        void printGraph(); //printa o grafo para debug
        int shortestPath(Node start, Node end); //retorna o menor caminho entre dois vertices
        int greatestPath(); //retorna o diametro do grafo
        set<long unsigned int> cutNodes(); //retorna um conjunto com os indices dos vertices de corte

    private:
        void _DFStree(Node fnode, vector<pair<int, int>> &visited, list<Node> &mst_order); //gera uma DFStree, onde visited é um vetor de pares p(tempo em que foi visitado, indice do pai), e mst_order é uma lista que guarda a ordem de visitação dos vertices (ultimo visitado para o primeiro visitado)
        vector<int> _sizePaths(long unsigned int idx); //retorna o tamanho dos caminhos a partir de um dado vertice
        bool _ruleForEdge(Node node1, Node node2); //returna verdadeiro se node1 está conectado com node2
        vector<list<Node>> graph;
};
