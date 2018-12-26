#include <locale.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct Entity{
	string Query;
	float Frequency;
};

using Vocabulary = multimap<string, Entity>;

void print(Entity a) {
	cout << "   " << a.Query << " - " << a.Frequency << endl;
};


vector<Entity> suggest(const Vocabulary & slovar, const string& currentWord) {
	vector<Entity> nextword;
	for (auto i = (slovar.equal_range(currentWord)).first; i != (slovar.equal_range(currentWord)).second; i++) {
		nextword.push_back(i->second);
	}
	sort(nextword.begin(), nextword.end(), [](Entity a, Entity b) {
		return (a.Frequency > b.Frequency);
	});
	return nextword;
};


multimap<string, Entity> load(const string& filename) {
	multimap<string, Entity> nextword;
	ifstream file;
	string key;
	string query;
	float frequency;
	file.open("Vocabularyionary.txt");
	while (file >> key) {
		if (!(file >> query)) return nextword;
		if (!(file >> frequency)) return nextword;
		
		nextword.insert({ key,{ query,frequency } });
	}
	file.close();
	return nextword;
};


int main()
{
	setlocale(LC_ALL, "Russian");
	auto slovar = load("Vocabularyionary.txt");
	auto nextword = suggest(slovar, "добрый");
	cout << "Добрый" << endl;
	if (!(nextword.empty())) {
		for_each(nextword.begin(), nextword.end(), print);
	}
	
	cout << endl;
	nextword = suggest(slovar, "спокойного");
	cout << "Cпокойного" << endl;
	if (!(nextword.empty())) {
		for_each(nextword.begin(), nextword.end(), print);
	}

  cout << endl;
	nextword = suggest(slovar, "спокойной");
	cout << "Cпокойной" << endl;
	if (!(nextword.empty())) {
		for_each(nextword.begin(), nextword.end(), print);
	}

	cin.get(); cin.get();
	return 0;
}
