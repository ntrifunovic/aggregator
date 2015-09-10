#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  int selector = stoi(argv[1]);
  int aggregator = stoi(argv[2]);
  int numTop = stoi(argv[3]);

  unordered_map<string, int> map;

  string line;
  while(getline(cin, line)) {
    vector<string> cells;
    string cell;
    stringstream lineStream(line);

    while(getline(lineStream, cell,',')) {
      cells.push_back(cell);
    }

    map[cells[selector]] += stoi(cells[aggregator]);
  }

  vector<pair<string, int>> top(numTop);
  partial_sort_copy(map.begin(),
		    map.end(),
		    top.begin(),
		    top.end(),
			 [](pair<const string, int> const& l,
			    pair<const string, int> const& r) {
                           return l.second > r.second;
			 });

  for (auto& elem: top) {
    cout << elem.first << " " << elem.second << endl;
  }
}
