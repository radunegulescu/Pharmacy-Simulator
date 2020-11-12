#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <stdlib.h>
using namespace std;
vector <int> ProfitDefault(){
    vector <int> aux(12);
    for(int i=0;i<12;i++){
        aux[i]=0;
    }
    return aux;
}
class Farmacii{
public:
    virtual ~Farmacii(){};
    virtual void citire(istream &in) = 0;
    virtual void afisare(ostream &out) = 0;
    friend istream& operator >> (istream&, Farmacii&);
    friend ostream& operator << (ostream&, Farmacii&);
};
istream& operator>> (istream& in, Farmacii& x){
    x.citire(in);
    return in;
}
ostream& operator<< (ostream& out, Farmacii& x){
    x.afisare(out);
    return out;
}
class Farmacie: public Farmacii{
private:
    string denumire;
    int nr_ang;
    vector <int> profituri;
public:
    Farmacie(string, int, vector<int>);
    Farmacie(const Farmacie&);
    Farmacie &operator=(const Farmacie&);
    ~Farmacie();
    void citire(istream &);
    void afisare(ostream &);
    string get_denumire() const;
    void set_denumire(string);
    int get_nr_ang() const;
    void set_nr_ang(int);
    vector <int> get_profituri() const;
    void set_profituri(vector <int>);
    friend istream& operator>>(istream &, Farmacie&);
    friend ostream& operator<<(ostream &, Farmacie&);
};

Farmacie::Farmacie(string den="", int nr=0, vector<int> prof=ProfitDefault()):denumire(den),nr_ang(nr){
    try{int a=0;
        if(prof.size()!=12){
            profituri=ProfitDefault();
            throw a;
        }
        else{
            profituri=prof;
        }
    }
    catch (int){
        cout<<"\nnr profituri incorect\n";
    }
}
Farmacie::Farmacie(const Farmacie&F):denumire(F.denumire),nr_ang(F.nr_ang),profituri(F.profituri){
}
Farmacie &Farmacie::operator=(const Farmacie&F){
    if(this!=&F){
        denumire=F.denumire;
        nr_ang=F.nr_ang;
        profituri=F.profituri;
    }
    return *this;
}
Farmacie::~Farmacie(){
    nr_ang=0;
    denumire="";
    profituri.clear();
}
void Farmacie::citire(istream &in){
    cout<<"\nFarmacie: ";
    cout<<"\ndenumire farmacie = ";
    getline(in,denumire);
    if(denumire=="")
       getline(in,denumire);
    cout<<"\nnumar angajati = ";
    in>>nr_ang;
    cout<<"\nprofituri = ";
    for(int i=0;i<12;i++){
        cout<<"\n luna "<<i+1<<" = ";
        in>>profituri[i];
    }
}
void Farmacie::afisare(ostream &out){
    out<<"\nFarmacie: ";
    out<<"\ndenumire farmacie = "<<denumire;
    out<<"\nnumar angajati = "<<nr_ang;
    out<<"\nprofituri = ";
    for(int i=0;i<12;i++){
        out<<"\n luna "<<i+1<<" = ";
        out<<profituri[i];
    }
}
istream& operator>>(istream &in, Farmacie& F){
    F.citire(in);
    return in;
}
ostream& operator<<(ostream &out, Farmacie &F){
    F.afisare(out);
    return out;
}
string Farmacie::get_denumire() const{
    return denumire;
}
void Farmacie::set_denumire(string den){
    denumire=den;
}
int Farmacie::get_nr_ang() const{
    return nr_ang;
}
void Farmacie::set_nr_ang(int nr){
    nr_ang=nr;
}
vector <int> Farmacie::get_profituri() const{
    return profituri;
}
void Farmacie::set_profituri(vector <int> prof){
        prof=profituri;
}

class FarmacieOnline: public Farmacii{
private:
    tuple<string, int, int> info;
public:
    FarmacieOnline(string, int, int);
    FarmacieOnline(const FarmacieOnline&);
    FarmacieOnline &operator=(const FarmacieOnline&);
    ~FarmacieOnline(){};
    void citire(istream &);
    void afisare(ostream &);
    friend istream& operator>>(istream &, Farmacie&);
    friend ostream& operator<<(ostream &, Farmacie&);
    ///web, nr_vizitatori, discount
    string get_web() const;
    void set_web(string);
    int get_nr_vizitatori() const;
    void set_nr_vizitatori(int);
    int get_discount() const;
    void set_discount(int);
};
FarmacieOnline::FarmacieOnline(string web="", int nr_vizitatori=0, int discount=0){
    info=make_tuple(web,nr_vizitatori,discount);
}
FarmacieOnline::FarmacieOnline(const FarmacieOnline&F){
    info=F.info;
}
FarmacieOnline &FarmacieOnline::operator=(const FarmacieOnline&F){
    if(this!=&F){
        info=F.info;
    }
    return *this;
}
void FarmacieOnline::citire(istream &in){
    cout<<"\nFarmacie online: \n";
    cout<<"adresa web = ";
    getline(in,get<0>(info));
    if(get<0>(info)=="")
       getline(in,get<0>(info));
    cout<<"\nnumar vizitatori = ";
    in>>get<1>(info);
    cout<<"\ndiscount = ";
    in>>get<2>(info);
}
void FarmacieOnline::afisare(ostream &out){
    out<<"\nFarmacie online: \n";
    out<<"adresa web = ";
    out<<get<0>(info);
    out<<"\nnumar vizitatori = ";
    out<<get<1>(info);
    out<<"\ndiscount = ";
    out<<get<2>(info);
}
istream& operator>>(istream &in, FarmacieOnline &F){
    F.citire(in);
    return in;
}
ostream& operator<<(ostream &out, FarmacieOnline &F){
    F.afisare(out);
    return out;
}
string FarmacieOnline::get_web() const{
    return get<0>(info);
}
void FarmacieOnline::set_web(string web){
    get<0>(info)=web;
}
int FarmacieOnline::get_nr_vizitatori() const{
    return get<1>(info);
}
void FarmacieOnline::set_nr_vizitatori(int nr_vizitatori){
    get<1>(info)=nr_vizitatori;
}
int FarmacieOnline::get_discount() const{
    return get<2>(info);
}
void FarmacieOnline::set_discount(int discount){
    get<2>(info)=discount;
}

template <class t> class GestionareFarmacii{
private:
    static int index_max;
    vector <int> index;
    const int id_lant;
    vector <t> v;
public:
    GestionareFarmacii(vector <t> a={}):id_lant(index_max){
        for(unsigned i=0;i<a.size();i++){
            v.push_back(a[i]);
            ++index_max;
            index.push_back(index_max);
        }
    }
    GestionareFarmacii(const GestionareFarmacii&G):id_lant(index_max){
        for(unsigned i=0;i<G.v.size();i++){
            v.push_back(G.v[i]);
            ++index_max;
            index.push_back(index_max);
        }
    }
    ~GestionareFarmacii(){
        index_max=index_max-v.size();
        v.clear();
        index.clear();
    }
    GestionareFarmacii& operator=(const GestionareFarmacii&G){
       if(this!=&G){
        v=G.v;
        index=G.index;
       }
       return *this;
    }
    const int get_id_lant() const{
        return id_lant;
    }
    static int get_index_max() {
        return index_max;
    }
    void add(const t&F){
        v.push_back(F);
        ++index_max;
        index.push_back(index_max);
    }
    t getelement(int i){
        return v[i];
    }
    void citire(istream &in){
        cout<<"\nnumar farmacii = ";
        int n;
        in>>n;
        for(int i=0;i<n;i++){
            cout<<"\nFarmacia "<<i+1<<": ";
            t F;
            in>>F;
            v.push_back(F);
            ++index_max;
            index.push_back(index_max);
        }
    }
    void afisare(ostream &out){
        out<<"\nGestionare Farmacii: \n";
        out<<"Index_max = "<<index_max;
        out<<"\nId_lant = "<<id_lant;
        out<<"\n";
        for(unsigned i=0;i<v.size();i++){
            out<<"\nindex "<<index[i]<<":";
            out<<v[i];
        }
    }
    friend istream& operator>>(istream &in, GestionareFarmacii<t>&G){
        G.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream &out, GestionareFarmacii<t>&G){
        G.afisare(out);
        return out;
    }
};
template <class t> int GestionareFarmacii<t>::index_max=0;

template <> class GestionareFarmacii <FarmacieOnline>{
private:
    static int index_max;
    vector <int> index;
    const int id_lant;
    vector <FarmacieOnline> v;
public:
    GestionareFarmacii(vector <FarmacieOnline> a={}):id_lant(index_max){
        for(unsigned i=0;i<a.size();i++){
            v.push_back(a[i]);
            ++index_max;
            index.push_back(index_max);
        }
    }
    GestionareFarmacii(const GestionareFarmacii<FarmacieOnline>&G):id_lant(index_max){
        for(unsigned i=0;i<G.v.size();i++){
            v.push_back(G.v[i]);
            ++index_max;
            index.push_back(index_max);
        }
    }
    ~GestionareFarmacii(){
        index_max=index_max-v.size();
        v.clear();
        index.clear();
    }
    GestionareFarmacii& operator=(const GestionareFarmacii<FarmacieOnline>&G){
        if(this!=&G){
            v=G.v;
            index=G.index;
        }
        return *this;
    }
    GestionareFarmacii& operator+=(const FarmacieOnline&F){
        v.push_back(F);
        ++index_max;
        index.push_back(index_max);
        return *this;
    }
    const int get_id_lant() const{
        return id_lant;
    }
    static int get_index_max() {
        return index_max;
    }
    void citire(istream &in){
        cout<<"\nnumar farmacii = ";
        int n;
        in>>n;
        for(int i=0;i<n;i++){
            cout<<"\nFarmacia "<<i<<": ";
            FarmacieOnline F;
            in>>F;
            v.push_back(F);
            ++index_max;
            index.push_back(index_max);
        }
    }
    void afisare(ostream &out){
        out<<"\nGestionare Farmacii Online: \n";
        out<<"Index_max = "<<index_max;
        out<<"\nId_lant = "<<id_lant;
        out<<"\n";
        int s=0;
        for(unsigned i=0;i<v.size();i++){
            s+=v[i].get_nr_vizitatori();
        }
        out<<"Numarul total de vizitatori ai farmaciilor online = "<<s<<"\n";
    }
    friend istream& operator>>(istream &in, GestionareFarmacii<FarmacieOnline>&G){
        G.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream &out, GestionareFarmacii<FarmacieOnline>&G){
        G.afisare(out);
        return out;
    }
};
template <> int GestionareFarmacii<FarmacieOnline>::index_max=0;
void tip(vector<Farmacii*> &v, int &i, GestionareFarmacii<Farmacie>&G1, GestionareFarmacii<FarmacieOnline>&G2) {
    Farmacii *p;
    string s;
    cout<<"\n";
    cout<<"Introduceti tipul Farmaciei "<<i+1<<": ";
    getline(cin,s);
    if(s==""){
        getline(cin,s);
    }
    try
    {
        if(s=="Farmacie")
        {
                p=new Farmacie;
                cin>>*p;
                v.push_back(p);
                Farmacie *q1=dynamic_cast<Farmacie*>(p);
                G1.add(*q1);
                i++;
        }
        else
            if(s=="Farmacie Online")
            {
                p=new FarmacieOnline;
                cin>>*p;
                v.push_back(p);
                FarmacieOnline *q2=dynamic_cast<FarmacieOnline*>(p);
                G2+=*q2;
                i++;
            }
            else
                throw 10;
    }
    catch (bad_alloc var)
    {
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j)
    {
        cout<<"Nu ati introdus un tip valid. Incercati Farmacie sau Farmacie Online.\n ";
    }
}
void Citire_si_Afisare_n_Farmacii(int n, vector<Farmacii*> &v, GestionareFarmacii<Farmacie>&G1, GestionareFarmacii<FarmacieOnline>&G2){
    try{
        if (n>0){
            for(int i=0;i<n;)
                tip(v,i,G1,G2);
            for(int i=0;i<v.size();i++){
                cout<<*(v[i]);
            }
        }
        else
            {throw "Numarul introdus trebuie sa fie pozitiv.\n";}
        }
    catch (const char *c){
            cout<<c;
    }
}
void menu_afis()
{
    cout<<"\nFARMACII\n";
    cout<<"\nMENIU:\n";
    cout<<"1. Citeste si afiseaza informatii despre n Farmacii si le adauga in Gestiune";
    cout<<"2. Adauga Farmacie Offline in Gestiune\n";
    cout<<"3. Adauga Farmacie Online in Gestiune\n";
    cout<<"4. Afiseaza Gestiune Farmacii Offline\n";
    cout<<"5. Afiseaza Gestiune Farmacii Online\n";
    cout<<"6. Sterge Farmaciile\n";

    cout<<"0. Iesire.\n";
}
void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;
    int n=0;
    GestionareFarmacii <Farmacie> G1;
    GestionareFarmacii <FarmacieOnline> G2;
    vector<Farmacii*> v;
    do
    {
        menu_afis();
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;
        if (option==1)
        {   cout<<"\nNumar Farmacii = ";
            cin>>n;
            Citire_si_Afisare_n_Farmacii(n,v,G1,G2);
        }
        if (option==2)
        {
            Farmacie F1;
            cin>>F1;
            G1.add(F1);
        }
        if (option==3)
        {
            FarmacieOnline F2;
            cin>>F2;
            G2+=F2;
        }
        if (option==4)
        {
            cout<<G1;
        }
        if (option==5)
        {
            cout<<G2;
        }
        if (option==6)
        {
            while(v.size()){
                v.erase(v.begin());
            }
        }
        if (option==0)
        {
            cout<<"\nEXIT\n\n";
        }
        if (option<0||option>6)
        {
            cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option!=0);
}
int main(){
    menu();
//    GestionareFarmacii<Farmacii*> G;
//    FarmacieOnline* F=new FarmacieOnline("www.dona.ro",2,3);
//    G.add(F);
//    cout<<*G.getelement(0);
//Farmacie F("Catena",12,{1,2,3,5,3,2,4,3,5,4,3,4});
//cout<<F;
//F.set_nr_ang(3);
//cout<<F;
//Farmacie G=F;
//G.set_nr_ang(5);
//cout<<G<<"\n\n\n\n";
//cout<<F;
//FarmacieOnline F2;
//F2.set_discount(20);
//F2.set_nr_vizitatori(50);
//F2.set_web("www.sensi_blue.ro");
//cout<<F2;
//Farmacii *F3=new FarmacieOnline();
//cin>>*F3;
//FarmacieOnline *p=dynamic_cast<FarmacieOnline*>(F3);
//cout<<endl<<(*p).get_web();
//Farmacii **v;
//Citire_si_Afisare_n_Farmacii(2,v);
//GestionareFarmacii <FarmacieOnline> G1;
//FarmacieOnline F1("www.dona.ro",20,12);
//FarmacieOnline F4("www.catena.ro",21,11);
//G1.add(F1);
//G1.add(F4);
//cout<<G1;
//GestionareFarmacii <FarmacieOnline> G3;
//FarmacieOnline F3("www.sensi_blue.ro",202,122);
//G3.add(F3);
//cout<<G3;
//GestionareFarmacii <Farmacie> G2;
//Farmacie F2("Catena",12,{1,2,3,5,3,2,4,3,5,4,3,4});
//G2.add(F2);
//cout<<G2;
//GestionareFarmacii <FarmacieOnline> G1;
//FarmacieOnline F1("www.dona.ro",20,12);
//FarmacieOnline F4("www.catena.ro",21,11);
//G1+=F1;
//G1+=F4;
//cout<<G1;
//GestionareFarmacii <FarmacieOnline> G3;
//FarmacieOnline F3("www.sensi_blue.ro",202,122);
//G3+=F3;
//cout<<G3;
//GestionareFarmacii <Farmacie> G2;
//Farmacie F2("Catena",12,{1,2,3,5,3,2,4,3,5,4,3,4});
//G2.add(F2);
//cout<<G2;
//GestionareFarmacii <Farmacie> G5;
//cin>>G5;
//cout<<G5;
//Farmacii **v;
//GestionareFarmacii <Farmacie> G1;
//GestionareFarmacii <FarmacieOnline> G2;
//Citire_si_Afisare_n_Farmacii(2,v,G1,G2);
//cout<<G1<<G2;
}
