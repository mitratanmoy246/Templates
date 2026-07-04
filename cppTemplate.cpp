#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

// PBDS Utilities:
// order_of_key(k): returns the number of elements strictly smaller than k.
// find_by_order(k): returns an iterator to the k-th largest element (0-indexed).
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

// ---------- Bit Utilities ----------
// setBit: Sets the i-th bit of x to 1. (0-indexed)
#define setBit(x, i) ((x) | (1LL << (i)))
// clearBit: Sets the i-th bit of x to 0. (0-indexed)
#define clearBit(x, i) ((x) & ~(1LL << (i)))
// toggleBit: Flips the i-th bit of x. (0-indexed)
#define toggleBit(x, i) ((x) ^ (1LL << (i)))
// checkBit: Returns true if the i-th bit of x is 1. (0-indexed)
#define checkBit(x, i) (((x) >> (i)) & 1LL)
// popcount: Count number of set bits in a 32-bit integer.
#define popcount(x) __builtin_popcount(x)
// popcountll: Count number of set bits in a 64-bit integer.
#define popcountll(x) __builtin_popcountll(x)
// isPowerOfTwo: Returns true if x is a power of 2 (e.g., 1, 2, 4, 8...).
#define isPowerOfTwo(x) ((x) && !((x) & ((x) - 1LL)))

const int MOD = 1e9 + 7;
const ll LINF = 1e18;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
ll binpow(ll a, ll b, ll m = MOD) { ll res = 1; a %= m; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1; } return res; }

// ---------- Math Utilities ----------
// Modular inverse using Fermat's Little Theorem.
// Time Complexity: O(log m)
// Use when m is prime (e.g., MOD = 1e9+7) and you need to perform division under modulo.
// Prerequisites: Your existing binpow function.
ll modInverse(ll n, ll m = MOD) { return binpow(n, m - 2, m); }

// ---------- Number Theory ----------

// 1. Optimized primality test
// Checks if n is a prime number using the 6k +/- 1 optimization.
// Time Complexity: O(sqrt(n))
// Use it for independent primality checks without a sieve (handles numbers up to 10^14).
bool isPrime(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// 2. SPF (Smallest Prime Factor) Sieve
vector<int> spf;
vector<int> primes;

// Computes SPF for all numbers up to n and fills the prime list.
// Clears previous data automatically if called multiple times.
// Time Complexity: O(n log log n)
// When to use: Call ONCE globally or in main() before test cases if n <= 10^7.
// Crucial for fast factorization of multiple numbers.
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

// 3. Prime factorization (with repetitions)
// Returns all prime factors of x (e.g., 12 returns {2, 2, 3}).
// Time Complexity: O(log x)
// Prerequisites: sieve(N) must be called first, where N >= x.
vector<int> getFactorization(int x) {
    vector<int> ret;
    while (x != 1) {
        ret.pb(spf[x]);
        x /= spf[x];
    }
    return ret;
}

// 4. Prime factorization with powers
// Returns prime factors and their frequencies (e.g., 12 returns {(2, 2), (3, 1)}).
// Time Complexity: O(log x)
// Prerequisites: sieve(N) must be called first, where N >= x.
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

// 5. Divisors
// Returns a sorted vector of all divisors of n.
// Time Complexity: O(sqrt(n) * log(sqrt(n)))
// When to use: To find every number that perfectly divides n (e.g., 12 returns {1, 2, 3, 4, 6, 12}).
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

// 6. Euler Totient (phi)
// Returns the number of integers up to n that are coprime to n.
// Time Complexity: O(sqrt(n))
// When to use: Fraction reductions, modular exponentiation where powers are huge (Euler's Theorem).
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

// 7. Count divisors
// Returns the total number of divisors of n without storing them.
// Time Complexity: O(sqrt(n))
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

// 8. Sum of divisors
// Returns the sum of all divisors of n.
// Time Complexity: O(sqrt(n))
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

// 9. Prime counting helper
// Returns the count of primes less than or equal to n.
// Time Complexity: O(log(number of primes))
// Prerequisites: sieve(N) must be called first, where N >= n.
int countPrimesUpto(int n) {
    return upper_bound(all(primes), n) - primes.begin();
}

template<typename T> bool chkmin(T &a, T b) { return (b < a ? a = b, 1 : 0); }
template<typename T> bool chkmax(T &a, T b) { return (b > a ? a = b, 1 : 0); }

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

    int t=1;
    cin>>t;
    
    while(t--) {
        solve();
    }
    
    return 0;
}