#include <bits/stdc++.h>

using namespace std;

const int N = 4, M = 7e7;
char grid[N][N];
int p[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907};
int memo[M];

inline int get_ind(int i, int j) {
    return i * 4 + j;
}

inline int get_digit(int i, int j, int mask) {
    return (mask / p[get_ind(i, j)]) % 3;
}

inline int set_digit(int i, int j, int mask, int t) {
    return mask + t * p[get_ind(i, j)];
}

bool gameOver(int mask) {
    for (int i = 0; i < 4; i++) {
        set<int> uni, unii;
        for (int j = 0; j < N; j++) {
            uni.insert(get_digit(i, j, mask));
            unii.insert(get_digit(j, i, mask));
        }

        if ((uni.size() == 1 && *uni.begin() != 0) || (unii.size() == 1 && *unii.begin() != 0))
            return 1;
    }

    set<int> uni, unii;
    int i = 0, j = N - 1;
    while (i < N) {
        uni.insert(get_digit(i, i, mask));
        unii.insert(get_digit(i, j, mask));
        j--;
        i++;
    }

    return (uni.size() == 1 && *uni.begin() != 0) || (unii.size() == 1 && *unii.begin() != 0);
}

bool winning(int mask, int t) {
    if (gameOver(mask))
        return 0;

    int &ret = memo[mask];
    if (~ret)
        return ret;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (!get_digit(i, j, mask) && !winning(set_digit(i, j, mask, t), (t == 1 ? 2 : 1)))
                return ret = 1;

    return ret = 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    memset(memo, -1, sizeof memo);
    char c;
    while (scanf(" %c", &c), c != '$') {
        int s = 0;
        for (int i = 0; i < N; i++) {
            scanf("%s", &grid[i]);
            for (int j = 0; j < N; j++) {
                s += grid[i][j] != '.' ? p[get_ind(i, j)] : 0;
                s += grid[i][j] == 'o' ? p[get_ind(i, j)] : 0;
            }
        }

        if (winning(s, 1)) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (!get_digit(i, j, s) && !winning(set_digit(i, j, s, 1), 2)) {
                        printf("(%d,%d)\n", i, j);
                        i = N, j = N;
                    }
                }
            }
        } else {
            puts("#####");
        }
    }

}