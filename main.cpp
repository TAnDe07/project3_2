#include"mapImplementation.h"
#include "graph.h"
#include "fstream"

int main() {
    int mapOrGraph = 0;
    int rec = 0;
    cout << "Hello! Welcome to Movies/TV Series Recommendation Generator" << endl;
    cout << "  " << endl;
    cout << "            Menu      " << endl;
    cout << "-------------------------------" << endl;
    cout << "1. MAP" << endl;
    cout << "2. GRAPH" << endl;
    cout << "-------------------------------" << endl;
    cout << "Menu Choice: ";
    cin >> mapOrGraph;
    cout << endl;


    string fileName = "data.tsv";

    ifstream inFile(fileName);
    map m;
    AdjacencyMatrix graph;

    if (inFile.is_open()) {
        string wholeLine;
       
        getline(inFile, wholeLine);
        //map
        if (mapOrGraph == 1) {
            for (int i = 0; i < 100000; i++) {
                string title;
                string year;
                string temp;
                string genre2;
                getline(inFile, temp, '\t');
                getline(inFile, temp, '\t');
                getline(inFile, title, '\t');
                getline(inFile, temp, '\t');
                getline(inFile, temp, '\t');
                getline(inFile, year, '\t');
                getline(inFile, temp, '\t');
                getline(inFile, temp, '\t');
                getline(inFile, genre2);
                vector<string> genre;

                for (int j = 0; j < genre2.size(); ++j) {
                    if (genre2.at(j) == ',') {
                        genre.push_back(genre2.substr(2, j - 2));
                        genre2.erase(0, j + 1);
                        j = 0;
                    }
                    else if (j == genre2.size() - 1) {
                        genre.push_back(genre2);
                    }
                }
                movie c(title, genre, year);
                m.mapInsert(title, c, false);
            }
        }
        //graph
        else {
            for (int i = 0; i < 100; ++i) {
                for (int j = 0; j < 1000; ++j) {
                    /*string wholeLine;
                    string title;
                    vector<string> genre;
                    string year;
                    string genre2;
                    getline(inFile, wholeLine);
                    */
                    string title;
                    string year;
                    string temp;
                    string genre2;
                    vector<string> genre;
                   
                    getline(inFile, temp, '\t');
                    getline(inFile, temp, '\t');
                    getline(inFile, title, '\t');
                    getline(inFile, temp, '\t');
                    getline(inFile, temp, '\t');
                    getline(inFile, year, '\t');
                    getline(inFile, temp, '\t');
                    getline(inFile, temp, '\t');
                    getline(inFile, genre2);
                    
                    for (int j = 0; j < genre2.size(); ++j) {
                        if (genre2.at(j) == ',') {
                            genre.push_back(genre2.substr(2, j - 2));
                            genre2.erase(0, j + 1);
                            j = 0;
                        }
                        else if (j == genre2.size() - 1) {
                            genre.push_back(genre2);
                        }
                    }
                    movie c(title, genre, year);
                    graph.InsertEdge(i, j, c);

                }

            }
        }
    }

    while (rec != 3) {
        cout << "Type of recommendation" << endl;
        cout << "-------------------------------" << endl;
        cout << "1.Search by genre recommendation" << endl;
        cout << "2.Search by year recommendation" << endl;
        cout << "3.Exit" << endl;
        cout << "-------------------------------" << endl;
        cout << "Menu Choice: ";
        cin >> rec;
        cout << endl;

        if (mapOrGraph == 1) {
            if (rec == 1) {
                cout << "Enter the movie name: " << endl;
                string title;
                cin >> title;
                m.mapSearch(rec, title);
            }
            else if (rec == 2) {
                cout << "Enter the movie name: " << endl;
                string title;
                cin >> title;
                m.mapSearch(rec, title);
            }

            if (rec == 3) {
                cout << "Thank you for using our recommendation system! Bye!" << endl;
                rec = 3;
            }
        }
        else {
            if (rec == 1) {
                cout << "Enter the movie name: " << endl;
                string title;
                cin >> title;
                graph.SearchRelated(rec, title);
            }
            else if (rec == 2) {
                cout << "Enter the movie name: " << endl;
                string title;
                cin >> title;
                graph.SearchRelated(rec, title);
            }
            if (rec == 3) {
                cout << "Thank you for using our recommendation system! Bye!" << endl;
                rec = 3;
            }
        
        }

        
    }
}