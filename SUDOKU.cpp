#include <bits/stdc++.h>
using namespace std;

// SUDOKU

int N; // no. of rows, colums, (No of entries in one block)
int n; // rows in one block
int m; // cols in one block

vector<vector<int>> ANS;

vector<set<int>> row;        // tells if cur row has x or not
vector<set<int>> col;        // tells if cur col has x or not
vector<set<int>> block;      // tells if cur block has x or not

int get_block(int r, int c) {
    return (r / n) * (N / m) + (c / m);
}

bool can(int r, int c, int x) {
    if (row[r].count(x)) return false;
    if (col[c].count(x)) return false;
    if (block[get_block(r, c)].count(x)) return false;
    return true;
}

bool dfs(int r, int c) {
    if (r >= N) return true;

    int new_row = r;
    int new_col = c + 1;
    if (new_col == N) {
        new_col = 0;
        new_row += 1;
    }

    if (ANS[r][c]) return dfs(new_row, new_col);

    for (int i = 1; i <= N; i++) {
        if (can(r, c, i)) {
            ANS[r][c] = i;
            row[r].insert(i);
            col[c].insert(i);
            block[get_block(r, c)].insert(i);

            if (dfs(new_row, new_col)) return true;

            ANS[r][c] = 0;
            row[r].erase(i);
            col[c].erase(i);
            block[get_block(r, c)].erase(i);
        }
    }

    return false;
}

int main() {
    cout << "Input the Dimensions of Matrix (rows) : " << endl;
    cout.flush();
    cin >> N;
    cout << "Input the Dimensions of One block (rows x colums) : " << endl;
    cout.flush();
    cin >> n >> m;

    // N = 6, n = 2 m = 3;
    
    ANS.resize(N, vector<int> (N, 0));
    row.resize(N);
    col.resize(N);
    block.resize(N);

    cout << "Input the Elements of the Matrix : " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> ANS[i][j];
            if (ANS[i][j]) {
                row[i].insert(ANS[i][j]);
                col[j].insert(ANS[i][j]);
                block[get_block(i, j)].insert(ANS[i][j]);
            }
        }
    }

    dfs(0, 0);

    cout << "Final Result : " << endl;
    cout.flush();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << ANS[i][j] << ' ';
        }
        cout << endl;
    }
}