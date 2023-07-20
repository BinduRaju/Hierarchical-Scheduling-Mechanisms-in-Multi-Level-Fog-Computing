#include <bits/stdc++.h>
#include<iostream>
using namespace std;
class Component;
class Edge;
class Cloudlet
{
    public:
    vector<Component>Compo;
};
class Component{
    public:
    int id;
    Component(int n)
    {
        id=n;
    }
};
inline bool operator<(const Component& lhs, const Component& rhs)
{
  return lhs.id < rhs.id;
}
struct MyClassComparator {
    bool operator()(const set<Component>& a, const set<Component>& b)  {
        auto itA = a.begin(), itB = b.begin();
        while (itA != a.end() && itB != b.end()) {
            if (itA->id < itB->id) {
                return true;
            } else if (itB->id < itA->id) {
                return false;
            }
            itA++; itB++;
        }
        return itA == a.end() && itB != b.end();
    }
    };
class Edge {
    public:
    int dt;
    char ind;
    float sel;
    float period;
    Edge()
    {
        dt=0;
        ind='X';
        sel=0;
        period=10;
    }
    void CreateEdge(int d,char w,float s,float p)
    {
        dt=d;
        ind=w;
        sel=s;
        period=p;
    }
};
class GraphMatrix
{
    public:
    int compcount;
    GraphMatrix(int v)
    {
        compcount=v;
    }
    Edge** adj;
    void creatgraph()
    {
        adj=new Edge*[compcount];
        for(int i=0;i<compcount;i++)
        {
            adj[i]=new Edge[compcount];
            for(int j=0;j<compcount;j++)
            {
                Edge e1;
                adj[i][j]=e1;
            }
        }
    }
    void AddEdge(Component &u,Component &v,int d,char w,float s,float p=10)
    {
        Edge e;
        e.CreateEdge(d,w,s,p);
        adj[u.id-1][v.id-1]=e;
    }
    ~GraphMatrix()
    {
        for(int i=0;i<compcount;i++)
        {
            delete []adj[i];
        }
        delete []adj;
    }
};


//--------------------------------------------------Algo-2----------------------------------------------------------------

set<set<Component>,MyClassComparator> computeComponentSets(Cloudlet c,GraphMatrix g) 
{
    set<set<Component>,MyClassComparator> S;
    for (int i = 0; i < c.Compo.size(); i++)
    {
        int f = 0;
        for (int j = 0; j < c.Compo.size(); j++) 
        {
            if (g.adj[c.Compo[i].id-1][c.Compo[j].id-1].ind == 'U')
            {
                f = 1;
                break;
            }
        }
        if (f == 0) 
        {
            std::set<Component> M={c.Compo[i]};
            S.insert(M);
        }
    }
    std::set<set<Component>, MyClassComparator> tempSet;
    for (std::set<Component> Ms : S) 
    {
        for (Component ms : Ms) 
        {
            for (int i=0;i<c.Compo.size();i++) 
            {
                if(g.adj[c.Compo[i].id-1][ms.id-1].ind=='U')
                {
                    std::set<Component> Mme = Ms;
                    Mme.insert(c.Compo[i]); 
                    tempSet.insert(Mme);
                }
            }
        }
    }
    S.insert(tempSet.begin(), tempSet.end());
    return S;
} 


//------------------------------------Algo-3------------------------------------------------------------------------

double computeImpact(GraphMatrix &g,set<Component>M,Cloudlet h)
{
    double Imp=0;
    for(Component c:M)
    {
        for(int i=0;i<g.compcount;i++)
        {
            if(g.adj[c.id-1][i].ind!='X')
            {
                double k=(g.adj[c.id-1][i].dt*g.adj[c.id-1][i].sel*10)/g.adj[c.id-1][i].period;
                int flag1=0;
                int flag2=0;
                for(Component sa:M)
                {
                    if(sa.id==i+1)
                    {
                        flag1=1;
                        break;
                    }
                }
                for(int j=0;j<h.Compo.size();j++)
                {
                    if(i+1==h.Compo[j].id)
                    {
                        flag2=1;
                        break;
                    }
                }
                if(flag1==0)
                {
                    if(flag2==1)
                    {
                         Imp=Imp-k;
                    }
                    else
                    {
                         Imp=Imp+k;
                    }
                }
            }
        }
        for(int i=0;i<g.compcount;i++)
        {
            if(g.adj[i][c.id-1].ind!='X')
            {
                double k=(g.adj[i][c.id-1].dt*g.adj[i][c.id-1].sel*10)/g.adj[i][c.id-1].period;
                int flag1=0;
                int flag2=0;
                for(Component sa:M)
                {
                    if(sa.id==i+1)
                    {
                        flag1=1;
                        break;
                    }
                }
                for(int j=0;j<h.Compo.size();j++)
                {
                    if(i+1==h.Compo[j].id)
                    {
                        flag2=1;
                        break;
                    }
                }
                if(flag1==0)
                {
                    if(flag2==1)
                    {
                         Imp=Imp-k;
                    }
                    else
                    {
                         Imp=Imp+k;
                    }
                }
            }
        }
    }
    cout<<Imp<<endl;
    return Imp;
}


//--------------------------------------Algo-1--------------------------------------------------------------

set<Component> communicationEdgeward(GraphMatrix &g,set<set<Component>,MyClassComparator> &S,Cloudlet h)
{
    double min_cost=INT_MAX;
    set<Component> mins;
    cout<<"Their respective impacts are as follows:"<<endl;
    for(set<Component> c:S)
    {
        double costc=computeImpact(g,c,h);
        if(costc<min_cost)
        {
            min_cost=costc;
            mins=c;
        }
    }
    return mins;
}

/////////////////MAIN FUNTION////////////////////////////////
int main()
{
    GraphMatrix g(4);
    g.creatgraph();
    Cloudlet device;
    Cloudlet fog;
    Cloudlet Cloud;
    Component m1(1);
    Component m2(2);
    Component m3(3);
    Component m4(4);
    device.Compo.push_back(m1);
    fog.Compo.push_back(m2);
    fog.Compo.push_back(m3);
    Cloud.Compo.push_back(m4);
    g.AddEdge(m1,m2,500,'U',1.0,10);
    g.AddEdge(m2,m3,450,'U',1.0,10);
    g.AddEdge(m3,m1,200,'D',1.0,50);
    g.AddEdge(m3,m4,500,'U',0.50,10);
    g.AddEdge(m4,m3,200,'D',1.0,10);
    set<set<Component>,MyClassComparator> S=computeComponentSets(fog,g);
    cout<<"The possible sets that can be sent to higher cloudlets are"<<endl;
    for (std::set<Component> Ms : S)
    {
        cout<<'{';
        for (Component ms : Ms) 
        {
            cout<<'m'<<ms.id<<" ";
        }
        cout<<'}'<<endl;
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<g.adj[i][j].ind<<" ";
        }
        cout<<endl;
    }
    std::set<Component>Moveup=communicationEdgeward(g,S,Cloud);
    cout<<"The component set that can be move to higher layer is"<<endl;
    for(Component c:Moveup)
    {
        cout<<'m'<<c.id<<" ";
    }
    return 0;
}

