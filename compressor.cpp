///****In the name of Allah, most Gracious, most Compassionate****//

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

#define NL cerr<<"\n";
#define ALL(a) a.begin(), a.end()
#define DBG(a) cerr<< #a <<" --> "<<(a)<<endl;
#define FastIO ios::sync_with_stdio(false); cin.tie(0);cout.tie(0)
#define IN freopen("input.txt","r+",stdin)
#define OUT freopen("output.cpp","w+",stdout)

template < class T1,class T2>
ostream &operator <<(ostream &os,const pair < T1,T2 > &p)
{
    os<<"{"<<p.first<<","<<p.second<<"}";
    return os;
}

const int N=3e5+5;
const int oo=1e9+7;

void RemoveLineComment(char *s,int n, char *dest)
{
    bool inLine=false;
    for(int i=0; i<n; i++)
    {
        if(inLine and s[i+1]=='\n')
        {
            inLine = false;
            continue;
        }
        if(inLine)
            continue;
        if(s[i]=='/' and s[i+1]=='/')
        {
            i++;
            inLine = 1;
            continue;
        }
        *dest= s[i];
        dest++;
    }
    *dest = 0;
}
void RemoveBlockComment(char *s,int n, char *dest)
{
    bool inblock=false;
    for(int i=0; i<n; i++)
    {
        if(inblock and s[i]=='*' and s[i+1]=='/')
        {
            i++;
            inblock = false;
            continue;
        }
        if(inblock)
            continue;
        if(s[i]=='/' and s[i+1]=='*')
        {
            i++;
            inblock = 1;
            continue;
        }
        *dest= s[i];
        dest++;
    }
    *dest = 0;
}

void RemoveBlankLine(char *s,int n, char *dest)
{
    bool linestart=false;
    for(int i=0; i<n; i++)
    {
        if(s[i]=='\n')
        {
            if(linestart)
            {
                *dest='\n';
                dest++;
            }
            linestart= false;

            continue;
        }
        if(linestart or s[i]!=' ')
        {
            linestart = true;
            *dest=s[i];
            dest++;
        }
    }
    *dest=0;
}
void RemoveSpaceAndNewLineAroundCharacter(char *s,int n, char *dest,const char ch)
{
    int j=0;
    bool inString=false;
    bool inMacro=false;
    char last =0;
    for(int i=0; i<n; i++)
    {

        if(s[i]=='"' and last!= '\\')
        {
            inString= !inString;
        }
        last=s[i];
        if(inString)
        {
            *(dest+j) = s[i];
            j++;
            continue;
        }
        if(s[i]=='\n')
        {
            inMacro=false;
        }
        if(s[i]=='#' and (s[i+1]=='d' or s[i+1]=='i'))
        {
            inMacro=true;
        }
        if(inMacro)
        {

            *(dest+j) = s[i];
            j++;
        }
        else if(s[i]==ch)
        {
            j--;
            while(j>0 and (s[j]==' '))
                j--;
            j++;
            *(dest+j) = s[i];
            j++;
            i++;
            while(i<n and (s[i]==' ' or (s[i]=='\n' and s[i+1]!='#') ))
                i++;
            i--;

        }
        else
        {
            *(dest+j) = s[i];
            j++;
        }

    }
    *(dest+j) = 0;
}

bool isIdentifierChar(const char &c)
{
    if(c>='a' and c<='z')
        return true;
    if(c>='A' and c<='Z')
        return true;
    if(c>='0' and c<='9')
        return true;
    if(c=='_' or c=='$' )
        return true;
    return false;
}
string getkey(const string &ss, int start)
{
    string ret ="";
    while(start<ss.size())
    {
        if (ss[start] != ' '  and ss[start]!='\n')
            ret+=ss[start++];
        else
            break;
    }
    return ret;
}
string getValue(const string &ss, int start)
{
    string ret ="";
    while(start<ss.size())
    {
        if (ss[start] != '\n' )
            ret+=ss[start++];
        else
            break;
    }
    return ret;
}
bool isParameterizedIdentifier(const string &s)
{
    for(const char c: s)
    {
        if(c=='(' )
            return true;
    }
    return false;
}
void Replace(string &ss,int start, string const & key, string const &value)
{
    size_t pos=start;
    while((pos= ss.find(key,pos))!=string::npos)
    {
        ss.replace(pos, key.size(), value);
        pos++;
    }
}

string getv(map<string, string > &change, map<string, bool > &visited, string u)
{
    if(visited[u])
        return getv(change, visited, change[u]);
    else
        return u;
}
void ParseMacroIdentifier(char *s, int n,char *dest)
{
    /*
        pre process broken line's
        remove space's, remove new line's
    */
    string source(s);
    map<string, string > change;
    map<string, bool > visited;
    bool inString=false;
    int last=0;
    for(int i=0; i<source.size(); i++)
    {

        if(source[i]=='#'
                and source[i+1]=='d'
                and source[i+2] == 'e'
                and source[i+3] == 'f'
                and source[i+4] == 'i'
                and source[i+5] == 'n'
                and source[i+6] == 'e' )
        {
            for(i = i+7; source[i]==' ' ; i++ ) ;
            string key =getkey(source,i);
            i+=key.size(); /// i is now pointing sapce or newline
            DBG(key);
            if(isParameterizedIdentifier(key))
            {
                for(; source[i]!='\n'; i++) ;
            }
            else
            {
                string value;
                if(source[i]!=' ')
                {
                    value="";
                }
                else
                {
                    i++; /// start value
                    value = getValue(source,i);
                }
                DBG(value);
                change[key]=value;
                visited[key]=1;
                i+=value.size(); /// i is now pointing sapce or newline
                for(; source[i]!='\n'; i++);
            }
        }
        else if( source[i]=='#'
                 and source[i+1]=='u'
                 and source[i+2]=='n'
                 and source[i+3] == 'd'
                 and source[i+4]=='e'
                 and source[i+5]== 'f')
        {
            for(i = i+6; source[i]==' ' ; i++ ) ;
            string key =getkey(source,i);
            i+=key.size(); /// i is now pointing sapce or newline
            assert(!isParameterizedIdentifier(key));
            {
                for(; source[i]!='\n'; i++) ;
            }
            if(visited[key])
            {
                visited[key]=0;
                change[key]="";
            }
        }
        if(source[i]=='"' and last!= '\\')
        {
            inString= !inString;
        }
        last = source[i];
        if(inString)
            continue;
        if(isIdentifierChar(source[i]))
        {
            assert(isIdentifierChar(source[i])==1);
            string key = "";
            int j=i;
            for(; isIdentifierChar(source[j]) and j<source.size(); j++)
                key+=source[j];
            cerr<<"found\n";
            DBG(key);
            DBG(visited[key]);
            if(visited[key])
            {
                string value= getv(change, visited, key);
                DBG(value);
                source.replace(i,key.size(), value);
                i+=value.size();
                i--;
            }
            else
            {
                i=j;
                i--;
            }
        }
    }
    NL;
    cerr<<source<<endl;
    for(char c: source)
    {
        *(dest++)= c;
    }
    *dest=0;
}
void PreProcessBrokenLine(char *s,int n,char *dest)
{
    for(int i=0; i<n; i++)
    {
        if(s[i]=='\\' and s[i+1] == '\n' )
        {
            i++;
        }
        else
        {
            *dest = s[i];
            dest++;
        }
    }
    *dest=0;
}
void compress(char *s,int n, char *dest)
{
    PreProcessBrokenLine(s,n,dest);
    RemoveBlockComment(dest,strlen(dest),dest);
    RemoveLineComment(dest,strlen(dest),dest);
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,' ');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,',');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,'(');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,')');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,'{');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,'}');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,';');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,'<');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,'>');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,'+');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,'-');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,'*');
    RemoveSpaceAndNewLineAroundCharacter(dest,strlen(dest),dest,'/');
    RemoveBlankLine(dest,strlen(dest),dest);
    ParseMacroIdentifier(dest,strlen(dest),dest);
}
char *readFile(const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL)
        return NULL; //could not open file
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code =(char * ) malloc(f_size);

    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char)c;
    }

    code[n] = '\0';

    return code;
}
int32_t main()
{
    OUT;
    char * s =readFile("lightoj.cpp");
    if(s)
    {
        int n =strlen(s);
        char *d = new char[n+5];
        compress(s,n,d);
        while(*d)
        {
            cout<<*d;
            d++;
        }
    }
    else
    {
        cout<<"File open error\n";
    }
}






