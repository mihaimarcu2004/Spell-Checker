#include <bits/stdc++.h>

using namespace std;

ifstream f ("date.in");
ofstream g ("date.out");

ifstream fi ("perechi.txt");

int nrcuv;
string s;

struct el
{
    char lit;
    int oprit;
    vector <int> fiu;
    int index;
};
vector <el> trie;

int cont=1;
string cuv;
string cuvant;
int dp[350][350];
int minim=99999999999;
int ind;


struct per
{
    string a;
    string b;
    bool operator < (per A) const
    {
        return b<A.b;
    }

};
map <per, int> m;
vector <int> variante;

void DFS(int nod, int adanc)
{
    if(nod!=1)
    {
        char c=trie[nod].lit;
        for(int i=1; i<cuv.size(); ++i)
        {
            char xx=cuv[i];
            if(xx==c)
                dp[i][adanc]=min(dp[i][adanc], dp[i-1][adanc-1]);

            int x=dp[i][adanc-1]+1;
            int y=dp[i-1][adanc-1]+1;
            int z=dp[i-1][adanc]+1;
            dp[i][adanc]=min(dp[i][adanc], min(x, min(y, z)));
            ///cout<<trie[nod].lit<<" "<<i<<" "<<adanc<<" "<<dp[i][adanc]<<"\n";

        }
        if(trie[nod].oprit==1 && minim>dp[cuv.size()-1][adanc])
        {
            variante.clear();
            minim=dp[cuv.size()-1][adanc];
            ind=trie[nod].index;
        }
        if(trie[nod].oprit==1 && minim==dp[cuv.size()-1][adanc])
            variante.push_back(trie[nod].index);

        for(int x=0; x<trie[nod].fiu.size(); ++x)
        {
            int fiu=trie[nod].fiu[x];
            DFS(fiu, adanc+1);
        }
        for(int i=1; i<cuv.size(); ++i)
            dp[i][adanc]=999999999;
    }
    else
    {
        for(int x=0; x<trie[nod].fiu.size(); ++x)
        {
            int fiu=trie[nod].fiu[x];
            DFS(fiu, adanc);
        }
    }


}


void baga(int i, int nod, int index)
{
    if(i==s.size()-1)
    {
        trie[nod].oprit=1;
        trie[nod].index=index;
    }
    else
    {
        int pus=0;
        for(int x=0; x<trie[nod].fiu.size(); ++x)
        {
            if(s[i+1]==trie[trie[nod].fiu[x]].lit)
                baga(i+1, trie[nod].fiu[x], index), pus=1;
        }
        if(pus==0)
        {
            ++cont;
            el x;
            x.lit=s[i+1];
            x.oprit=0;
            x.index=index;
            trie.push_back(x);
            trie[nod].fiu.push_back(cont);

            baga(i+1, cont, index);
        }
    }
}
string raspuns;
string ras;
void afiseaza(int nod)
{
    if(trie[nod].oprit==1 && trie[nod].index==ind)
    {
        ras=raspuns;
        g<<raspuns<<" ";
        return;
    }
    for(int x=0; x<trie[nod].fiu.size(); ++x)
    {
        raspuns.push_back(trie[trie[nod].fiu[x]].lit);
        afiseaza(trie[nod].fiu[x]);
        raspuns.pop_back();
    }
}


void cafiseaza(int nod)
{
    if(trie[nod].oprit==1 && trie[nod].index==ind)
    {
        ras=raspuns;
       /// cout<<raspuns<<"\n";
        return;

    }
    for(int x=0; x<trie[nod].fiu.size(); ++x)
    {
        raspuns.push_back(trie[trie[nod].fiu[x]].lit);
        cafiseaza(trie[nod].fiu[x]);
        raspuns.pop_back();
    }
}

void cer1(int nod)
{
    if(trie[nod].oprit==1)
        g<<raspuns<<"\n";
    for(int x=0; x<trie[nod].fiu.size(); ++x)
    {
        raspuns.push_back(trie[trie[nod].fiu[x]].lit);
        if(trie[nod].fiu[x]<100000)
        cer1(trie[nod].fiu[x]);
        raspuns.pop_back();
    }
}
void stergere(int nod, int adanc)
{
    if(adanc==cuv.size())
        trie[nod].oprit=0;
    else
        for(int x=0; x<trie[nod].fiu.size(); ++x)
        {
            int fiu=trie[nod].fiu[x];
            stergere(fiu, adanc+1);
        }


}

int main()
{
    for(int i=1; i<=100; ++i)
        dp[0][i]=dp[i][0]=i;
    for(int i=1; i<=100; ++i)
        for(int j=1; j<=100; ++j)
            dp[i][j]=999999;
    f>>nrcuv;
    el x;
    trie.push_back(x);
    x.lit='\0';
    x.oprit=0;

    trie.push_back(x);
    for(int i=1; i<=nrcuv; ++i)
    {
        f>>s;
        baga(-1,1, i);
    }
    int ord=0;
    int lastlit;
    string prim, secund;
    int val;
    fi>>val;
    while(fi>>prim>>secund>>val)
    {
        per A;
        A.a=prim;
        A.b=secund;
        m[A]=val;
    }

    while(cin>>cuv)
    {

        /// cout<<cuv<<"\n";
        if(cuv=="0")
        {
            ofstream fi ("perechi.txt");
            fi<<0<<"\n";
            for(auto x:m)
            {
                fi<<x.first.a<<" "<<x.first.b<<" "<<x.second<<"\n";
            }

            return 0;
        }

        else if(cuv=="1")
        {
            while(!raspuns.empty())
                raspuns.pop_back();
            cer1(1);
            lastlit=1;
        }
        else if(cuv=="2")
        {
            cin>>cuv;
            s=cuv;
            baga(-1,1,++nrcuv);
            lastlit=2;
        }
        else if(cuv=="3")
        {
            cin>>cuv;
            stergere(1,0);
            lastlit=3;
        }
        else if(cuv=="4")
        {
            lastlit=4;

        }
        string last;
        while(lastlit==4 && cin>>cuv)
        {
            if(cuv=="0")
            {
                ofstream fi ("perechi.txt");
                ///  cout<<"YES\n";
                fi<<0<<"\n";
                for(auto x:m)
                {
                    ///  cout<<x.first.a<<" "<<x.first.b<<"\n";
                    if(x.second!=0 && x.first.a.size()!=0 && x.first.b.size()!=0)
                        fi<<x.first.a<<" "<<x.first.b<<" "<<x.second<<"\n";
                }

                return 0;
            }

            ind=0;
            cuv=cuv+cuv[cuv.size()-1];
            for(int i=cuv.size(); i>0; --i)
                cuv[i]=cuv[i-1];

            minim=999999999;
            ind=0;
            DFS(1, 1);

            raspuns.clear();
            int maxim=-1;
            int indaf=-1;
            string ajutor;
            for(int x=0; x<variante.size(); ++x)
            {
                ind=variante[x];
                cafiseaza(1);
                per A;
                A.a=last;
                A.b=ras;
                per A1;
                A1.a=ras;
                A1.b=last;
                cout<<ind<<" "<<m[A]<<"\n";
                if(maxim<m[A] || maxim<m[A1])
                {
                    maxim=max(m[A], m[A1]);
                    indaf=ind;
                    ajutor=raspuns;

                }
                raspuns.clear();
                ras.clear();
            }
            ind=indaf;
            afiseaza(1);
            ajutor.clear();
            ind=indaf;
            raspuns.clear();
            ///afiseaza(1);
            raspuns.clear();
             cout<<"\n";
           /// cout<<maxim<<" "<<ind<<"\n";
            cout<<ras<<" "<<minim<<" "<<maxim<<" "<<indaf<<"\n";


            if(ord!=0)
            {
                per x;
                x.a=cuvant;
                x.b=ras;
                m[x]++;
                /// cout<<x.a<<" "<<x.b<<"\n";

            }
            last=ras;
            cuvant=ras;
            ras.erase();
            raspuns.erase();
            ++ord;
        }


    }
    return 0;
}
