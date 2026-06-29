#include <bits/stdc++.h>
using namespace std;

// --- Types & Constants ---
using ll = long long; using vi = vector<int>; using vll = vector<ll>;
using pii = pair<int, int>; using pll = pair<ll, ll>;
const int MOD = 1e9 + 7; const ll INF = 1e18;

// --- Fast I/O & Macros ---
#define fastio() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rev(i, a, b) for(int i = a; i >= (b); --i)
#define each(a, x) for(auto& a : x)
#define yes cout << "YES\n"
#define no cout << "NO\n"

// --- Math & Utils ---
template<class T> bool cmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool cmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
ll binpow(ll a, ll b, ll m = MOD) { ll r = 1; a %= m; while(b) { if(b&1) r = r * a % m; a = a * a % m; b >>= 1; } return r; }
bool is_prime(ll n) { if(n<2) return 0; if(n%2==0||n%3==0) return n<=3; for(ll i=5; i*i<=n; i+=6) if(n%i==0||n%(i+2)==0) return 0; return 1; }

// --- Solution ---
void solve() {
    
}

int main() {
    fastio();
    int t = 1; 
    cin >> t;
    while(t--) solve();
    return 0;
}