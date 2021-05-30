#include <cstdio>
#include <iostream>
#include<string>
#include<sstream>
#include <stdlib.h> 
#define N 300
 
using namespace std;
int main() {
    int s[N][N];
    int lena = 0,lenb = 0,sub = 0,ins = 0,del = 0; 
	int i,j;
	string t[2];
	getline(cin, t[0], ';');
	getline(cin, t[1]);
	stringstream ss(t[0]);
	while (ss){
	 ss>> s[lena+2][0];
	 lena++;
	 s[lena+1][1]=lena;
	 }
	 lena--;
	 ss.str("");
	 ss.clear();
	 ss<<t[1];
	 while (ss){
	 ss>> s[0][lenb+2];
	 lenb++;
	 s[1][lenb+1]=lenb;
	 }
	 lenb--;
    s[0][0] = 0;
    s[1][0] = 0;
    s[0][1] = 0;
    s[1][1] = 0;
   if (lena == 0 && lenb == 0) {
		printf("0 0 0");
	}else{		
		for (i = 2; i <= lena+1; i++) {
        for (j = 2; j <= lenb+1; j++) {
            int cost = s[i][0] == s[0][j] ? 0 : 1;
            int min = (s[i-1][j]+1 < s[i][j-1]+1 ? s[i-1][j]+1 : s[i][j-1]+1);	
			min = (min < s[i-1][j-1]+cost ? min : s[i-1][j-1]+cost);
            s[i][j] = min;
        }
    }
   
     int m=lenb+1; int n=lena+1;
	    while(n > 0 || m > 0) 
    {
        
        if(n && s[n - 1][m] + 1 == s[n][m])
        {
            ins++;
            n--;
            continue;
        }
        if(m && s[n][m - 1] + 1 == s[n][m])
        {
            del++;
            m--;
            continue;
        }
        if(n && m && s[n - 1][m - 1] + 1 == s[n][m])
        {
            sub++;
            n--, m--;
            continue;
        }
        n--, m--;
    }
		printf("%d %d %d", ins,del,sub);
		
	}
	return 0;
}