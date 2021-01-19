// Ivan Chowdhury
// Cooper Union EE'20
// Data Structures and Algorithms II
// Graph Class

#include "graph.h"

using namespace std;

graph::graph(int capacity) {  
    this->vertex_map = new hashTable(capacity);
}


void graph::Dijkstra(std::string Vsource) {
    heap H(this->vertex_list.size()+1);
    list<vertex *>::iterator it;
    for (it=this->vertex_list.begin(); it!=this->vertex_list.end(); it++) {
        if ((*it)->name == Vsource)
            (*it)->distance = 0;
        else
            (*it)->distance = INT_MAX;
        (*it)->Vprev = NULL;
        (*it)->vertexKnown = false;
        H.insert((*it)->name, (*it)->distance, (*it));
    }

    vertex *v;
    while (H.deleteMin(NULL,NULL,&v) != 1) {
        v->vertexKnown = true;
        list<edge *>::iterator it2;
        if (v->distance == INT_MAX)
            continue;

        for (it2=v->adj.begin(); it2!=v->adj.end(); it2++) {
            int newCost = v->distance + (*it2)->edgeCost;
            if (newCost < (*it2)->Vdest->distance) {
                (*it2)->Vdest->distance = newCost;
                H.setKey((*it2)->Vdest->name,newCost);
                (*it2)->Vdest->Vprev = v;
            }
        }
    }
    return;
}


void graph::insertE(std::string start, std::string end, int distance) {
    this->insertV(start);
    this->insertV(end);

    bool keyExists = false;
    vertex *dest = static_cast<vertex *> (this->vertex_map->getPointer(end, &keyExists));

    edge *E = new edge();
    E->edgeCost = distance;
    E->Vdest = dest;

    vertex *source = static_cast<vertex *> (this->vertex_map->getPointer(start, &keyExists));
    source->adj.push_back(E);

    return;
}


bool graph::insertV(std::string id) {
    if (this->checkV(id))
        return false;

    vertex *v = new vertex();
    v->name = id;

    this->vertex_map->insert(id, v);
    this->vertex_list.push_back(v);
    return true;
}


bool graph::checkV(std::string id) {
    return this->vertex_map->contains(id);
}


void graph::writePath(std::string filename) {
    ofstream out(filename.c_str());
    list<vertex *>::iterator it;
    string path;

    for (it=this->vertex_list.begin(); it!=this->vertex_list.end(); it++) {
        vertex *v = (*it);
        out << (*it)->name << ": ";

        if (v->distance == INT_MAX)
            out << "NO PATH" << endl;
        else if (v->distance == 0)
            out << v->distance << " [" << v->name << "]" << endl;
        else {
            path = v->name;
            out << v->distance << " [";
            
            for (; v->Vprev != NULL; ) {
                path = v->Vprev->name + ", " + path;
                v = v->Vprev;
            }
            out << path << "]" << endl;
        }
    }
    return;
}