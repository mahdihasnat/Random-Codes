#include <bits/stdc++.h>
using namespace std;
#define input freopen("input.txt","r",stdin)
struct TrieNode
{
    string s;
    TrieNode * next[128];
    TrieNode()
    {
        s="";
        for(int i=0;i<128;i++)
            next[i]=nullptr;
    }
};
void AddTrieNode(TrieNode * head,string &macro,int i,string &s)
{
    if(i==macro.size())
    {
        head->s=s;
    }
    else if(head->next[macro[i]])
    {
        AddTrieNode(head->next[macro[i]],macro,i+1,s);
    }
    else
    {
        head->next[macro[i]]=new TrieNode();
        AddTrieNode(head->next[macro[i]],macro,i+1,s);
    }
}
int NotParameterized(string &s)
{
    for(int i=0;i<s.size();i++)
        if(s[i]=='(') return 0;
    return 1;
}
TrieNode * GetDefine(string &src)
{
    TrieNode * head= new TrieNode();
    stringstream ssrc(src);
    string tmp1,tmp2;
    while(ssrc>>tmp1)
    {
        if(tmp1=="#define")
        {
            ssrc>>tmp1;
            getline(ssrc,tmp2);
            cout<<"#ref="<<tmp1<<"#def="<<tmp2<<endl;
            if(NotParameterized(tmp1)) {
                AddTrieNode(head,tmp1,0,tmp2);
                cout<<" added = "<<tmp2<<endl;
            }
        }
    }
    return head;
}
string NULLstr = "";
string & GetReferance(TrieNode * head,string &macro,int i )
{
    //cout<<" i = "<<i<<" s[i] = "<<macro[i]<<" head= "<<head<<endl;
    if(head)
    {
        if(i==macro.size()) return head->s;
        else return GetReferance(head->next[macro[i]],macro,i+1);
    }
    else return NULLstr;
}
int GetTokenLastIndex(string &src,int index)
{
    while(index<src.size() && src[index]!=' '&&src[index]!='\n') index++;
    return index;
}
int GetTokenLastIndexLine(string &src,int index)
{
    while(index<src.size() &&src[index]!='\n') index++;
    return index;
}
string GetToken(string &src,int &index,int &startindex,int &stopindex)
{
    if(index>=src.size()) return "";
    while(index<src.size()&&(src[index]==' '||src[index]=='\n')) index++;
    startindex=index;

    stopindex=GetTokenLastIndex(src,index);
    if(stopindex>=src.size()) stopindex--;
    string token=src.substr(index,stopindex-startindex);
    index=stopindex;
    return token;
}
string GetTokenLine(string &src,int &index,int &startindex,int &stopindex)
{
    if(index>=src.size()) return "";
    while(index<src.size()&&src[index]==' ') index++;

    startindex=index;
    stopindex=GetTokenLastIndexLine(src,index);
    string token=src.substr(index,stopindex-index);
    index=stopindex;
    return token;

}
void NormalizeProgramme(string &src)
{
    int index=0,startindex=0,stopindex=0;
    TrieNode * head = new TrieNode();
    string token;
    do
    {
        //cout<<" age index = "<<index<<" si = #"<<src[index]<<"#"<<endl;
        token = GetToken(src,index,startindex,stopindex);
        //cout<<"token =#"<<token<<"#"<<endl;
        //cout<<" pore index ="<<index<<" si = #"<<src[index]<<"#"<<endl;

        //cout<<" index = "<<index<<endl;
        if(token=="#define")
        {
            string tmp1=GetToken(src,index,startindex,stopindex);
            string tmp2=GetTokenLine(src,index,startindex,stopindex);
            //cout<<" defined = "<<tmp1<<endl;
            //cout<<"tmp1 = "<<tmp1<<" tmp2 = "<<tmp2<<endl;
            AddTrieNode(head,tmp1,0,tmp2);
            //cout<<" si= "<<src[index];
        }
        else
        {
            //cout<<" pore index ="<<index<<" si = #"<<src[index]<<"#"<<endl;
            //cout<<" hoi  ";
            string rep;
            rep=GetReferance(head,token,0);
            //cout<<"token = "<<token<<" ref = "<<rep<<endl;
            if(rep!="")
            {
                //cout<<" rep = "<<rep<<endl;
                src.replace(startindex,stopindex-startindex,rep);
                index+=rep.size()-stopindex+startindex ;
            }
        }
    }
    while(token!="") ;
    cout<<src<<endl;

}
int main()
{

    input;
    string s;
    char buff[10000];
    int k;
    while(k=getchar())
    {
        //cout<<(char )k;
        s.push_back((char )k);
        if(k==EOF) break;
    }

    NormalizeProgramme(s);


}
