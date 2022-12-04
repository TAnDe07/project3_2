//
// Created by tanad on 11/14/2022.
//

#ifndef COP3530PROJECT3_GRAPH_H
#define COP3530PROJECT3_GRAPH_H

#endif //COP3530PROJECT3_GRAPH_H
#include "movie.h"

class AdjacencyMatrix {
private:
    //Think about what member variables you need to initialize
    vector<vector<movie>> graph;
    movie getMovie(string title);
public:
    //Think about what helper functions you will need in the algorithm
    void InsertEdge (int i, int j, movie m);
    vector<movie> SearchRelated(int selection, string m);
    vector<pair<int, int>> CurrentIndices(movie m);
    vector<pair<movie, vector<pair<int, int>>>> SearchRelatedGenre(movie m, vector<string> genre);
    vector<pair<movie, vector<pair<int, int>>>> SearchRelatedYear(movie m);
};


//first five of similar genre/duration
vector<movie> AdjacencyMatrix::SearchRelated(int selection, string title) {
    movie m  = getMovie(title);
    vector<movie> recommended;
    vector<pair<movie, vector<pair<int, int>>>> temp;
    if (selection == 1) {
        temp =  SearchRelatedGenre(m, m.genre);
    }
    else if (selection == 2) {
        temp = SearchRelatedYear(m);
    }

    vector<pair<int, int>> currentIndices;
    while (recommended.size() < 5) {
        vector<pair<int, int>> visited;
        int leastI = 101;
        int leastJ = 1001;
        for (int i = 0; i < temp.size(); ++i) {
            int tempLeastI = temp.at(i).second.at(0).first;
            int tempLeastJ = temp.at(i).second.at(0).second;
            if (tempLeastI < leastI && tempLeastJ < leastJ) {
                bool visited2 = false;
                for (int j = 0; j < visited.size(); ++j) {
                    if (visited.at(i).first == tempLeastI && visited.at(i).second == tempLeastJ) {
                        visited2 = true;
                    }
                }
                if (visited2 == false) {
                    leastJ = tempLeastJ;
                    leastI = tempLeastI;
                }
            }
            recommended.push_back(graph[leastI] [leastJ]);
        }
    }
    return recommended;
}

movie AdjacencyMatrix:: getMovie(string title) {

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.at(i).size(); ++j) {
            if (graph[i][j].name == title) {
                return graph[i][j];
            }
        }
    }
}

vector<pair<int, int>>  AdjacencyMatrix::CurrentIndices(movie m) {
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.at(i).size(); ++j) {
            if (graph[i][j].name == m.name) {
                vector<pair<int, int>> indices;
                indices.emplace_back(i, j);
                return indices;
            }
        }
    }
}

void AdjacencyMatrix::InsertEdge(int i, int j, movie m) {
    graph[i][j] = m;
    graph[j][i] = m;
}

vector<pair<movie, vector<pair<int, int>>>> AdjacencyMatrix::SearchRelatedGenre(movie m, vector<string> genre){
    vector<pair<movie, vector<pair<int, int>>>> list;

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.at(i).size(); ++j) {

            for (int k = 0; k < graph[i][j].genre.size(); ++k) {
                for (int l = 0; l < m.genre.size(); ++l) {
                    if (graph[i][j].genre.at(k) == m.genre.at(l)) {
                        vector<pair<int, int>> temp;
                        temp.emplace_back(i, j);
                        list.emplace_back(graph[i][j], temp);
                    }
                }
            }
        }
    }
    return list;
}

vector<pair<movie, vector<pair<int, int>>>> AdjacencyMatrix::SearchRelatedYear(movie m) {
    vector<pair<movie, vector<pair<int, int>>>> list;

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.at(i).size(); ++j) {
            int range = stoi(graph[i][j].year) - stoi(m.year);
            if (range > -5 || range < 5) {
                vector<pair<int, int>> temp;
                temp.emplace_back(i, j);
                list.emplace_back(graph[i][j], temp);
            }
        }
    }
    return list;
}
