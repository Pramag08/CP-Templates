#ifdef LOCAL
template<class A, class B> ostream& operator<<(ostream& o, const pair<A,B>& p) {
    return o << '(' << p.first << ", " << p.second << ')';
}
template<class T, class = decltype(begin(declval<T>())),
         class = enable_if_t<!is_same_v<T, string>>>
ostream& operator<<(ostream& o, const T& c) {
    o << '{'; for (auto it = begin(c); it != end(c); ++it) o << (it == begin(c) ? "" : ", ") << *it;
    return o << '}';
}
void _dbg() { cerr << endl; }
template<class H, class... T> void _dbg(H h, T... t) {
    cerr << h; if (sizeof...(t)) cerr << ", "; _dbg(t...);
}
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: ", _dbg(__VA_ARGS__)
#else
#define dbg(...) 42
#endif



//returns all 0-indexed starting positions where pattern p(substring) occurs in string s
vector<int> kmp(string s, string p){
    int n=s.size(), m=p.size();
    vector<int> lps(m), ans;

    for(int i=1,j=0;i<m;i++){
        while(j && p[i]!=p[j]) j=lps[j-1];
        if(p[i]==p[j]) j++;
        lps[i]=j;
    }

    for(int i=0,j=0;i<n;i++){
        while(j && s[i]!=p[j]) j=lps[j-1];
        if(s[i]==p[j]) j++;

        if(j==m){
            ans.push_back(i-m+1);
            j=lps[j-1];
        }
    }
    return ans;
}

// divs[x] contains all divisors of x in increasing order
const int N = 2e5;
vector<vector<int>> divs(N+1);

void build_divs(){
    for(int d=1;d<=N;d++)
        for(int x=d;x<=N;x+=d)
            divs[x].push_back(d);
}

//Fenwick point update
struct Fenwick {
    int n;
    vector<ll> tree;

    Fenwick(int n) : n(n), tree(n + 1, 0) {}

    // Adds delta to element at 0-based index i
    void add(int i, ll delta) {
        for (++i; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }

    // Returns prefix sum in [0, i]
    ll query(int i) {
        ll sum = 0;
        for (++i; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }

    // Returns range sum in [l, r] (0-based)
    ll query(int l, int r) {
        if (l > r || r < 0) return 0;
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }
};
