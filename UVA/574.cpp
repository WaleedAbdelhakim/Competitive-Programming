#include <bits/stdc++.h>
#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
using namespace std;

typedef vector<int> vi;
typedef long long ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 , -1 , 0 , 0 , -1 , 1 ,  1 , -1};

vi info;
const int N = 1005;
int freq[105];
int memo[N][13];

bool solve(int rem , int prev) {
  if(rem == 0)
    return 1;

  int &ret = memo[rem][prev];
  if(ret != -1)
    return ret;

  ret = 0;
  for (int i = prev-1 ;i >= 0 ;i--) {
    int c = info[i];
    for (int j = 0 ;j < freq[info[i]] ;j++ , c += info[i]) {
      if(c > rem)break;
      ret |= solve(rem - c , i);
    }
  }

  return ret;
}

string doIt(int num , int cnt) {
  string ret = "";
  for (int i = 0 ;i < cnt ;i++) {
    if(i != 0)
      ret += "+";
    ret += to_string(num);
  }
  return ret;
}

string cur = "";
void printPaths(int rem , int prev) {
  if(rem == 0) {
    cout << cur << endl;
    return;
  }

  if(cur.size())
    cur += '+';

  int sz = cur.size();
  for (int i = prev-1 ;i >= 0 ;i--) {
    for (int j = freq[info[i]] ;j > 0 ;j--) {
      if(j*info[i] > rem) continue;
      cur += doIt(info[i] , j);
      if(solve(rem - (j * info[i]) , i))
        printPaths(rem - (j * info[i]) , i);
      cur.resize(sz);
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.in", "rt", stdin);
#endif
  int t , n;
  while(cin >> t >> n , n) {
    int x;

    memset(freq , 0 , sizeof freq);
    info.clear();
    for (int i = 0 ;i < n ;i++) {
      scanf("%d",&x);
      freq[x]++;
      if(freq[x] == 1)
        info.pb(x);
    }

    sort(all(info));

    memset(memo , -1 , sizeof memo);

    printf("Sums of %d:\n",t);
    if(!solve(t , info.size()))
      puts("NONE");
    else
      printPaths(t , info.size());
  }
}
