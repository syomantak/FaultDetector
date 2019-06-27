//By TheOneYouWant

#pragma GCC optimize ("-O2")
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define memreset(a) memset(a,0,sizeof(a))
#define testcase(t) int t;cin>>t;while(t--)
#define forstl(i,v) for(auto &i: v)
#define forn(i,e) for(int i = 0; i < e;++i)
#define forsn(i,s,e) for(int i = s; i < e;++i)
#define rforn(i,s) for(int i = s; i >= 0;--i)
#define rforsn(i,s,e) for(int i = s; i >= e;--i)
#define bitcount(a) __builtin_popcount(a) // set bits (add ll)
#define ln '\n'

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll,ll> p64;
typedef pair<int,int> p32;
typedef pair<int,p32> p96;
typedef vector<ll> v64;
typedef vector<int> v32; 
typedef vector<v32> vv32;
typedef vector<v64> vv64;
typedef vector<p32> vp32;
typedef vector<p64> vp64;
typedef vector<vp32> vvp32;
typedef map<int,int> m32;

const int LIM=1e5+5, MOD=1e9+7;
const ld EPS = 1e-9;

char logicalExpressionEvaluation(string str) 
{ 
    stack<char> arr; 
  
    // traversing string from the end. 
    for (int i = str.length() - 1; i >= 0; i--)  
    { 
        if(str[i]=='@') continue;
        if (str[i] == '[')  
        { 
            vector<char> s; 
            while (arr.top() != ']') 
            { 
                s.push_back(arr.top()); 
                arr.pop(); 
            } 
            arr.pop(); 
  
            // for NOT operation 
            if (s.size() == 3) 
            { 
                s[2] == '1' ? arr.push('0') : arr.push('1'); 
            } 
            // for AND and OR operation 
            else if (s.size() == 5) 
            { 
                int a = s[0] - 48, b = s[4] - 48, c; 
                // s[2] == '&' ? c = a & b : c = a | b; 
                if(s[2]=='&') c = a&b;
                else if(s[2]=='|') c=a|b;
                else if(s[2]=='^') c=a^b;
                else if(s[2]=='.'){
                    bool d = a&b;
                    if(d==0) c=1;
                    else c=0;
                }
                else if(s[2]=='%'){
                    bool d = a|b;
                    if(d==0) c=1;
                    else c=0;
                }
                arr.push((char)c + 48); 
            } 
        } 
        else
        { 
            arr.push(str[i]); 
        } 
    } 
    return arr.top(); 
} 

// int t,n,m,k,x,y,w;
signed main(){
    fastio;
    
    string s;
    getline(cin,s);
    // cout<<s<<ln;
    set<string> st;
    map<string,int> m;
    map<string,string> mapping;
    int num;
    cin>>num;
    forn(i,num){
        string x,y;
        cin>>x>>y;
        mapping[y] = x;
    }
    forn(i,s.length()){
        if(s[i]-'a'>=0 && s[i]-'z'<=0){
            char a1 =s[i];
            i++;
            string a3;
            a3 = "00";
            a3[0] = a1;
            a3[1] = s[i];
            // a3.append(s[i]);
            st.insert(a3);
        }
    }
    // cout<<st<<ln;
    bool p=0;
    int range = (1<<st.size());
    forn(i,range){
        int z = i;
        v32 v;
        map <int,int> mr;
        forn(i,st.size()){
            v.pb(z%2);
            z=z/2;
        }
        // cout<<i<<" "<<v<<ln;
        reverse(v.begin(),v.end());
        int it=0;
        forstl(r,st){
            m[r] = '0'+v[it];
            it++;
        }
        // cout<<i<<" "<<m['a']<<ln;
        string f=s;
        // cout<<i<<" "<<s<<ln;
        int cnt=0;
        forn(i,s.length()){
            if(s[i]-'a'>=0 && s[i]-'z'<=0){
                char x1 = s[i];
                i++;
                string x3;
                x3 = "00";
                x3[0] = x1;
                x3[1] = s[i];
                // x3.append(s[i]);
                f[i-1] = m[x3];
                f[i] = '@';
            }
        }
        // forstl(r,s){
        //     if(r-'a'>=0 && r-'z'<=0){
        //         f[cnt] = m[r];
        //     }
        //     cnt++;
        // }
        // cout<<i<<" "<<f<<ln;
        // cout<<i<<" "<<f<<ln;
        char ans = logicalExpressionEvaluation(f);
        if(ans=='1'){
            p=1;
            forstl(r,st){
                cout<<"Choose "<<mapping[r]<<" as "<<(char)m[r]<<ln;
            }
            break;
        }
    }

    
    if(!p) cout<<"Not possible"<<ln;

    return 0;
}