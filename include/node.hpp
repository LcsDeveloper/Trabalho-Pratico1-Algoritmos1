#pragma once

typedef struct{
    int x;
    int y;
}Position;

typedef struct{
    int r;
    Position position;
}Abrigo;

class Node{
    public:
        Node();
        Node(int id);
        int id;
        Abrigo abrigo;
};
