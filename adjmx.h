#pragma once

#ifndef COP3530PROJECT3_GRAPH_H
#define COP3530PROJECT3_GRAPH_H

#endif //COP3530PROJECT3_GRAPH_H
#include "movie.h"

class AdjacencyMatrix {
private:
    //Think about what member variables you need to initialize
    
public:
    vector <vector<movie>> graph;
    //Think about what helper functions you will need in the algorithm
    void InsertEdge(int i, int j, movie m);
    vector<movie> SearchRelatedGenre(movie m);
    vector<movie> SearchRelatedYear(movie m);

};

//first five of similar genre
vector<movie> AdjacencyMatrix::SearchRelatedGenre(movie m) {
    vector<movie> movies;
    int count = 0;
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.at(i).size(); ++j) {
            if (count == 5) {
                break;
            }
            if (graph[i][j].genre == m.genre) {
                movies.push_back(m);
                count += 1;
            }

        }
    }
    for (auto it = movies.begin(); it != movies.end(); it++) {
        cout << it->name << endl;
    }
    return movies;
}
//first five of similar duration
vector<movie> AdjacencyMatrix::SearchRelatedYear(movie m) {
    vector<movie> movies;
    int count = 0;
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.at(i).size(); ++j) {
            if (count == 5) {
                break;
            }

            if (graph[i][j].year == m.year) {
                movies.push_back(m);
                count += 1;
            }
        }
    }
    for (auto it = movies.begin(); it != movies.end(); it++) {
        cout << it->name << endl;
    }
    return movies;
}

//first five of similar genre/duration



void AdjacencyMatrix::InsertEdge(int i, int j, movie m) {
    graph[i][j] = m;
    graph[j][i] = m;
}