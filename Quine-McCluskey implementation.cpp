//Code by:Anshul Negi
//2019EEB1145


#include<bits/stdc++.h>
#include<fstream>
#include <cstdlib>

using namespace std;


string getString(char x) 
{ 
     
    string s(1, x); 
  
    return s;    
}

string decToBinary(int n,int base) 
{ 
    string binaryNum;  
    int i = 0; 
    while (n > 0) { 
        binaryNum=((n%2)?"1":"0") + binaryNum; 
        n = n/2; 
        i++; 
    } 
    while (i<base)
    {           binaryNum="0" + binaryNum; 
              i++;
    }
    
  return binaryNum;
}

int num_ones(string v)
  {
      int count=0;
      for(int i=0;i<v.length();i++)
        {if(v[i]=='1')
         count++;
        }

      return count;  
  }

pair<int,int> get_diff(string x,string y)
    {
        int count=0,pos=0;
        for(int i=0;i<x.length();i++)
           { if(x[i]=='_' && y[i]!='_')
                {
                    count+=2;
                }
            else if(y[i]=='_' && x[i]!='_')
              count+=2;
             else if(x[i]!=y[i])
                  {count++;
                    pos=i;
                  }
           }
          return make_pair(count,pos);
        
    }

int further_loop(vector<vector<string>> table)
          {
              for(int i=0;i<table.size();i++)
                  {
                      if(table[i].size())
                          return 1;
                  }
                return 0;
          }

int compare(string x,string y)
    {
        for(int i=0;i<x.length();i++)
          {
              if(x[i]!='_')
                {
                    if(x[i]!=y[i])
                       return 0;
                }
          }
        return 1;
    }

void equiv_var(string s)
     {
         for(int i=0;i<s.size();i++)
            {
                if(s[i]!='_')
                   {
                       if(s[i]=='1')
                          {
                              cout<<getString(char('A'+i));
                          }
                       else
                       {
                           cout<<getString(char('A'+i));
                           cout<<"'";
                       }
                       
                   } 
            }
            cout<<"  ";
     }

class McQ
{
 private:
     int base,init_var;
     vector<int> minT_init;
     vector<vector<string>> table;
     set<string> pi;

     vector<string> prime_implicants;
     set<string> essential_pi;
 
 public:
     void initialise()
        {
            cout<<"Enter the number of variables\n";
            cin>>base;
            cout<<"Enter the number of minterms\n";
            cin>>init_var;
            table.resize(base+1);
            for(int i=0;i<init_var;i++)
              {
                  cout<<"Enter the minterm\n";
                  int n;
                  cin>>n;
                  minT_init.push_back(n);
                  string s=decToBinary(minT_init[i],base);
                  int no1=num_ones(s);

                  table[no1].push_back(s);
              }
                     

                  while(1)
                     {   vector<vector<string>> temp_table=transformation();
                        if(!further_loop(temp_table))
                          break;
                         table=temp_table;
                         
                         
                         
             
                     }  
                for(auto c:pi)
                  {
                    prime_implicants.push_back(c);
                  }         

                map<int,vector<string>> pi_table;
                for(int i=0;i<prime_implicants.size();i++)
                   {
                       for(int j=0;j<minT_init.size();j++)
                         {
                           string s=decToBinary(minT_init[j],base);  
                           if(compare(prime_implicants[i],s))
                                pi_table[minT_init[j]].push_back(prime_implicants[i]);                         
                         }
                   }
                for(auto c:pi_table)
                  {
                      if(c.second.size()==1)
                          essential_pi.insert(c.second[0]);
                  }

                 cout<<"The prime implicants are : ";
               for(int i=0;i<prime_implicants.size();i++)
                   {
                       equiv_var(prime_implicants[i]);
                   }
                  cout<<endl;
            cout<<"The essential prime implicants are : ";
               for(auto c:essential_pi)
                   {
                       equiv_var(c);
                   }
                cout<<endl;
            
        }
     vector<vector<string>> transformation()
       {
           int check[table.size()][init_var]={0};
                vector<vector<string>> temp_table(table.size()-1);
           for(int i=0;i<table.size()-1;i++)
              {
                  for(int j=0;j<table[i].size();j++)
                        {
                            for(int k=0;k<table[i+1].size();k++)
                                {
                                    if(get_diff(table[i][j],table[i+1][k]).first==1)
                                       {
                                           check[i][j]=1;
                                           check[i+1][k]=1;
                                           string s=table[i][j];
                                           int x=get_diff(table[i][j],table[i+1][k]).second;
                                             s[x]='_';
                                            temp_table[i].push_back(s);
                                       }
                                         
                                }
                        }
              }
            for(int i=0;i<table.size();i++)
              {
                  for(int j=0;j<table[i].size();j++)
                    {
                        if(!check[i][j])
                          pi.insert(table[i][j]);
                    }
              }
            return temp_table;
       }

    void print_table()
       {
           for(int i=0;i<table.size();i++)
              {
                  cout<<i<<"\n"<<endl;
                  for(int j=0;j<table[i].size();j++)
                     cout<<table[i][j]<<endl;

                    cout<<endl;
              }
              
       }
};


int main()
  {

      McQ  tab;
      tab.initialise();
  
      return 0;

  }



