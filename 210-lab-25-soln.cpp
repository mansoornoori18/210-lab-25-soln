#include <iostream>  //
#include <fstream>   //
#include <chrono>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <iomanip>
using namespace std;

// const int SZ = 20000, COLS = 3, ROWS = 4, TESTS = 4;
const int STRUCTURES = 3;
const int ROWS = 4, COLS = 3;
const int W1 = 10;
const int Runs = 15;   // for number of times to repeat run 1

int main() {
    long long results[Runs][ROWS][COLS] = {0};
    string cd;
    vector<string> data_vector;
    list<string> data_list;
    set<string> data_set;
    
    // outer loop to go through each operation 2
    for (int run = 0; run < Runs; run++){
        cout << "startng run #" << (run+1) << endl;

        data_vector.clear();
        data_list.clear();
        data_set.clear();

    // testing for READ operations
    for (int i = 0; i < STRUCTURES; i++) {
        ifstream fin("codes.txt");
        auto start = chrono::high_resolution_clock::now();
        switch(i) {
            case 0: {  // read into a vector
                while (fin >> cd)
                        data_vector.push_back(cd);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][0][i] = duration.count();
                break;
            }
            case 1: {  // read into a list
                while (fin >> cd)
                        data_list.push_back(cd);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][0][i] = duration.count();
                break;
            }
            case 2: {  // read into a set
                while (fin >> cd)
                        data_set.insert(cd);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][0][i] = duration.count();
                break;
            }
        }
        fin.close();
    }

    // testing for SORT operations
    for (int i = 0; i < STRUCTURES; i++) {
        auto start = chrono::high_resolution_clock::now();
        switch(i) {
            case 0: {  // sort a vector
                sort(data_vector.begin(), data_vector.end());
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][1][i] = duration.count();
                break;
            }
            case 1: {  // sort a list
                data_list.sort();
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][1][i] = duration.count();
                break;
            }
            case 2: {  // can't sort a set, so set to -1
                results[Runs][1][i] = -1;
                break;
            }
        }
    }

    // testing for INSERT operations
    for (int i = 0; i < STRUCTURES; i++) {
        int ind_v = data_vector.size() / 2;
        int ind_l = data_list.size() / 2;
        auto start = chrono::high_resolution_clock::now();
        switch(i) {
            case 0: {  // insert into a vector
                data_vector.insert(data_vector.begin() + ind_v, "TESTCODE");
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][2][i] = duration.count();
                break;
            }
            case 1: {  // insert into a list
                auto it = data_list.begin();
                advance(it, ind_l);
                data_list.insert(it, "TESTCODE");
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][2][i] = duration.count();
                break;
            }
            case 2: {  // insert into a set
                data_set.insert("TESTCODE");
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][2][i] = duration.count();
                break;
            }
        }
    }

    // testing for DELETE operations
    for (int i = 0; i < STRUCTURES; i++) {
        // select a target value in the vector 
        int ind = data_vector.size() / 2;
        string target_v = data_vector[ind];

        // select a target value in the list
        auto it1 = data_list.begin();
        advance(it1, ind);
        string target_l = *it1;

        // select a target value in the set
        auto it2 = data_set.begin();
        advance(it2, ind);
        string target_s = *it2;
        
        auto start = chrono::high_resolution_clock::now();
        switch(i) {
            case 0: {  // delete by value from vector
                data_vector.erase(remove(data_vector.begin(), data_vector.end(), target_v));
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][3][i] = duration.count();
                break;
            }
            case 1: {  // delete by value from list
                data_list.remove(target_l);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][3][i] = duration.count();
                break;
            }
            case 2: {  // delete by value from set
                data_set.erase(target_s);    
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                results[Runs][3][i] = duration.count();
                break;
            }
        }
    }
    cout << "Run #" << (run+1) << " Completed" << endl;
    }
    // for average
    long long averages[ROWS][COLS] = {0};

    // the sum of the all runs 
    for (int run = 0; run < Runs ; ++run){
        for ( int op = 0; op < Runs ; ++op){
            for(int st = 0; st < Runs; ++st){
                averages[op][st] += results[run][op][st];
            }
        }
    }
    //DIvide by 3 to get ther average
    




    string labels[] = {"Read", "Sort", "Insert", "Delete"};
    cout << setw(W1) << "Operation" << setw(W1) << "Vector" << setw(W1) << "List"
         << setw(W1) << "Set" << endl;
    for (int i = 0; i < 4; i++) {
        cout << setw(W1) << labels[i];
        for (int j = 0; j < COLS; j++) 
            cout << setw(W1) << results[i][j];
        cout << endl;
    }
    

    return 0;
}