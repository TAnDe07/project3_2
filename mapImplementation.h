#include "movie.h"

class map {
private:
    struct Node {
        string key;
        movie value;
        bool redOrBlack; //Red = false, black = true;
        Node *left;
        Node *right;
        Node *parent;

        Node(string key, movie value, bool red, Node *parent, Node *left, Node *Right) : key(key), value(value),
                                                                                      redOrBlack(red),
                                                                                      parent(parent), left(nullptr),
                                                                                      right(nullptr) {}
    };

    Node *root = nullptr;

    void leftRotation(Node *helperRoot, Node *temp) {
        Node *y = temp->right;
        temp->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = temp;
        }
        y->parent = temp->parent;
        if (temp->parent == nullptr) { //x is root
            helperRoot = y;
        } else if (temp == temp->parent->left) { // x is left child
            temp->parent->left = y;
        } else {// x is right child
            temp->parent->right = y;
        }
        y->left = temp;
        temp->parent = y;

    }

    void rightRotation(Node *helperRoot, Node *temp) {
        Node *y = temp->left;
        temp->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = temp;
        }
        y->parent = temp->parent;
        if (temp->parent == nullptr) {
            helperRoot = y;
        } else if (temp == temp->parent->right) {
            temp->parent->right = y;
        } else {// x is right child
            temp->parent->left = y;
        }
        y->right = temp;
        temp->parent = y;

    }

    vector<Node*> helperMapSearchGenre(Node *helperRoot, string first) {
        Node *temp = helperMapSearch(helperRoot, first);
        vector<string> genres;
        vector<Node *> recommended;
        if (temp != nullptr) {
            inorderHelperGenre(temp, recommended, genres);
        }
        return recommended;
    }

    vector<Node *>helperMapSearchYear(Node *helperRoot, string first) {
        Node *temp = helperMapSearch(helperRoot, first);
        int year;
        vector<Node *> recommended;
        if (temp != nullptr) {
            year = stoi(temp->value.year);
            inorderHelperYear(temp, recommended, year);
        }
        return recommended;
    }

    void inorderHelperGenre(Node *helperRoot, vector<Node *> &movies, vector<string> genre) {
        //if tree is empty
        if (movies.size() == 5) {
            return;
        }
        //gets reference of info inorder and stores them in vector
        inorderHelperGenre(helperRoot->left, movies, genre);
        for (int i = 0; i <  helperRoot->value.genre.size(); ++i) {
            for (int j = 0; j < genre.size(); ++j) {
                if (helperRoot->value.genre.at(i) == genre.at(j)){
                    movies.push_back(helperRoot);
                    break;
                }
            }
        }
        inorderHelperGenre(helperRoot->right, movies, genre);
    }

    void inorderHelperYear(Node *helperRoot, vector<Node *> &movies, int year) {
        //if tree is empty
        if (movies.size() == 5) {
            return;
        }
        //gets reference of info inorder and stores them in vector
        inorderHelperYear(helperRoot->left, movies, year);
        int range = stoi(helperRoot->value.year) - year;
        if (range < 5 && range > - 5){
            movies.push_back(helperRoot);
        }
        inorderHelperYear(helperRoot->right, movies, year);
    }

    map::Node *helperMapSearch(Node *helperRoot, string first) {
        Node *temp = helperRoot;
        //while id is not found
        while (temp != nullptr && temp->key != first) {
            //if id is greater than current id, go to right subtree
            if (temp->key < first) {
                temp = temp->right;
            }
                //if id is less than current id, go to left subtree
            else {
                temp = temp->left;
            }
        }
        //if id is found
        if (temp != nullptr && temp->key == first) {

            return temp;
        }
        return nullptr;
    }

    map::Node *helperMapInsert(Node *helperRoot, string first, movie second, bool red) {
        // if tree is empty, insert at root
        if (helperRoot == nullptr) {
            return new Node(first, second, true, nullptr, nullptr, nullptr);
        }
            // if id is less than current id, go to left subtree
        else if (helperRoot->key > first) {
            helperRoot->left = helperMapInsert(helperRoot->left, first, second, red);
        }
            // if id is greater than current id, go to right subtree
        else if (helperRoot->key < first) {
            helperRoot->right = helperMapInsert(helperRoot->right, first, second, red);
        }
            // if id is equal to current id, print unsuccessful, and return
        else if (helperRoot->key == first) {
            return helperRoot;
        }
        //balance tree after insertion
        return balanced(helperRoot, first, second, red);
    }

    map::Node *balanced(Node *helperRoot, string first, movie second, bool red) {

        Node *k = helperMapSearch(helperRoot, first);
        while (k->parent->redOrBlack == false) {
            if (k->parent == k->parent->parent->right) {
                Node *u = k->parent->parent->left;
                if (u->redOrBlack == false) {
                    u->redOrBlack = true;
                    k->parent->redOrBlack = true;
                    k->parent->parent->redOrBlack = false;
                    k = k->parent->parent;
                }
                else if (k == k->parent->left) {
                    k = k->parent;
                    leftRotation(helperRoot, k);
                    k->parent->redOrBlack = true;
                    k->parent->parent->redOrBlack = false;
                    rightRotation(helperRoot, k->parent->parent);
                }
                else {
                    k = k->parent;
                    rightRotation(helperRoot, k);
                    k->parent->redOrBlack = true;
                    k->parent->parent->redOrBlack = false;
                    leftRotation(helperRoot, k->parent->parent);
                }
                helperRoot->redOrBlack = true;
            }
        }
        return helperRoot;
    }
public:

    vector<Node *> mapSearch(int selection, string first) {
        vector <Node*> recommended;
        //genre
        if (selection == 1) {
            recommended = helperMapSearchGenre(this->root, first);
        }
            //year
        else if (selection == 2) {
            recommended = helperMapSearchYear(this->root, first);
        }
        return recommended;
    }

    void mapInsert(string first, movie second, bool red) {
        this->root = helperMapInsert(this->root, first, second, red);

    }

};