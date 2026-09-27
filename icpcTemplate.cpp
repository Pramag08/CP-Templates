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
