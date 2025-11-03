#include <bits/stdc++.h>
using namespace std;

struct Slot {
  // 0=never used, 1= tombstoned,  2=occupied
  int status = 0;
  string key;
};

// hashes the last char, then finds the ascii value for future sorting
static inline int hidx(const string& s) {
  return static_cast<int>(s.back() - 'a');
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // read the single input line of moves
  string line;
  if (!getline(cin, line)) {
    line = "";
  }
  stringstream ss(line);
  vector<string> moves;
  for (string tok; ss >> tok;) {
    moves.push_back(tok);
  }

  // table with 26 slots
  array<Slot, 26> table;

  // for the number of moves
  for (const string& move : moves) {
    if (move.empty()) {
      continue;
    }
    char op = move[0];         //A or D, insert or delete
    string key = move.substr(1);  //key

    int start = hidx(key); //hashes the value start is an index
    int pos = start;

    if (op == 'A') {
      // search to ensure key doesnt exist
      bool exists = false;
      //while loop to search for an empty pos, if empty no duplicates
      while (table[pos].status != 0) {
        //position
        if (table[pos].status == 2 && table[pos].key == key) {
          exists = true;
          break;
        }
        //loop around
        pos = (pos + 1) % 26;
        if (pos == start){
          break;
        }
      }
      //if exists leave the current loop
      if (exists){
        continue;
    }

      // back to start and insert on first unoccupied slot
      pos = start;
      while (table[pos].status == 2) {
        pos = (pos + 1) % 26;
      }
      // empty slot found status 2 and key=key
      table[pos].status = 2;
      table[pos].key = key;

    } else if (op == 'D') {
      // search for target, tombstone if found 
      pos = start;
      //while loop till the first 0, if there is a 0 then key will be never used
      while (table[pos].status !=0) {
        //check for target
        if (table[pos].status == 2 && table[pos].key == key) {
          table[pos].status = 1;  // tombstone the position
          table[pos].key.clear(); 
          break;
        }
        pos = (pos + 1) % 26;
        if (pos == start) break; 
      }
    }
  }

  // the output after each move
  bool first = true;
  for (const auto& s : table) {
    if (s.status == 2) {
      if (!first) cout << ' ';
      cout << s.key;
      first = false;
    }
  }
  cout << '\n';
  return 0;
}
