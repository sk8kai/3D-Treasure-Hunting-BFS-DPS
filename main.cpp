// Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A
//  main.cpp
//  project1
//
//  Created by Kai Yamasaki on 1/12/23.
//
#include <queue>

#include <numeric>
#include <iostream>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//ADDED THIS FROM xcode_redirect.hpp file on canvas
#include <cstdio>
// REQUIRES: argc & argv from main(), and optind from getopt.h
// MODIFIES: optind is incremented until it equals argc
// EFFECTS:
//     Looks for extra arguments after getopt() finishes reading options.
//     It replaces simple shell functionality by using freopen() to change
//     stdin (from < infilename) and stdout (from > outfilename).
inline void xcode_redirect(int argc, char **argv, int optind = 1) {
    while (optind < argc) {
        switch (*argv[optind]) {
            case '<':  // redirect input
                if (!freopen(argv[++optind], "r", stdin)) {
                    std::cerr << "Unable to open input file: " << argv[optind] <<
std::endl;
                    exit(1);
                }
                break;
            case '>':  // redirect output
                if (!freopen(argv[++optind], "w", stdout)) {
                    std::cerr << "Unable to open output file: " << argv[optind] <<
std::endl;
                    exit(1);
                }
                break;
        }  // switch
        ++optind;
    }  // while
}  // xcode_redirect()

class project {
public:
    project() : method('\0'), oMode('M'), beenMSet(false) {}  //pretty sure default output should be M
    void method_set(char x) {
        method = x;
        beenMSet = true;
    }
    void oMode_set(char x) {
        oMode = x;
    }
    char getMethod() {
        return method;
    }
    char getoMode() {
        return oMode;
    }
    bool getMSet() {
        return beenMSet;
    }
private:
    char method;
    char oMode;
    bool beenMSet;
};


void getMode(int argc, char * argv[], project &perf) {
  // These are used with getopt_long()
  opterr = false; // Let us handle all error output for command line options
  int choice;
  int index = 0;
  option long_options[] = {
    // DONE: Fill in two lines, for the "mode" ('m') and
    // the "help" ('h') options.
    // ./project0 --mode nosize
    // ./project0 --help          //third argument always nullptr, cuz feature not used
      { "queue", no_argument, nullptr, 'q' } ,
      { "stack", no_argument, nullptr, 's'} ,
      { "help", no_argument, nullptr, 'h'} ,
      { "output", required_argument, nullptr, 'o'} ,
    { nullptr, 0, nullptr, '\0' },
  };  // long_options[]

  // TODO: Fill in the double quotes, to match the mode and help options.
  while ((choice = getopt_long(argc, argv, "qsho:", long_options, &index)) != -1) {
      // : means m is followed by an argument, while h has no argument
    switch (choice) {
        case 'h':
            cout << "INSERT: helpful guide how you need to use this program\n";
            exit(0);

        case 'q': {  // Need a block here to declare a variable inside a case
            if (perf.getMSet()) {
                cerr << "Multiple routing modes specified\n";
                exit(1);
            }
            perf.method_set('q');
            break;
        }
        case 's': {  // Need a block here to declare a variable inside a case
            if (perf.getMSet()) {
                cerr << "Multiple routing modes specified\n";
                exit(1);
            }
            perf.method_set('s');

          break;
        }  // case 'm'
        case 'o': {
            char in = *optarg;
            if (in != 'M' && in != 'L') {
                cerr << "Invalid output mode specified\n";
                exit(1);
            }
            else if (in == 'M') {
                perf.oMode_set('M');
            }
            else {
                perf.oMode_set('L');
            }
            break;
        }
      //default:
        //cerr << "Error: invalid option" << endl;
        //exit(1);
    }  // switch ..choice
  }  // while
}







class Position{
public:
    //Position() : level(-1), row(-1), col(-1){
    Position() : level(10000), row(10000), col(10000){
        
        //planning on deleting discovered and from anywasy
        }
    Position(uint32_t l, uint32_t r, uint32_t c) : level(l), row(r), col(c) { }
    uint32_t get_level() {
        return level;
    }
    uint32_t get_row() {
        return row;
    }
    
    uint32_t get_col() {
        return col;
    }
    
private:
    uint32_t level;
    uint32_t row;
    uint32_t col;
};

void increment(uint32_t &level, uint32_t &row, uint32_t &col, const uint32_t s) {
    ++col;
    if (col == s) {
        ++row;
        col = 0;
        if (row == s) {
            row = 0;
            ++level;
        }
    }
    
}
//orignally had uint32_t numL and const uint32_t s in the parameter, but remove for error
bool validCharacter(char input) {
    if (input == '.') {
        return true;
    }
    else if (input == 'H') {
        return true;
    }
    else if (input == 'S') {
        return true;
    }
    else if (input == 'E') {
        return true;
    }
    else if (input == '#') {
        return true;
    }
    else {
        cerr << "Invalid map character\n";
        exit(1);
        return false;
    }
}

void funcMRead(const uint32_t s, const uint32_t lastLV, vector<vector<vector<pair<char, char>>>> &v, uint32_t (&sLoc)[3]) {
    char input;
    uint32_t level = 0;
    uint32_t row = 0;
    uint32_t col = 0;
    bool cool = true;
    while (cin >> input && cool == true) {
        if (level >= lastLV) {
            //if they start entering in input beyond what we have space for (exta)
            //stop reading in
            cool = false;
        }
        else if (input == '/') {
            //might bug if they throw a / in the middle of the read in crap
            string ignore;
            getline(cin, ignore);
        }
        else if (input != '.'){
            cool = validCharacter(input);
            v[level][row][col].first = input;
            if (input == 'S') {
                sLoc[0] = level;
                sLoc[1] = row;
                sLoc[2] = col;
                v[level][row][col].second = 'G';
            }
            increment(level, row, col, s);
        }
        else {
            cool = validCharacter(input);
            increment(level, row, col, s);
        }
    }
}

//orignally had uint32_t numL & const uint32_t s in the parameter, but remove for error
void okLocation(uint32_t numL, uint32_t s, uint32_t level, uint32_t row, uint32_t col) {
    if (level >= numL) {
        cerr << "Invalid map level\n";
        exit(1);
    }
    if (row >= s) {
        cerr << "Invalid map row\n";
        exit(1);
    }
    
    if (col >= s) {
        cerr << "Invalid map column\n";
        exit(1);
    }
    //might show an error if inputted a negative location, unsure 
    //
}

void funcLRead(uint32_t numL, uint32_t s, vector<vector<vector<pair<char, char>>>> &v, uint32_t (&sLoc)[3]) {
    char input;
    uint32_t level = 0;
    uint32_t row = 0;
    uint32_t col = 0;
    char null;
    bool cool = true;
    while (cin >> input && cool == true) {
        if (level >= numL) {
            //if they start entering in input beyond what we have space for (exta)
            //stop reading in
            cool = false;
        }
        else if (input == '/') {
            string ignore;
            getline(cin, ignore);
        }
        else {
            cin >> level >> null >> row >> null >> col >> null >> input >> null;
            cool = validCharacter(input);
            okLocation(numL, s, level, row, col);
            v[level][row][col].first = input;
            if (input == 'S') {
                sLoc[0] = level;
                sLoc[1] = row;
                sLoc[2] = col;
                v[level][row][col].second = 'G';
            }
            
        }
    }
}

void print( vector<vector<vector<pair<char, char>>>> &v, uint32_t numLevels) {
    for (uint32_t i = 0; i < static_cast<uint32_t>(numLevels); i++) {
        cout << "//level " << i << endl;
        for (uint32_t j = 0; j < v[i].size(); j++) {
            for (uint32_t k = 0; k < v[i][j].size(); k++) {
                cout << v[i][j][k].first;
            }
            cout << endl;
        }
    }
}

bool isValid(uint32_t check[], const uint32_t &size,  const vector<vector<vector<pair<char, char>>>> &v) {
    if ((check[1] + 1) > size){
        return false;
    }
    else if (check[1] > size) {
        return false;
    }
    else if ((check[2] + 1) > size){
        return false;
    }
    else if (check[2] > size) {
        return false;
    }
    else if (v[check[0]][check[1]][check[2]].first == '#') {
        return false;
    }
    else {
      return true;
    }
   
}

void programStart(char cmethod, char oMode) {
    if (cmethod == 'e') {
        cout << "INVALID COMMAND INPUT\n";
    }
    //read in right here
    string inputForm;
    uint32_t numL;
    uint32_t s;
    cin >> inputForm;
    cin >> numL;
    cin >> s;
    uint32_t startLoc[3];
    
    pair<char, char> filler;
    filler.first = '.';
    filler.second = 'U';
    vector<vector<vector<pair<char, char>>>> v(numL, vector<vector<pair<char, char>>>(s, vector<pair<char, char>>(s,filler)));
    
    //uint32_t vecSize = (numL * (s * s));
    v.resize(numL, vector<vector<pair<char, char>>>(s, vector<pair<char, char>>(s)));
    //cout << L[0][0][0].first << endl << L[0][0][0].second << endl;
    //vector<vector<vector<char>>> v(numL, vector<vector<char>>(s, vector<char>(s,'.')));
    if (inputForm == "M") {
        funcMRead(s, numL, v, startLoc);
    }
    else {
        funcLRead(numL, s, v, startLoc);
    }
    /*
    cout << "M" << endl << "5" << endl << "50" << endl << "//A slightly larger random file for testing" << endl;
    print(v, numL);
     */
    
    //test print shown here:
    //print(v);
    //cout << endl << endl;
    //cout << startLoc[0] << " " << startLoc[1] << " " << startLoc[2] << endl;
    
    /// currently have-- start location, vector of elements, mode, sizes of vector
    bool isStack = false;
    if (cmethod == 's') {
        isStack = true;
    }
    else if (cmethod == 'q') {
        isStack = false;
    }
    else {
        cout << "UNKNOWN ERROR\n";
    }
    
    
    deque<Position> searchCon;
    Position currLoc(startLoc[0], startLoc[1], startLoc[2]);
    searchCon.push_back(currLoc);
    bool endFound = false;
    Position hangar;
    
    
    
    
    while (endFound == false) {
        
        
        uint32_t l = currLoc.get_level();
        uint32_t r = currLoc.get_row();
        uint32_t c = currLoc.get_col();
        --r;
        
        /*
        if (l == 0 && r == (-1) && c == 3) {
            cout << "check this here" << endl;
        }
         */
        
        //north coordinate check
        uint32_t checkLoc[3] =  {l , r, c};
        
        //cout << l << r << c << endl << endl;
        if (isValid(checkLoc, s, v)) {
            if (v[l][r][c].second == 'U') {
                v[l][r][c].second = 'n';
                //(isStack) ? searchCon.push_front(currLoc) : searchCon.push_back(currLoc);
                Position valid(l, r, c);
                searchCon.push_back(valid);
                if (v[l][r][c].first == 'H') {
                    Position found(l, r, c);
                    hangar = found;
                    
                    endFound = true;
                }
            }
        }
        
        //east coordinate check from north
        ++c;
        r = currLoc.get_row();
        checkLoc[1] = r;
        checkLoc[2] = c;
        
        //remove this later
        //cout << l << r << c << endl << endl;
        if (isValid(checkLoc, s, v)){
            if (v[l][r][c].second == 'U') {
                v[l][r][c].second = 'e';
                Position valid(l, r, c);
                searchCon.push_back(valid);
                if (v[l][r][c].first == 'H') {
                    Position found(l, r, c);
                    hangar = found;
                    endFound = true;
                }
            }
        }
        
        
        //south coordinate check from east
        c = currLoc.get_col();
        r = currLoc.get_row();
        ++r;
        checkLoc[1] = r;
        checkLoc[2] = c;
        
        
        
        //cout << l << r << c << endl << endl;
        if (isValid(checkLoc, s, v)) {
            if(v[l][r][c].second == 'U') {
                v[l][r][c].second = 's';
                Position valid(l, r, c);
                searchCon.push_back(valid);
                if (v[l][r][c].first == 'H') {
                    Position found(l, r, c);
                    hangar = found;
                    endFound = true;
                }
            }
        }
        
        //west coordinate check from south
        --c;
        r = currLoc.get_row();
        checkLoc[1] = r;
        //ERROR HERE R IS 4.. why
        // C should be -1 and R should be 3
        //currLoc was also changed

        checkLoc[2] = c;
        
        
        //cout << l << r << c << endl << endl;
        if (isValid(checkLoc, s, v)) {
            if (v[l][r][c].second == 'U') {
                v[l][r][c].second = 'w';
                Position valid(l, r, c);
                searchCon.push_back(valid);
                if (v[l][r][c].first == 'H') {
                    Position found(l, r, c);
                    hangar = found;
                    endFound = true;
                }
            }
        }
        
        c = currLoc.get_col();
        r = currLoc.get_row();
                
    
        
        
        if (v[l][r][c].first == 'E') {
            char orig = static_cast<char>('0' + l);
            for (uint32_t i  = 0; i < numL; ++i) {
                if (i != l && v[i][r][c].second == 'U') {
                    if (v[i][r][c].first == 'E') {
                        Position elevs(i, r, c);
                        searchCon.push_back(elevs);
                        v[i][r][c].second = orig;
                    }
                    
                }
            }
        }
        
        
        
        
        if (isStack) {
            currLoc = searchCon.back();
            searchCon.pop_back();
            
    
        }
        else {
            searchCon.pop_front();
            currLoc = searchCon.front();
            
        }
        
        if (searchCon.empty()) {
            if (oMode ==  'M') {
                cout << "Start in level " << startLoc[0] << ", row " << startLoc[1] << ", column " << startLoc[2] << endl;
                print(v, numL);
                exit(0);
            }
            else {
                cout << "//path taken" << endl;
                exit(0);
            }
        }
    

    }
    
    //const int hLocs[3] = { hangar.get_level(), hangar.get_row(), hangar.get_col() };
    uint32_t hLocs[3];
    hLocs[0] = hangar.get_level();
    hLocs[1] = hangar.get_row();
    hLocs[2] = hangar.get_col();
    
   // cout << "HLOCKS test" << endl;
    //cout << hLocs[0] << hLocs[1] << hLocs[2] << endl;
    
    
    
    
    
   
    
    //cout << "the final destination for the hangar is as follows:" << endl;
    //cout << hangar.get_level() << hangar.get_row()  << hangar.get_col() << endl;
    //cout << "tracing path is as follows: " << endl;
   // cout << v[hangar.get_level()][hangar.get_row()][hangar.get_col()].second << endl;
    
    
    

    
    

    
    
    
    
    
    //cout << "Elevator.second before this func: " << v[1][0][3].second << endl;
    //cout << "Elevator.second before this func: " << v[0][0][3].second << endl;
    
    //deque<char> tracing;
    //tracing.resize(vecSize);
    
    
  

    
    
    
    char direct = v[hangar.get_level()][hangar.get_row()][hangar.get_col()].second;
    bool atOrigin = false;
    
    
    while (atOrigin == false) {
        //if (direct == '4')  {
          //  cout << endl << endl << count << endl;
            //int x = 0;
        //}
        /*
        if ((direct >= '0') && (direct <= '9')) {
            tracing.push_back(direct);
            cout << direct << endl;
            tracing.push_back(direct);
        }
         */
        if (static_cast<int>(direct) < 48 || static_cast<int>(direct) > 57) {
            //tracing.push_back(direct);
            
            
            //delete this cout testing pursposes
            //cout << direct << endl;
        }
    
      
       
        if (direct == 'G') {
            atOrigin = true;
        }
        else if (direct == 'n') {
            Position next(hangar.get_level(), (hangar.get_row() + 1), hangar.get_col());
            hangar = next;
            v[hangar.get_level()][hangar.get_row()][hangar.get_col()].first = direct;
            direct = v[hangar.get_level()][hangar.get_row()][hangar.get_col()].second;
        }
        else if (direct == 'e') {
            Position next(hangar.get_level(), hangar.get_row(), (hangar.get_col() - 1));
            hangar = next;
            v[hangar.get_level()][hangar.get_row()][hangar.get_col()].first = direct;
            direct = v[hangar.get_level()][hangar.get_row()][hangar.get_col()].second;
        }
        else if (direct == 's') {
            Position next(hangar.get_level(), (hangar.get_row() - 1), hangar.get_col());
            hangar = next;
            v[hangar.get_level()][hangar.get_row()][hangar.get_col()].first = direct;
            direct = v[hangar.get_level()][hangar.get_row()][hangar.get_col()].second;
        }
        else if (direct == 'w') {
            Position next(hangar.get_level(), hangar.get_row(), (hangar.get_col() + 1));
            hangar = next;
            v[hangar.get_level()][hangar.get_row()][hangar.get_col()].first = direct;
            direct = v[hangar.get_level()][hangar.get_row()][hangar.get_col()].second;
            //for some reaosn code wont push back after a certain number of Ws? at deque size 258, so i set it obscenely large?
        }
        else if (direct == 'U') {
            cout << "you fucked up bro" << endl;
        }
        // had static_cast<uint32_t>(direct - '0')  >= 0 &&  in the command line too
        // remove so it works for make submits 
        else if (static_cast<uint32_t>(direct - '0') < numL) {
            //if (count == 2) {
              //  cout << "Testing here" << endl;
                //when this iterates through the 2nd time why is it 3 WW?
            //}
            uint32_t nextlv = static_cast<uint32_t>(direct - '0');
            v[nextlv][hangar.get_row()][hangar.get_col()].first = static_cast<char>('0' + hangar.get_level());
            Position next(nextlv, hangar.get_row(), hangar.get_col());
            hangar = next;
            direct = v[hangar.get_level()][hangar.get_row()][hangar.get_col()].second;
            
            
            
            
            //originally had this below
            //tracing.push_back(direct);
            
            /*
            tracing.push_back(static_cast<char>(hangar.get_level() + '0'));
            
            
            char lev = v[hangar.get_level()][hangar.get_row()][hangar.get_col()].second;
            uint32_t act = static_cast<uint32_t>(lev - '0');
            Position next(act, hangar.get_row(), hangar.get_col());
            hangar = next;
            direct = v[hangar.get_level()][hangar.get_row()][hangar.get_col()].second;
            ++count;
             */
        }
        else {
            direct = static_cast<char>('0' + hLocs[0]);
            //above code probabnly will not work/cause bugs
        
        }
    }
    
    
    Position fol((startLoc[0]), (startLoc[1]), (startLoc[2]));
    
    /*
    cout << endl << endl;
    while (!tracing.empty()) {
        cout << tracing.front() << endl;
        tracing.pop_front();
    }
    cout << oline << endl;
    */
     
    
    
    //backtracing segment
    

/*

        if (tracing.back() != 'G') {
            //cout << "confused" << endl;
        }
        else  {
            tracing.pop_back();
        }
        //v[fol.get_level()][fol.get_row()][fol.get_col()].first = tracing.back();
        
        
        
        
       // tracing.pop_back();
    //int count = 0;
        while (tracing.back() != '\0') {
            //count++;
            //if (count == 2) {
              //  cout << "looking here" << endl;
            //}
            char next = tracing.back();
            if (next == 'n') {
                v[fol.get_level()][fol.get_row()][fol.get_col()].first = next;
                Position hi(fol.get_level(), (fol.get_row() - 1), fol.get_col());
                fol = hi;
                //cout << next << endl;
                
            }
            else if (next == 'e') {
                v[fol.get_level()][fol.get_row()][fol.get_col()].first = next;
                Position hi(fol.get_level(), fol.get_row(), (fol.get_col() + 1));
                fol = hi;
                //cout << next << endl;
            }
            else if (next == 's') {
                v[fol.get_level()][fol.get_row()][fol.get_col()].first = next;
                Position hi(fol.get_level(), (fol.get_row() + 1), fol.get_col());
                fol = hi;
                //cout << next << endl;
            }
            else if (next == 'w') {
                v[fol.get_level()][fol.get_row()][fol.get_col()].first = next;
                Position hi(fol.get_level(), fol.get_row(), (fol.get_col() - 1));
                fol = hi;
                //cout << next << endl;
            }
            else if (next == 'U') {
                //cout << "you messed up bro" << endl;
            }
            
    
            else {
                v[fol.get_level()][fol.get_row()][fol.get_col()].first = next;
                if (hLocs[0] != next) {
                    //cout << "ERROR passing levels" << endl << endl;
                }
                Position hi(static_cast<uint32_t>(hLocs[0] - '0'), fol.get_row(), (fol.get_col()));
                fol = hi;
               //cout << next << endl;
                
                
                //this is wrong here
                //code above seems correct
                
                

            }
            tracing.pop_back();
            
            
        }
        
*/
    
   
    if (oMode == 'M') {
        cout << "Start in level " << startLoc[0] << ", row " << startLoc[1] << ", column " << startLoc[2] << endl;
        print(v, numL);
    }
    else {
        
        cout << "//path taken" << endl;
        

        
        //Position destination(hLocs[0] - '0', hLocs[1] - '0', hLocs[0] - '2');
        Position track(startLoc[0], startLoc[1], startLoc[2]);
        bool arrived = false;

        //cout << hang[0] << hang[1] << hang[2] << endl << endl;
        //uint32_t count = 0;
        while (arrived == false) {
            //++count;
            uint32_t le = track.get_level();
            uint32_t ro = track.get_row();
            uint32_t co = track.get_col();
            
            char motion = v[le][ro][co].first;
            
            if ((le == hLocs[0]) && (ro == hLocs[1]) && (co == hLocs[2])) {
                arrived = true;
            }
            
            else if (motion == 'H') {
                //count++;
                arrived = true;
            }
            else {
                cout << "(" << le << "," << ro << "," << co << "," << motion << ")\n";
            
                if (motion == 'n') {
                    Position hi(track.get_level(), (track.get_row() - 1), track.get_col());
                    track = hi;
                }
                else if (motion == 'e') {
                    Position hi(track.get_level(), track.get_row(), (track.get_col() + 1));
                    track = hi;
                }
                else if (motion == 's') {
                    Position hi(track.get_level(), (track.get_row() + 1), track.get_col());
                    track = hi;
                }
                else if (motion == 'w') {
                    Position hi(track.get_level(), track.get_row(), (track.get_col() - 1));
                    track = hi;
                }
                else {
                    Position hi(static_cast<uint32_t>(motion - '0'), track.get_row(), (track.get_col()));
                    track = hi;
                }
            }
        }
    
    }
}









// This function is already done.
int main(int argc, char *argv[]) {
  // This should be in all of your projects, speeds up I/O
  ios_base::sync_with_stdio(false);

    
    
    //TODO: need to throw an error if stack or queue isn't specified
    project perf;
    getMode(argc, argv, perf);
    if (!perf.getMSet()) {
      cout << "No routing mode specified\n";
        exit(1);
    }
    xcode_redirect(argc, argv);
    if (perf.getoMode() == 'M') {
        programStart(perf.getMethod(), perf.getoMode());
    }
    else  if (perf.getoMode() == 'L') {
        programStart(perf.getMethod(), perf.getoMode());
    }
    else {
        cerr << "Error messeage\n";
        exit(1);
    }
    
    
    

  // Get the mode from the command line and read in the data
    
    
    /*
    string cline = static_cast<string>(argv[1]);
    string oMode = "m";

    
    if ((cline == "-h" || cline == "--help") && argc == 2) {
        cout << "HELP MESSAGE HERE\n";
    }
    else if (cline == "--stack" || cline == "-s" || cline == "-q" || cline == "--queue"){
         if (argc == 6) {
            xcode_redirect(argc, argv);
            string inSign = static_cast<string>(argv[2]);
            string outSign = static_cast<string>(argv[4]);
            if (inSign == "<" && outSign == ">") {
                //perform the xcode redirect, then fucnction start
                setMode(cline, oMode);
                programStart(cline, oMode);
            }
            else {
                cout << "INVALID COMMAND INPUT\n";
            }
        }
        else if (argc == 8) {
            xcode_redirect(argc, argv);
            string req = static_cast<string>(argv[2]);
            string inSign = static_cast<string>(argv[4]);
            string outSign = static_cast<string>(argv[6]);
            if ((req == "--output" || req == "-o") && inSign == "<" && outSign == ">"){
                //set mode
                //perform the xcode redirect, then fucnction start
                
                string oline = static_cast<string>(argv[3]);
                setMode(cline, oline);
                oMode = oline;

                programStart(cline, oMode);
            }
        }
        else {
            cout << "INVALID COMMAND INPUT\n";
        }
    }
    else {
        cout << "INVALID COMMAND INPUT\n";
    }
     */
  return 0;
}  // main()


/*
 
 
 
 L
 2
 3
 //Path
 (0, 2, 1, E)
 (1, 0, 1, E)
 (1, 1, 1, E)
 (1, 0, 1, #)
 (0, 0, 0, E)
 (0, 0, 1, S)
 (1, 0, 0, H)
 (0, 1, 1, E)
 




 */
