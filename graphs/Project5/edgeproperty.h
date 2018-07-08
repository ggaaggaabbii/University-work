#ifndef EDGEPROPERTY_H
#define EDGEPROPERTY_H
#include <bits/stdc++.h>

template <typename T>
class EdgeProperty {
    private:
        //we keep a map that maps the id of an edge to a tuple that contains the endpoints and the property
        std::unordered_map<int, std::tuple<int, int, T> > prop;

    public:
        EdgeProperty() {}
        /*
        adds an edge to the map
        input: the edge id, the endpoints of the map, the property
        */
        void addEdge(int edgeId, int source, int dest, T property) {
            prop[edgeId] = std::tuple<int, int, int> {source, dest, property};
        }
        /*
        deletes an edge from the map
        input: the edge id
        */
        void deleteEdge(int edgeId) {
            prop.erase(edgeId);
        }
        /*
        gets a tuple containing the endpoints and property of an edge
        input: the edge id
        */
        std::tuple<int, int, T> getEdge(int edge) {
            if (prop.find(edge) != prop.end()) {
                return prop[edge];
            }

            std::tuple<int, int, T> t{ -1, -1, std::get<2>(prop.begin()->second)};
            return t;
        }
        /*
        updates the property of an edge
        input: the edge id and the new value of the edge
        output: true if the edge exists and can be updated, false otherwise
        */
        bool updateEdge(int edge, T newVal) {
            if (prop.find(edge) == prop.end()) {
                return false;
            }

            int source = std::get<0>(prop[edge]);
            int dest = std::get<1>(prop[edge]);
            std::tuple<int, int, T> t{source, dest, newVal};
            prop[edge] = t;
            return true;
        }
        /*
        the = operator used to make the graph copyable
        */
        EdgeProperty& operator =(EdgeProperty& e) {
            this->prop = e.prop;
            return *this;
        }
};

#endif // EDGEPROPERTY_H
