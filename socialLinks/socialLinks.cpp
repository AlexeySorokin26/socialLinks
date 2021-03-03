#include <iostream>
#include "Person.h"
#include "Graph.h"

int Person::counter = 0;


int main() {

    const int sizeOfSocialNetwork = 8;

    std::string names[sizeOfSocialNetwork] = {
        "alexey", "irina", "viktor", "elena", "olga", "vladimir", "keisi", "pavel" };
    
    Person* persons = new Person[sizeOfSocialNetwork];

    for (int i = 0; i < sizeOfSocialNetwork; ++i)
        persons[i].SetName(names[i]);

    Graph graph(persons);
    graph.addEdge(persons[0], persons[1], 1);
    graph.addEdge(persons[0], persons[2], 1);
    graph.addEdge(persons[0], persons[3], 1);
    graph.addEdge(persons[0], persons[4], 1);
    graph.addEdge(persons[0], persons[5], 1);
    

    graph.addEdge(persons[1], persons[6], 1);
    graph.addEdge(persons[6], persons[7], 1);

    auto pair = graph.findAll3HandshakeFor(4);

    delete[] persons;
    return 0;
}

