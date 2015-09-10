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
  int keep = stoi(argv[4]);
  int max = stoi(argv[5]);

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

    map[cells[selector]] = newSum;
    
    if(map.size() > max) {
      vector<pair<string, int>> top(keep);
      partial_sort_copy(map.begin(),
			map.end(),
			top.begin(),
			top.end(),
			[](pair<const string, int> const& l,
			   pair<const string, int> const& r) {
			  return l.second > r.second;
			});
      map.clear();
      map.insert(top.begin(),
		 top.end());
    }

  }

  for (auto& elem: set) {
    cout << elem.first << " " << elem.second << endl;
  }
}
