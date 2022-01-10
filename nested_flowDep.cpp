//
// Created by vae on 2022/1/6.
//

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

#define main20 main20

void compute_seq(vector<vector<int>> &vec) {

    for (auto i = 0; i != vec.size(); ++i) {
        for (auto j = 0; j < vec[i].size(); ++j) {
            if ((i - 1) >= 0) {
                vec[i][j] += vec[i - 1][j];
            }
            if ((j - 1) >= 0) {
                vec[i][j] += vec[i][j - 1];
            }
            if ((j - 1) >= 0 && (i - 1) >= 0) {
                vec[i][j] += vec[i - 1][j - 1];
            }
        }
    }

}


void compute_par(vector<vector<int>> &vec) {

    //纵向的计算
    for (auto i = 0; i != vec.size(); ++i) {
#pragma opm parallel for default(none)
        for (auto j = i, k = 0; j >= 0; --j, ++k) {
            if ((j - 1) >= 0) {
                vec[j][k] += vec[j - 1][k];
            }
            if ((k - 1) >= 0) {
                vec[j][k] += vec[j][k - 1];
            }
            if ((j - 1) >= 0 && (k - 1) >= 0) {
                vec[j][k] += vec[j - 1][k - 1];
            }
        }
    }

//    横向的计算
    for (auto i = 1; i != vec.size(); ++i) {
        // 这里可以并行
        for (unsigned j = vec.size() - 1, k = i; j >= 0 && k < vec[0].size(); --j, ++k) {
            if ((j - 1) >= 0) {
                vec[j][k] += vec[j - 1][k];
            }
            if ((k - 1) >= 0) {
                vec[j][k] += vec[j][k - 1];
            }
            if ((j - 1) >= 0 && (k - 1) >= 0) {
                vec[j][k] += vec[j - 1][k - 1];
            }
        }
    }


}


int main20() {
    vector<vector<int>> vec(10, vector<int>(10, 1));
//    cout << vec.size() << " " << vec[0].size();
//    cout << "*********";
    compute_par(vec);
    for (auto &e: vec) {
        for (auto i: e) {
            cout << i << " ";
        }
        cout << endl;
    }
}

