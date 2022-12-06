#include "map.h"
#include "adjmx.h"
#include "unordermap.h"
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
    
    unorderMap um;
    AdjacencyMatrix adj;

    if (inFile.is_open()) {
        string wholeLine;

        getline(inFile, wholeLine);
        //map
        if (mapOrGraph == 1) {
            for (int i = 0; i < 100000; i++) {
                string title;
                string year;
                string temp;
                string genre;
                getline(inFile, temp, '\t');
                getline(inFile, temp, '\t');
                getline(inFile, title, '\t');
                getline(inFile, temp, '\t');
                getline(inFile, temp, '\t');
                getline(inFile, year, '\t');
                getline(inFile, temp, '\t');
                getline(inFile, temp, '\t');
                getline(inFile, genre);
               

                movie c(title, genre, year);
                um.insert(title, c);

                //m.mapInsert(title, c, false);
            }
        }
        //graph
        else {
            for (int i = 0; i < 100; ++i) {
                for (int j = 0; j < 1000; ++j) {
                   
                    string title;
                    string year;
                    string temp;
                    string genre;
                    

                    getline(inFile, temp, '\t');
                    getline(inFile, temp, '\t');
                    getline(inFile, title, '\t');
                    getline(inFile, temp, '\t');
                    getline(inFile, temp, '\t');
                    getline(inFile, year, '\t');
                    getline(inFile, temp, '\t');
                    getline(inFile, temp, '\t');
                    getline(inFile, genre);

                    
                    movie c(title, genre, year);
                    adj.InsertEdge(i, j, c);

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

        if (rec == 3) {
            cout << "Thank you for using our recommendation system! Bye!" << endl;
            rec = 3;
            break;
        }
        
        
        
        if (mapOrGraph == 1) {
            if (rec == 1) {
                
                cout << "Enter the movie name: " << endl;
                string title;
                cin >> title;
                um.SearchRelatedGenre(title);
            }
            else if (rec == 2) {
                
                cout << "Enter the movie name : " << endl;
                string title;
                cin >> title;
                um.SearchRelatedYear(title);
            }

           
        }
        else {
            if (rec == 1) {
                cout << "Enter the movie name: " << endl;
                string title;
                cin >> title;
                for (int i = 0; i < 100; ++i) {
                    for (int j = 0; j < 1000; ++j) {
                        if (adj.graph[i][j].name == title) {
                            adj.SearchRelatedGenre(adj.graph[i][j]);
                        }
                    }

                }
                

            }
            else if (rec == 2) {
                cout << "Enter the movie name: " << endl;
                string title;
                cin >> title;
                for (int i = 0; i < 100; ++i) {
                    for (int j = 0; j < 1000; ++j) {
                        if (adj.graph[i][j].name == title) {
                            adj.SearchRelatedYear(adj.graph[i][j]);
                        }
                    }

                }
                
            }
            

        }
}
    
}