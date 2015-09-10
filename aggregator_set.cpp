#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

#define MAX_COLUMNS 50

using namespace std;

int main(int argc, char *argv[]) {
  int selector = stoi(argv[1]);
  int aggregator = stoi(argv[2]);
  int numTop = stoi(argv[3]);

  unordered_map<string, int> map;
  set<pair<int, string>> set;

  string line;
  string cells[MAX_COLUMNS];

  ios_base::sync_with_stdio(false);

  while(getline(cin, line)) {
    stringstream lineStream(line);

    for(int i = 0; getline(lineStream, cells[i],','); i++);

    const int value = stoi(cells[aggregator]);
    const string key = cells[selector];
    const int oldSum = map[key];
    const int newSum = oldSum + value;

    if(set.size() < numTop) {
      set.insert(make_pair(newSum, key));
    } else if(set.begin()->first < newSum) {
      const auto& curr = set.find(make_pair(oldSum, key));

      set.erase(curr == set.end() ? set.begin() : curr);
      set.insert(make_pair(newSum, key));
    }

    map[key] = newSum;
  }

  for (auto& elem: set) {
    cout << elem.first << " " << elem.second << endl;
  }
}
