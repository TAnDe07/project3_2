#pragma once
#include "movie.h"

class unorderMap {
	
public:
	
	list<list<pair<string,movie>>>hashTable[100];
	
	
	
	int hashfunction(string title) {
		return (title.size() % 100);

	}

	void insert(string key, movie value) {

		hashTable[hashfunction(key)].emplace_back(key, value);
	}


	void SearchRelatedGenre(string title) {
		string genre;
		int count = 0;
		vector<string>movieGenres;

		for (int i = 0; i < 100;i++) {

			auto it = hashTable[i].begin();
			for (; it != hashTable[i].end(); it++) {
				auto it1 = (*it).begin();
				for (; it1 != (*it).end(); it++) {
					if (it1->first == title) {
						genre = it1->second.genre;
					}
				}
			}
		}

		for (int i = 0; i < 100; i++) {
			auto it = hashTable[i].begin();
			for (; it != hashTable[i].end(); it++) {
				auto it1 = (*it).begin();
				for (; it1 != (*it).end(); it++) {
					if (count == 5) {
						break;
					}
					
					if (it1->second.genre == genre) {
						movieGenres.push_back(it1->first);
						count++;
					}

				}
			}
		}
		for (int i = 0; i < movieGenres.size(); i++) {
			cout << movieGenres[i] << endl;


		}



	}


	void SearchRelatedYear(string title) {
		string year;
		int count = 0;
		vector<string>movieYears;

		for (int i = 0; i < 100; i++) {

			auto it = hashTable[i].begin();
			for (; it != hashTable[i].end(); it++) {
				auto it1 = (*it).begin();
				for (; it1 != (*it).end(); it++) {
					if (it1->first == title) {
						year = it1->second.year;
					}
				}
			}
		}

		for (int i = 0; i < 100; i++) {
			auto it = hashTable[i].begin();
			for (; it != hashTable[i].end(); it++) {
				auto it1 = (*it).begin();
				for (; it1 != (*it).end(); it++) {
					if (count == 5) {
						break;
					}

					if (it1->second.year == year) {
						movieYears.push_back(it1->first);
						count++;
					}

				}
			}
		}
		for (int i = 0; i < movieYears.size(); i++) {
			cout << movieYears[i] << endl;


		}



	}


};