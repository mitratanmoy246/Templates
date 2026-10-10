
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

constexpr int MOD = 1000000007;
constexpr ll INF = 1000000000000000000LL;

#define fast ios::sync_with_stdio(false); cin.tie(nullptr)
#define pb push_back
#define F first
#define S second
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) ((int)(v).size())

#define read(a,n) for(int i=0;i<n;i++) cin>>a[i]
#define read1(a,n) for(int i=1;i<=n;i++) cin>>a[i]
#define print(v) for(auto x:v) cout<<x<<' '; cout<<'\n'
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define endl '\n'

#define eb emplace_back
#define mp make_pair
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define repn(i,n) for(int i=0;i<(n);i++)
#define rev(i,a,b) for(int i=(a);i>=(b);i--)
#define each(x,a) for(auto &x:a)

#define vec2d(v,n,m,val) vector<vector<int>> v(n,vector<int>(m,val))
#define vec2dll(v,n,m,val) vector<vector<ll>> v(n,vector<ll>(m,val))

// -------------------- PBDS --------------------
// GNU extension: order_of_key(x) counts elements < x.
// find_by_order(k) returns the iterator at zero-based index k.
// oset stores unique integers.
template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

using oset = ordered_set<int>;

using oset_desc = tree<int,null_type,greater<int>,
    rb_tree_tag,tree_order_statistics_node_update>;

// -------------------- BITWISE --------------------
// Set bit:       n |= (1LL<<i);
// Unset bit:     n &= ~(1LL<<i);
// Toggle bit:    n ^= (1LL<<i);
// Check bit:     (n>>i)&1LL
// Even/odd:      n%2==0 / n%2!=0
// Lowest bit:    n&-n
// Count bits:    __builtin_popcountll(n)

#define setBit(x,i) ((x)|(1LL<<(i)))
#define clearBit(x,i) ((x)&~(1LL<<(i)))
#define toggleBit(x,i) ((x)^(1LL<<(i)))
#define checkBit(x,i) (((x)>>(i))&1LL)
#define popcount(x) __builtin_popcountll(x)
#define isPowerOfTwo(x) ((x)>0 && (((x)&((x)-1))==0))

// -------------------- BASIC HELPERS --------------------

template<class T>
bool chkmin(T &a,T b){
    if(b<a){
        a=b;
        return true;
    }
    return false;
}

template<class T>
bool chkmax(T &a,T b){
    if(a<b){
        a=b;
        return true;
    }
    return false;
}

ll gcdll(ll a,ll b){
    while(b){
        ll r=a%b;
        a=b;
        b=r;
    }
    return a<0?-a:a;
}

ll lcmll(ll a,ll b){
    if(a==0 || b==0)return 0;
    return a/gcdll(a,b)*b;
}

// -------------------- POWER --------------------

// Ordinary power; may overflow.
ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res*=a;
        b>>=1;
        if(b)a*=a;
    }
    return res;
}

// Modular power.
ll modpow(ll a,ll b,ll mod=MOD){
    ll res=1;
    a%=mod;
    while(b>0){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

// Valid for prime mod when n is not divisible by mod.
ll modInverse(ll n,ll mod=MOD){
    return modpow(n,mod-2,mod);
}

// -------------------- NUMBER THEORY --------------------

bool isPrime(ll n){
    if(n<2)return false;
    if(n<=3)return true;
    if(n%2==0 || n%3==0)return false;

    for(ll i=5;i<=n/i;i+=6){
        if(n%i==0 || n%(i+2)==0)return false;
    }
    return true;
}

// Sieve: prime[i] = 1 if i is prime.
vi sieve(int n){
    vi prime(n+1,1);
    prime[0]=0;
    if(n>=1)prime[1]=0;

    for(ll i=2;i*i<=n;i++){
        if(prime[i]){
            for(ll j=i*i;j<=n;j+=i){
                prime[j]=0;
            }
        }
    }
    return prime;
}

// Smallest prime factor sieve.
// Call buildSPF(max_value) before factorization.
vi spf,primes;

void buildSPF(int n){
    spf.assign(n+1,0);
    primes.clear();

    for(int i=2;i<=n;i++)spf[i]=i;

    for(ll i=2;i*i<=n;i++){
        if(spf[i]==i){
            for(ll j=i*i;j<=n;j+=i){
                if(spf[j]==j)spf[j]=i;
            }
        }
    }

    for(int i=2;i<=n;i++){
        if(spf[i]==i)primes.pb(i);
    }
}

vi getFactorization(int x){
    vi ret;
    if(x<1 || x>=sz(spf))return ret;

    while(x>1){
        ret.pb(spf[x]);
        x/=spf[x];
    }
    return ret;
}

// Returns {prime, exponent}.
vector<pii> getFactorizationPowers(int x){
    vector<pii> ret;
    if(x<1 || x>=sz(spf))return ret;

    while(x>1){
        int p=spf[x],cnt=0;

        while(x%p==0){
            cnt++;
            x/=p;
        }
        ret.eb(p,cnt);
    }
    return ret;
}

vi getDivisors(int n){
    vi divs;
    if(n<=0)return divs;

    for(ll i=1;i*i<=n;i++){
        if(n%i==0){
            divs.pb(i);
            if(i*i!=n)divs.pb(n/i);
        }
    }

    sort(all(divs));
    return divs;
}

int countDivisors(int n){
    if(n<=0)return 0;

    int cnt=0;
    for(ll i=1;i*i<=n;i++){
        if(n%i==0){
            cnt++;
            if(i*i!=n)cnt++;
        }
    }
    return cnt;
}

ll sumDivisors(int n){
    if(n<=0)return 0;

    ll sum=0;
    for(ll i=1;i*i<=n;i++){
        if(n%i==0){
            sum+=i;
            if(i*i!=n)sum+=n/i;
        }
    }
    return sum;
}

int phi(int n){
    if(n<=0)return 0;

    int res=n;
    for(ll i=2;i*i<=n;i++){
        if(n%i==0){
            while(n%i==0)n/=i;
            res-=res/(int)i;
        }
    }

    if(n>1)res-=res/n;
    return res;
}

int countPrimesUpto(int n){
    return upper_bound(all(primes),n)-primes.begin();
}

// -------------------- GRAPH: BFS --------------------

// Vertices must fit the indexing used by adj and vis.
void bfs(int src,vector<vi>& adj,vi& vis){
    queue<int> q;
    q.push(src);
    vis[src]=1;

    while(!q.empty()){
        int u=q.front();
        q.pop();

        for(int v:adj[u]){
            if(!vis[v]){
                vis[v]=1;
                q.push(v);
            }
        }
    }
}

// -------------------- GRAPH: DFS --------------------

void dfs(int u,vector<vi>& adj,vi& vis){
    vis[u]=1;

    for(int v:adj[u]){
        if(!vis[v])dfs(v,adj,vis);
    }
}

// -------------------- DSU / UNION FIND --------------------

struct DSU{
    vi par,sz;

    DSU(int n){
        par.resize(n+1);
        sz.assign(n+1,1);
        iota(all(par),0);
    }

    int find(int x){
        if(par[x]==x)return x;
        return par[x]=find(par[x]);
    }

    bool unite(int a,int b){
        a=find(a);
        b=find(b);

        if(a==b)return false;
        if(sz[a]<sz[b])swap(a,b);

        par[b]=a;
        sz[a]+=sz[b];
        return true;
    }
};

// -------------------- DEBUG --------------------

#ifndef ONLINE_JUDGE
#define debug(x) cerr<<#x<<" = "; _print(x); cerr<<'\n'
#else
#define debug(x)
#endif

void _print(ll x){cerr<<x;}
void _print(ull x){cerr<<x;}
void _print(int x){cerr<<x;}
void _print(char x){cerr<<x;}
void _print(bool x){cerr<<(x?"true":"false");}
void _print(string x){cerr<<x;}
void _print(ld x){cerr<<x;}
void _print(double x){cerr<<x;}


// -------------------- SOLVE --------------------

void solve(){
    int n;
    cin>>n;

    vi a(n);
    read(a,n);

    // Write solution here.
}

signed main(){
    fast;

    int test_case=1;
    // cin>>test_case;

    for(int i=1;i<=test_case;i++){
        // cout<<"Case "<<i<<": ";
        solve();
    }

    return 0;
}
