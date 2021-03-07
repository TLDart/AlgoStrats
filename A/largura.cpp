//Duarte Dias 2018293526
//Maria Dias 2018274188
#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <cmath>

using namespace std;

int best = INT_MAX;
void printpointset(vector<vector<int>> &a){
    cout << "----------" << endl;
    for(int i = 0; i < (int) a.size(); i++){
        for(int j = 0; j <  (int)a.size(); j++){
            cout << a[i][j] << " ";
        }
            cout << endl;
    }
}
int slideL(vector<vector<int>> &a){\
    int pos, lst, cnt = 0;
    for(int i = 0; i  <  (int)a.size(); i++){ // Act over the colums up >> down , right >> left
        lst = a.size() -1;
        for(int j = a.size() - 2 ; j >= 0; j--){ //Calculate
            if(a[i][lst] == a[i][j]){
                a[i][j] *= 2;
                cnt++;
                a[i][lst] = 0;
                cnt++;
                lst = j-1;
                j--;
            }
            else if(a[i][j] != 0){
                lst = j;
            }
        }
    }
    for(int i = 0; i <  (int)a.size(); i++){ // Colapse matrix to the left
        pos = -1;
        for(int j = 0 ; j <  (int)a.size(); j++){
            if(a[i][j] == 0 && pos == -1){
                pos = j;
            }
            else if (pos != -1 && a[i][j] != 0){
                a[i][pos] = a[i][j];
                a[i][j] = 0;
                pos++;
            }
        }
    }
    return cnt;
}

int slideR(vector<vector<int>> &a){
    int pos,lst, cnt = 0;
    for(int i = 0; i  <  (int)a.size(); i++){ // Act over the colums up >> down , left >> right
        lst = 0;
        for(int j =  1 ; j <  (int)a.size(); j++){ //Sum from right to left and skip if there is an addition
            if(a[i][lst] == a[i][j]){
                a[i][j] *= 2;
                cnt++;
                a[i][lst] = 0;
                lst = j + 1;
                j++;
            }

            else if(a[i][j] != 0){
                lst = j;
            }
        }
    }

    for(int i = 0; i <  (int)a.size(); i++){ // Colapse matrix to the right
        pos = -1;
        for(int j = a.size() -1 ; j > - 1; j--){
            if(a[i][j] == 0 && pos == -1){
                pos = j;
            }
            else if (pos != -1 && a[i][j] != 0){
                a[i][pos] = a[i][j];
                a[i][j] = 0;
                pos--;
            }
        }
    }
    return cnt;
}

int slideU(vector<vector<int>> &a){\
    int pos, lst, cnt = 0;
    for(int j = 0; j  <  (int)a.size(); j++){ // Act over the colums up >> down , right >> left
        lst = a.size() -1;
        for(int i = a.size() - 2 ; i >= 0; i--){ //Calculate
            if(a[lst][j] == a[i][j]){
                a[i][j] *= 2;
                cnt++;
                a[lst][j] = 0;
                cnt++;
                lst = i-1;
                i--;
            }
            else if(a[i][j] != 0){
                lst = i;
            }
        }
}
    for(int j = 0; j <  (int)a.size(); j++){ // Colapse matrix upwards
        pos = -1;
        for(int i = 0 ; i <  (int)a.size(); i++){
            if(a[i][j] == 0 && pos == -1){
                pos = i;
            }
            else if (pos != -1 && a[i][j] != 0){
                a[pos][j] = a[i][j];
                a[i][j] = 0;
                pos++;
            }
        }
    }
    return cnt;
}

int slideD(vector<vector<int>> &a){\
    int pos, lst, cnt = 0;
    for(int j = 0; j  <  (int)a.size(); j++){ // Act over the colums up >> down , right >> left
        lst = 0;
        for(int i = 1 ; i <  (int)a.size(); i++){ //Calculate
            if(a[lst][j] == a[i][j]){
                a[i][j] *= 2;
                cnt++;
                a[lst][j] = 0;
                lst = i+1;
                i++;
            }
            else if(a[i][j] != 0){
                lst = i;
            }
        }
}
    for(int j = 0; j <  (int)a.size(); j++){ // Colapse matrix upwards
        pos = -1;
        for(int i = a.size() -1  ; i > -1; i--){
            if(a[i][j] == 0 && pos == -1){
                pos = i;
            }
            else if (pos != -1 && a[i][j] != 0){
                a[pos][j] = a[i][j];
                a[i][j] = 0;
                pos--;
            }
        }
    }
    return cnt;
}

bool check(vector<vector<int>> &a){
  int cnt = 0;
    for(int i = 0; i < (int) a.size(); i++){
      for(int j = 0; j < (int) a.size(); j++){
          if(a[i][j]){
            cnt++;
            if(cnt > 1){
              return false;
            }
          }
      }
    }
    if(cnt == 1){
      return true;
    }
    return false;
}
void recursion(vector<vector<vector<int>>> &vec, int k, int m ){ // Params vector vec , rec depth, max rep

  int size = vec.size();
  
  vector<vector<vector<int>>> aux;
  int i;
  for (i = 0; i < size; i++){

    if((k == m  && !check(vec[i])) || k >= best){
      return;
    }
    if(check(vec[i])){
      if(k < best){
        best = k;
      }
      return;
    }

    vector<vector<int>> a(vec[i]), b(vec[i]), c(vec[i]), d(vec[i]);

    slideD(a);
    slideL(b);
    slideR(c);
    slideU(d);

    aux.push_back(a);
    aux.push_back(b);
    aux.push_back(c);
    aux.push_back(d);

  }
  recursion(aux, k+1, m);
  
}


void solve(vector<vector<int>> &a, int k){
   //slideD(a);
   //printpointset(a);
   map<int, int> m;

   //Preprocess the data
   for(int i = 0; i < (int) a.size(); i++){
     for(int j = 0; j < (int) a.size(); j++){
       auto it = m.find(a[i][j]);
       if(a[i][j] != 0){
         if(it != m.end()){
           m[a[i][j]]++;
         }
         else{
           m[a[i][j]] = 1;
         }
       }
     }
   }

    /* for(auto it = m.begin(); it != m.end(); it++){
      cout << it->first << " " << it->second  << endl;
    } */
   bool val = check(a);
   for(auto it = m.begin(); it != m.end(); it++){
     if(it->second % 2 != 0 && !val){
       cout << "no solution" << endl;
       return;
     }
     else{
       if(it != --m.end()){
         m[it->first * 2] += it->second /2;
       }
     }
   }

  /* for(auto it = m.begin(); it != m.end(); it++){
      cout << it->first << " " << it->second  << endl;
    } */
   //Check if the square is valid

   vector<vector<vector<int>>> vec = {a}; 

   recursion(vec,0,k);
   if(best == INT_MAX){
     cout << "no solution" << endl;
   }
   else{
     cout << best << endl;
   }
   //cout << -1 << endl;
   //If it is valid then we solve
   //recursion(a,k, 0);
   //cout << best << endl;
}


int main(){
    int tt, n, k, p;
    cin >> tt;
    for(int i = 0; i < tt; i++){
      best = INT_MAX;
        cin >> n>> k;
        vector<vector<int>> a;
        for(int j = 0; j < n; j++){
            vector<int> row;
            for(int l = 0; l < n; l++){
                cin >> p;
                row.push_back(p);
            }
            a.push_back(row);
        }
        //printpointset(a);
        solve(a,k);


    }
}
