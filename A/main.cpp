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

void pp(int k ){
  for(int i = 0 ; i < k; i++)
    cout << " " ;
}
int slideL(vector<vector<int>> &a){\
    int pos, lst, cnt = 0;
    for(int i = 0; i  <  (int)a.size(); i++){ // Act over the colums up >> down , right >> left
        lst = a.size() -1;
        for(int j = a.size() - 2 ; j >= 0; j--){ //Calculate
            if(a[i][lst] == a[i][j]){
                a[i][j] *= 2;
                if(a[i][j] != 0)
                  cnt++;
                a[i][lst] = 0;
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
                if(a[i][j] != 0)
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

int slideU(vector<vector<int>> &a){
    int pos, lst, cnt = 0;
    for(int j = 0; j  <  (int)a.size(); j++){ // Act over the colums up >> down , right >> left
        lst = a.size() -1;
        for(int i = a.size() - 2 ; i >= 0; i--){ //Calculate
            if(a[lst][j] == a[i][j]){
                a[i][j] *= 2;
                if(a[i][j] != 0)
                  cnt++;
                a[lst][j] = 0;
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
                if(a[i][j] != 0)
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
    if(cnt == 1 || cnt == 0){
      return true;
    }
    return false;
}

bool horizontalCheck(vector<vector<int>> &a, vector<vector<int>> &b){ // It is guaranteed that the matrixes have the same size
int l1,r1,l2,r2, leftmost = -1, rightmost = -1;
for(int i = 0; i < (int) a.size(); i++){
      int l1 = -1,r1 = -1,l2 = -1,r2 = -1;
      for(int j = 0; j < (int) a.size(); j++){
        if(a[i][j] != 0 && l1 == -1){
          l1 = j;
          r1 = j;
        }
        else if(a[i][j] != 0)
          r1 = j;

        if(b[i][j] != 0 && l2 == -1){
          l2 = j;
          r2 = j;
        }
        else if(b[i][j] != 0)
          r2 = j;
      }
      cout << l1 << " "<< r1 << " "<< l2 << " "<< r2<< endl; 
      if(rightmost ==  -1){
        cout << "result" << r2 -r1 << endl;
        rightmost = max(r2 - r1, 0);
      }
      if(leftmost ==  -1){
        leftmost = max(l2 - l1,0);
      }
      else if(r2 -r1 != rightmost || l2-l1 != leftmost){
        return false;
      }
      cout << "Rm Lm " << rightmost << " " << leftmost << endl;

    }
    return true;
}




void recursion(vector<vector<int>> &a, int k, int m){ // Params vector a , rec depth, max rep , last mv
  bool val = check(a);
  //cout << "k is " << k <<" " << lmv[0] << " " << lmv[1] << " " << lmv[2] << " " << lmv[3] << endl;
  if((k == m  && !val) || k >= best){
    return;
  }
  if(val){
    if(k < best){
      best = k;
    }
    //cout << "found"  << endl;
    //cout << m << " "<< k << " "<< best << endl;
    //printpointset(a);
    return;
  }
  vector<vector<int>> b(a), c(a),d(a), e(a); ; 
  int t1,t2 ,t3,t4;

  t1 = min(slideL(b),1);
  t2 = min(slideR(c),1);
  t3 = min(slideU(d),1); 
  t4 = min(slideD(e),1); 
  
  if(d == b || c == e)
    return;

  if(a != b)
    recursion(b,k+1,m);
  if(a != c)
  recursion(c,k+1,m);
  if(a != d)
  recursion(d,k+1,m);
  if(a != e)
  recursion(e,k+1,m);


  return;


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

   recursion(a,0,k);
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

void test(vector<vector<int>> &a, int k){
  vector<vector<int>> b(a), c(a),d(a), e(a);
  int t1,t2 ,t3,t4;

  cout  << "here" << endl;
  t1 = min(slideL(b),1);
  t2 = min(slideR(c),1);
  t3 = min(slideU(d),1); 
  t4 = min(slideD(e),1); 

  cout << horizontalCheck(a,b) << endl;
  cout << horizontalCheck(a,c) << endl;
 // cout << horizontalCheck(a,d) << endl;
 // cout << horizontalCheck(a,e) << endl;


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
