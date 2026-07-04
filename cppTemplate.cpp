/*
 * Author      : Tanmoy Mitra
 * Codeforces  : mitratanmoy246
 * CodeChef    : band_deed_94
 * Language    : GNU C++23
 * Version     : 1.3
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

// --- PBDS ---
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> oset;
typedef tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update> oset_desc;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define mp make_pair
#define F first
#define S second

#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(a) ((int)(a).size())

#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define repn(i, n) for(int i = 0; i < (n); ++i)
#define rev(i, a, b) for(int i = (a); i >= (b); --i)
#define rep_str(i, s) for(int i = 0; s[i] != '\0'; ++i)
#define each(x, a) for(auto &x : a)

#define read(a, n) do { for(int i = 0; i < (n); ++i) cin >> a[i]; } while(0)
#define read1(a, n) do { for(int i = 1; i <= (n); ++i) cin >> a[i]; } while(0)
#define printv(a) for(auto &x : a) cout << x << " "; cout << "\n";
#define nl cout<<'\n'

#define vec2d(v, n, m, val) vector<vector<int>> v(n, vector<int>(m, val))
#define vec2dll(v, n, m, val) vector<vector<ll>> v(n, vector<ll>(m, val))

// --- Bit Utilities ---
#define setBit(x, i) ((x) | (1LL << (i)))
#define clearBit(x, i) ((x) & ~(1LL << (i)))
#define toggleBit(x, i) ((x) ^ (1LL << (i)))
#define checkBit(x, i) (((x) >> (i)) & 1LL)
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
#define isPowerOfTwo(x) ((x) && !((x) & ((x) - 1LL)))

const int MOD = 1e9 + 7;
const ll LINF = 1e18;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
ll binpow(ll a, ll b, ll m = MOD) { ll res = 1; a %= m; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1; } return res; }
ll modInverse(ll n, ll m = MOD) { return binpow(n, m - 2, m); }

// --- Number Theory ---
bool isPrime(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

vector<int> spf;
vector<int> primes;
void sieve(int n) {
    spf.assign(n + 1, 0);
    primes.clear();
    for (int i = 2; i <= n; i++) spf[i] = i;
    for (int i = 2; i * i <= n; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= n; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        if (spf[i] == i) primes.pb(i);
    }
}

vector<int> getFactorization(int x) {
    vector<int> ret;
    while (x != 1) {
        ret.pb(spf[x]);
        x /= spf[x];
    }
    return ret;
}

vector<pair<int, int>> getFactorizationPowers(int x) {
    vector<pair<int, int>> ret;
    while (x != 1) {
        int p = spf[x];
        int count = 0;
        while (x % p == 0) {
            count++;
            x /= p;
        }
        ret.eb(p, count);
    }
    return ret;
}

vector<int> getDivisors(int n) {
    vector<int> divs;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divs.pb(i);
            if (i * i != n) divs.pb(n / i);
        }
    }
    sort(all(divs));
    return divs;
}

int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

int countDivisors(int n) {
    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            count++;
            if (i * i != n) count++;
        }
    }
    return count;
}

long long sumDivisors(int n) {
    long long sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) sum += (n / i);
        }
    }
    return sum;
}

int countPrimesUpto(int n) {
    return upper_bound(all(primes), n) - primes.begin();
}

template<typename T> bool chkmin(T &a, T b) { return (b < a ? a = b, 1 : 0); }
template<typename T> bool chkmax(T &a, T b) { return (b > a ? a = b, 1 : 0); }

// --- Debugging ---
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" = "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.F); cerr << ","; _print(p.S); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

void solve() {
    
}

int main() {
    fastio();

    int t = 1;
    cin >> t;
    
    while(t--) {
        solve();
    }
    
    return 0;
}