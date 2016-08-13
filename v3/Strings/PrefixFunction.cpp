// Ver v2/strings.cpp
//  * KMP + Automáta (Generalización)
//  * Z-function

vector<int> prefix_function (string s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}


const int alphabet = 256; 
vector<vector<int>> build_automata(string s) {
    s += '#';
    int n = (int) s.length();
    vector<int> pi = prefix_function (s);
    vector <vector<int>> aut (n, vector<int> (alphabet));
    for (int i=0; i<n; ++i)
        for (int c=0; c<alphabet; ++c)
            if (i > 0 && c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + (c == s[i]);
    return aut;
}
