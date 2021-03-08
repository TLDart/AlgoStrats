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
void slideL(vector<vector<int>> &a, int &mrg, int &swp){
    int pos, lst;
   
    for(int i = 0; i  <  (int)a.size(); i++){ // Act over the colums up >> down , left >> right
        lst = 0;
        for(int j =  1 ; j <  (int)a.size(); j++){ //Sum from right to left and skip if there is an addition
            if(a[i][lst] == a[i][j]){
                a[i][j] *= 2;
                if(a[i][j] != 0)
                  mrg++;
                a[i][lst] = 0;
                lst = j + 1;
                j++;
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
                swp++;
            }
        }
    }
}

void slideR(vector<vector<int>> &a, int &mrg, int &swp){
    int pos,lst;
    for(int i = 0; i  <  (int)a.size(); i++){ // Act over the colums up >> down , right >> left
        lst = a.size() -1;
        for(int j = a.size() - 2 ; j >= 0; j--){ //Calculate
            if(a[i][lst] == a[i][j]){
                a[i][j] *= 2;
                if(a[i][j] != 0)
                  mrg++;
                a[i][lst] = 0;
                lst = j-1;
                j--;
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
                swp++;
            }
        }
    }
}

void slideU(vector<vector<int>> &a, int &mrg, int &swp){
    int pos, lst;
    for(int j = 0; j  <  (int)a.size(); j++){ // Act over the colums up >> down , right >> left
        lst = 0;
        for(int i = 1 ; i <  (int)a.size(); i++){ //Calculate
            if(a[lst][j] == a[i][j]){
                a[i][j] *= 2;
                if(a[i][j] != 0)
                  mrg++;
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
        for(int i = 0 ; i <  (int)a.size(); i++){
            if(a[i][j] == 0 && pos == -1){
                pos = i;
            }
            else if (pos != -1 && a[i][j] != 0){
                a[pos][j] = a[i][j];
                a[i][j] = 0;
                pos++;
                swp++;
            }
        }
    }
}

void slideD(vector<vector<int>> &a, int &mrg, int &swp){
    int pos, lst;
   
for(int j = 0; j  <  (int)a.size(); j++){ // Act over the colums up >> down , right >> left
        lst = a.size() -1;
        for(int i = a.size() - 2 ; i >= 0; i--){ //Calculate
            if(a[lst][j] == a[i][j]){
                a[i][j] *= 2;
                if(a[i][j] != 0)
                  mrg++;
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
        for(int i = a.size() -1  ; i > -1; i--){
            if(a[i][j] == 0 && pos == -1){
                pos = i;
            }
            else if (pos != -1 && a[i][j] != 0){
                a[pos][j] = a[i][j];
                a[i][j] = 0;
                pos--;
                swp++;
            }
        }
    }
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

void printrec(vector<vector<int>> &v, int recLevel, string move){
    cout << "---------------------" << endl;
    cout << "Recursion Depth " << recLevel<< endl;
    cout << "Move " << move << endl;
    printpointset(v); 
    cout << "---------------------" << endl;
}


void recursion(vector<vector<int>> &a, int k, int m, int ls, int lu){ // Params vector a , rec depth, max rep , last mv
  bool val = check(a);
  if(val){
      if(k < best){
        best = k;
      }
      return;
    }
  if((k == m) || k >= best){
    return;
  }
  
  int m1 = 0,m2 = 0 ,m3 = 0,m4 = 0;
  int s1 = 0,s2 = 0 ,s3 = 0,s4 = 0;
  if(ls){
    vector<vector<int>> b(a), c(a);
    slideL(b, m1, s1);
    slideR(c, m2, s2);

    /* printrec(b,k,"Left");
    cout << m1 << " " << s1 << endl;
    printrec(c,k,"Right");
    cout << m2 << " " << s2 << endl; */

    if (m1 || s1)
      recursion(b,k+1,m, m1, 1);
    if(m2 || s2)
      recursion(c,k+1,m, m2, 1);
  }

  if(lu){
    vector<vector<int>> d(a), e(a); 

    slideU(d, m3, s3);
    slideD(e, m4, s4);

   /*  printrec(d,k,"Up");
    cout << m3 << " " << s3 << endl;
    printrec(e,k,"DOwn");
    cout << m4 << " " << s4 << endl; */

    if (m3 || s3)
      recursion(d,k+1,m, 1, m3);
    if(m4 || s4){
      recursion(e,k+1,m, 1, m4);
    }
  }

  return;

}
void solve(vector<vector<int>> &a, int k){
   map<int, int> m;

   //Preprocess the data
   int sum = 0;
  for(int i = 0; i < (int) a.size(); i++){
     for(int j = 0; j < (int) a.size(); j++){
        sum+= a[i][j];
     }
   }
   //Check if the square is valid
  if(log2(sum) != floor(log2(sum))){
    cout << "no solution" << endl;
    return;
  }
  else
   recursion(a,0,k,2,2);

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
        cin >> n >> k;
        vector<vector<int>> a;
        for(int j = 0; j < n; j++){
            vector<int> row;
            for(int l = 0; l < n; l++){
                cin >> p;
                row.push_back(p);
            }
            a.push_back(row);
        }
        solve(a,k);
    }
}
