#include "graph.h"

int main()
{  
    setlocale(LC_ALL, "");
    // создаём объект
    Graph g;
       
    g.addVertex("Ivan");
    g.addVertex("Maria");
    g.addVertex("Kesha");
    g.addVertex("Dormidont");
    g.addVertex("Vasya");
    g.addVertex("Glafira");
    g.addVertex("Klava");
    g.addVertex("Inna");
    g.addVertex("Galja");
    g.addVertex("Stepan");
    g.addVertex("Fjokla");

    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 1);
    g.addEdge(2, 5, 1);
    g.addEdge(1, 4, 1);
    g.addEdge(4, 3, 1);
    g.addEdge(5, 3, 1);
    g.addEdge(4, 7, 1);
    g.addEdge(3, 6, 1);
    g.addEdge(3, 7, 1);
    g.addEdge(3, 8, 1);
    g.addEdge(5, 8, 1);
    g.addEdge(8, 6, 1);
    g.addEdge(7, 6, 1);
    g.addEdge(9, 8, 1);
    g.addEdge(9, 5, 1);
    g.addEdge(10, 6, 1);
    g.addEdge(11, 6, 1);

    //g.depth(0);
    //g.findMinDistanceDecstr(0);
	g.findMinDistancesFloyd();
    g.printFriend(3);
	

    // удаляем вершину и ребро
    //g.delEdge(0,3);
    //g.delVertex(3);

    return 0;
}
