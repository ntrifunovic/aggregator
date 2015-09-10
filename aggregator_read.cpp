#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

#define MAX_COLUMS 50

using namespace std;

int main(int argc, char *argv[]) {
  int selector = stoi(argv[1]);
  int aggregator = stoi(argv[2]);
  int numTop = stoi(argv[3]);

  string line;
  string cells[MAX_COLUMS];

  ios_base::sync_with_stdio(false);

  while(getline(cin, line)) {
    stringstream lineStream(line);

    for(int i = 0; getline(lineStream, cells[i],','); i++);
    
    // extract key
    stoi(cells[aggregator]);
  }

  cout << "All done" << endl;
}
