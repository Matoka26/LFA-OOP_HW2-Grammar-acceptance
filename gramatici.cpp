#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class IOinterface{
public:
    virtual istream& citire(istream&) = 0;
};

class Gramatica: public IOinterface{
private:
    map<char,vector<string>>dic;
public:
    virtual istream& citire(istream& in){
        char cheie;
        string aux;
        int index;
        while(!in.eof()){
            in>>cheie;
            in>>index;
            for(int i = 0 ; i < index ; i++){
                in>>aux;
                this->dic[cheie].push_back(aux);
            }
        }
    }

    string getElementDic(char cheie,int index){
        return (this->dic[cheie][index]);
    }

    bool inVector(string tranzitie,vector<string> vec){
        bool check = 0;
        for(int i = 0 ; i < vec.size() ; i++)
            if(vec[i][0] == tranzitie[0])
                check = 1;
        return check;
    }

    bool acceptare(char stare,string cuvant){
        if(cuvant == ""){
            return inVector("-",this->dic[stare]);
        }
        if(cuvant.length() == 1)
            for(int i = 0 ; i < this->dic[stare].size() ; i++)
                if(this->dic[stare][i][0] == cuvant[0] && this->dic[stare][i].length() == 1)
                    return 1;

        for(int i = 0 ; i < this->dic[stare].size() ; i++)
            if(this->dic[stare][i].length() > 1 && this->dic[stare][i][0] == cuvant[0])
                if(acceptare(this->dic[stare][i][1] , cuvant.substr(1)))
                    return 1;
    }
};

class Cuvinte:public IOinterface{
private:
    vector<string>cuvinte;
public:
    virtual istream& citire(istream& in){
        string aux;
        while(!in.eof()){
            in>>aux;
            this->cuvinte.push_back(aux);
        }
    }

    vector<string> getVector() const{
        return this->cuvinte;
    }
    int getIndex() const{
        return this->cuvinte.size();
    }

    string operator[](int index){
        return this->cuvinte[index];
    }

};

class Meniu{
private:
    Gramatica graf;
    Cuvinte listaCuvinte;
public:
    void start(istream& gramatica , istream& cuvinte){
        this->graf.citire(gramatica);
        this->listaCuvinte.citire(cuvinte);
        cout<<"Cuvinte:\n---------\n";
        for(int i = 0 ; i < this->listaCuvinte.getIndex() ; i ++){
            if(this->graf.acceptare('S',this->listaCuvinte[i]))
                cout<<(this->listaCuvinte.getVector())[i]<<"->acceptat\n";
            else
                cout<<(this->listaCuvinte.getVector())[i]<<"->respins\n";
        }
    }

};

int main(){
ifstream gramatica("gramatica.txt");
ifstream cuvinte("cuvinte.txt");
Meniu meniu;

meniu.start(gramatica,cuvinte);

gramatica.close();
cuvinte.close();
return 0;
}
