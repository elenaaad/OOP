#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

class Plata
{
protected:
    int data;
    float suma;

public:
    Plata(int d=0,float s=0)
    {
        data=d;
        suma=s;
    }
    Plata(const Plata &ob);

    ~Plata(){}

    void setData(int d) { data=d;}

    int getData() {return data;}

    void setSuma(float s){suma=s;}

    int getSuma(){return suma;}

    virtual void cin_plata();
    virtual void cout_plata();

    friend istream& operator>>(istream &in,Plata &p)
    {
        p.cin_plata();
        return in;
    }

    friend ostream& operator<<(ostream &out,Plata &p)
    {
        p.cout_plata();
        return out;
    }
    Plata& operator=(const Plata& ob);
};

Plata::Plata(const Plata &ob)
{
    data=ob.data;
    suma=ob.suma;
}

void Plata::cin_plata()
{
    cout<<"Data: "<<'\n';
    cin>>data;
    cout<<"Suma: "<<'\n';
    cin>>suma;
}
void Plata::cout_plata()
{
    cout<<"Data:"<<data<<'\n';
    cout<<"Suma:"<<suma<<'\n';

}
Plata& Plata::operator=(const Plata &ob)
{
    if(this != &ob)
    {
        data=ob.data;
        suma=ob.suma;
    }
    return *this;
}


class Numerar: public Plata
{
public:
    Numerar(){}
    ~Numerar(){}

    void cin_plata()
    {
        cout<<"-Plata numerar-"<<'\n';
        cout<<"Data: "<<'\n';
        cin>>data;
        cout<<"Suma: "<<'\n';
        cin>>suma;
    }
    void cout_plata()
    {
        cout<<"Chitanta Plata - numerar"<<'\n';
        cout<<"Data: "<<data<<'\n';
        cout<<"Suma: "<<suma<<'\n';

    }
};

class Cec:public Plata
{
public:
    void cin_plata()
    {
        cout<<"Plata - cec"<<'\n';
        cout<<"Data: "<<'\n';
        cin>>data;
        cout<<"Suma: "<<'\n';
        cin>>suma;
    }
    void cout_plata()
    {
        cout<<"Chitanta Plata - cec"<<'\n';
        cout<<"Data: "<<data<<'\n';
        cout<<"Suma: "<<suma<<'\n';
    }
};


class Card_credit:public Plata
{
private:
    int nr_card;

public:
    Card_credit(int data=0,float suma=0,int nrc=0):Plata(data,suma)
    {
        nr_card=nrc;
    }
    Card_credit(const Card_credit &ob):Plata(ob)
    {
        nr_card=ob.nr_card;
    }
    ~Card_credit(){}

    void cin_plata()
    {
        cout<<"PLATA CARD DE CREDIT"<<'\n';
        cout<<"Introduceti numarul cardului: "<<'\n';
        cin>>nr_card;
        cout<<"Data: "<<'\n';
        cin>>data;
        cout<<"Suma: "<<'\n';
        cin>>suma;
    }
    void afisare_plata()
    {
        cout<<"-Chitanta Plata card de credit-"<<'\n';
        cout<<"Data: "<<data<<'\n';
        cout<<"Suma; "<<suma<<'\n';
        cout<<"Numar card de credit:"<<nr_card<<'\n';
    }

    Card_credit& operator=(const Card_credit &ob);
};

Card_credit& Card_credit::operator=(const Card_credit &ob)
{
    if(this!=&ob)
        this->Plata::operator=(ob);
    return *this;
}

template <class T>
class Gestiune
{
    T *N;
    unordered_map <int,T> map;

    int total_plati;
    int plati_num;
    int plati_cec;
    int plati_card;

public:

    Gestiune(int num=0,int cec=0,int card=0,int plati=0)
    {
        plati_num=num;
        plati_cec=cec;
        plati_card=card;
        total_plati=plati;
    }
    Gestiune(const Gestiune &ob)
    {
        plati_num=ob.plati_num;
        plati_cec=ob.plati_cec;
        plati_card=ob.plati_card;
        total_plati=ob.total_plati;
    }
    ~Gestiune(){}

    void setTotal_plati(int nr)
    {
        total_plati=nr;
    }
    void setPlati_num(int nr)
    {
        plati_num=nr;
    }
    void setPlati_cec(int nr)
    {
        plati_cec=nr;
    }
    void setPlati_card(int nr)
    {
        plati_card=nr;
    }

    void Cin_Gestiune();
    void Cout_Gestiune();

    Gestiune operator +=(Gestiune obp)
    {
        total_plati=obp.total_plati + total_plati;
        plati_num = obp.plati_num + plati_num;
        plati_cec=obp.plati_cec + plati_cec;
        plati_card=obp.plati_card + plati_card;

        return *this;
    }

    void TotalNum(int nr_plati)
    {
        plati_num+=nr_plati;
        cout<<"Totalul inregistrat de plati numerar: "<<plati_num<<'\n';
    }

    void TotalCec(int nr_plati)
    {
        plati_cec+=nr_plati;
        cout<<"Totalul inregistrat de plati cec: "<<plati_cec<<'\n';
    }

    void TotalCard(int nr_plati)
    {
        plati_card+=nr_plati;
        cout<<"Totalul inregistrat de plati cu cardul: "<<plati_card<<'\n';
    }
};

template <class T>
void Gestiune<T>::Cin_Gestiune()
{

    N=new T[total_plati];

    for(int i=0; i<total_plati; i++)
    {
        N[i].cin_plata();
        map.insert(pair<int,T>(i,N[i]));
    }

}
template <class T>
void Gestiune<T>::Cout_Gestiune()
{

    typename unordered_map<int,T>::iterator it;
    for(it = map.begin(); it != map.end(); it++) {
        cout << it->first << " " << it->second;
        cout << '\n';
    }
}

template<>
class Gestiune<Card_credit>
{

    int total_plati;
    int plati_card;
    int nr_clienti;
    char Client[31];
    Card_credit *N;

    unordered_map <int,Card_credit> map;


public:

    Gestiune(int card=0,int plati=0,int nr_cl=0)
    {

        plati_card=card;
        total_plati=plati;
        nr_clienti=nr_cl;
        strcpy(Client,"");
    }

    Gestiune(const Gestiune &ob)
    {

        plati_card=ob.plati_card;
        total_plati=ob.total_plati;
        nr_clienti=ob.nr_clienti;
        strcpy(Client,ob.Client);
    }

    ~Gestiune(){}

    void setTotal_plati(int nr)
    {
        total_plati=nr;
    }

    void setPlati_card(int nr)
    {
        plati_card=nr;
    }

    Gestiune operator +=(Gestiune obp)
    {

        plati_card = obp.plati_card + plati_card;
        total_plati = obp.total_plati + total_plati;

        return *this;
    }
    
    void TotalCard(int nr_plati)
    {
        plati_card+=nr_plati;
        cout<<"(Acest client) Totalul inregistrat de plati cu cardul: "<<plati_card<<'\n';
    }


    void Cin_Gestiune()
    {

        N=new Card_credit[total_plati];

        cout<<"Introduceti numarul de clienti "<<'\n';
        cin>>nr_clienti;

        for(int j=0; j<nr_clienti; j++)
        {
            cout<<"Introduceti numele clientului "<<'\n';
            cin>>Client;

            for(int i=0; i<total_plati; i++)
            {
                N[i].cin_plata();
                map.insert(pair<int,Card_credit>(i,N[i]));

            }
        }

    }

    void Cout_Gestiune()
    {
        cout<<"Numar clienti: "<<nr_clienti<<'\n';
        cout<<"Nume client: "<<Client<<'\n';

        typename unordered_map<int,Card_credit>::iterator it;

        for(it=map.begin(); it!=map.end(); it++) {
            cout << it->first << " " << it->second;
            cout << '\n';
        }
    }
};

int main()
{

    int op;
    int plati_num=0,plati_cec=0,plati_card=0;

    do {
        cout << "Alegeti optiunea de plata:" << '\n';

        cout << "1: Numerar" << '\n';
        cout << "2: Cec" << '\n';
        cout << "3: Card de credit" << '\n';
        cout << "4: Cancel" << '\n';

        cin >> op;

        if (op == 1) {
            cout << "Ati ales numerar" << '\n';

            Gestiune<Numerar> N;
            N.setPlati_num(plati_num);

            cout << "Introduceti numarul de plati:" << '\n';
            cin >> plati_num;

            N.setPlati_num(plati_num);
            N.Cin_Gestiune();
            N.TotalNum(plati_num);
            N.Cout_Gestiune();


        } else if (op == 2) {

            cout << "Ati ales cec" << '\n';

            Gestiune<Cec> C;
            C.setPlati_cec(plati_cec);

            cout << "Numarul de plati: " << '\n';
            cin >> plati_cec;

            C.setPlati_cec(plati_cec);
            C.Cin_Gestiune();
            C.TotalCec(plati_cec);
            C.Cout_Gestiune();

        } else if (op == 3) {
            cout << "Ati ales plata cu cardul" << '\n';

            Gestiune<Card_credit> CC;
            CC.setPlati_card(plati_card);

            cout << "Numarul de plati ale acestui client: " << '\n';
            cin >> plati_card;

            CC.setPlati_card(plati_card);
            CC.Cin_Gestiune();
            CC.TotalCard(plati_card);
            CC.Cout_Gestiune();

        } else if (op == 4) {
            cout << "La revedere!"<< '\n';
        } else {
            cout << "Optiunea nu exista";
        }

    }
    while(op!=4);

    return 0;
}