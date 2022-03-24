#include <iostream>
using namespace std;

class Nod {
private:
    int info;
    Nod *next;

public:

    Nod();
    Nod(int);
    ~Nod(); //destructor
    int getInfo const { return info; };
    Nod* getNext();
    void setNext(Nod*);
    void setInfo(int);

};

Nod::Nod()
{
    info = 0;
    next = NULL;
}

Nod::Nod(int infor)
{
    info = infor;
    next = NULL;
}

Nod::~Nod()
{
    next = NULL;
}

int Nod:: getInfo()
{
    return info;
}

Nod* Nod::getNext()
{
    return next;
}

void Nod::setNext(Nod* urm)
{
    next = urm;
}
void Nod::setInfo(int info)
{
    info = info;
}

//trec la lista

class Lista_circulara{

private:
     Nod *prim;
     int nr;

public:
    Lista_circulara();
    Lista_circulara(Nod*, int);
    Lista_circulara(const Lista_circulara&);
    ~Lista_circulara(); //destructor
    void setPrim(Nod*);
    void setNr(int);
    Nod* getPrim()const;
    int getNr()const;
    void add(int, Nod*); //metoda pt adaugarea elem pe poz
    friend istream& operator>> (istream&, Lista_circulara&);
    //metoda publica care primește parametrul întreg k și realizeaza eliminarea elementelor
    //listei circulare din k în k pana la golirea acesteia (elementele vor fi afisate în ordinea în care sunt eliminate);
    void afis_k(int);
    void deleteF(int);
    void afis_sterg(int);

    void invers(); //metoda pt inversarea legaturilor listei
    Lista_circulara operator+(const Lista_circulara &); //concatenarea a 2 liste circulare

};

Lista_circulara::Lista_circulara()
{
    prim = NULL;
    nr = 0;
}

Lista_circulara::Lista_circulara(Nod *p, int n)
{
    prim = p;
    nr = n;
}

Lista_circulara::Lista_circulara(const Lista_circulara &l)
{
    nr = l.nr;
    prim = l.prim;
}

Lista_circulara::~Lista_circulara()
{
    Nod *p = prim, *q;
    while(nr)
    {
        q = p;
        p = p->getNext();
        delete q;
        nr--;
    }
    prim = NULL;
}

void Lista_circulara::setPrim(Nod *p)
{
    prim = p;
}

void Lista_circulara::setNr(int n)
{
    nr = n;
}

Nod* Lista_circulara::getPrim()const
{
    return prim;
}

int Lista_circulara::getNr()const
{
    return nr;
}

void Lista_circulara::add(int poz, Nod *elem)
{
    if(nr == 0)
    {
        prim = elem;
        prim->setNext(prim);
        nr++;
    }
    else
    if(poz == 0)
    {
        Nod *i = prim;
        int j = 1;
        while(j != nr )
        {
            j++;
            i = i->getNext();
        }
        i->setNext(elem);
        elem->setNext(prim);
        prim = elem;
        nr++;
    }
    else
    {
        Nod *i = prim;
        int j = 1;
        while(j != poz )
        {
            j++;
            i = i->getNext();
        }

        elem->setNext(i->getNext());
        i->setNext(elem);
        nr++;
    }
}

istream& operator>>(istream &read, Lista_circulara &l)
{
    cout << "Numar de elemente: ";
    int numar;
    read >> numar;

    for(int i = 0; i < numar; i++)
    {
        cout << "Elementul de pe pozitia " << i << ": ";
        int val;
        read >> val;
        Nod *elem = new Nod(val);
        l.add(i,elem);
    }
    return read;
}

void Lista_circulara::afis_k(int k)
{
    if(nr)
    {
        int i = 0;
        Nod *inc = prim;
        while(i != k)
        {
            i++;
            inc = inc->getNext();
        }

        i = nr + 1;
        cout << "Lista este: ";
        while(i != 0)
        {
            cout << inc->getInfo() << " ";
            inc = inc->getNext();
            i--;
        }
        cout << "\n";
    }
    else
        cout << "Lista goala\n";
}

void Lista_circulara::deleteF(int poz)
{
    if(nr == 0)
    {
        cout << "Lista goala; nu se pot extrage elemente\n";
    }
    else
    if(nr == 1)
    {
        prim = NULL;
        nr = 0;
    }
    else
    if(poz == 0)
    {
        Nod *i = prim;
        int j = 0;
        while(j != nr - 1)
        {
            i = i->getNext();
            j++;
        }
        i->setNext(prim->getNext());
        prim->setNext(NULL);
        prim = i->getNext();
        nr--;
    }
    else
    {
        Nod *i = prim, *k;
        int j = 0;
        while(j != poz - 1)
        {
            i = i->getNext();
            j++;
        }
        k = i->getNext();
        i->setNext(k->getNext());
        k->setNext(NULL);
        nr--;
    }
}

void Lista_circulara::afis_sterg(int k)
{
    if(nr)
    {
        int i = 0;
        Nod *inc = prim;
        while(i != k)
        {
            i++;
            inc = inc->getNext();
        }

        cout << "Lista este: ";
        int val = inc->getInfo();
        while(nr != 0)
        {
            cout << inc->getInfo() << " ";
            inc = inc->getNext();
            if(i == nr - 1 && nr != 1)
            {
                deleteF(i);
                i = 0;
            }
            else
                deleteF(i);
        }
        cout << val << "\n";
    }
    else
        cout << "Lista goala\n";
}

void Lista_circulara::invers()
{
    if(nr == 0)
    {
        cout << "Lista goala\n";
    }
    else
    {
        int i = nr;
        Nod *curent = prim, *pre = NULL, *next = NULL, *primul = NULL;

        next = curent->getNext();
        curent->setNext(pre);
        pre = curent;
        curent = next;
        primul = pre;
        i--;

        while(i)
        {
            next = curent->getNext();
            curent->setNext(pre);
            pre = curent;
            curent = next;
            i--;
        }
        primul->setNext(pre);
        prim = pre;
    }
}

Lista_circulara Lista_circulara::operator+(const Lista_circulara &l2)
{
    Nod *primul, *p = prim, *element_p = new Nod(prim->getInfo()), *q;
    primul = element_p;
    q = primul;
    p = p->getNext();

    for(int i = 1; i < nr; i++)
    {
        Nod *el = new Nod(p->getInfo());
        q->setNext(el);
        q = q->getNext();
        p = p->getNext();
    }

    p = l2.prim;
    for(int i = 0; i < l2.nr; i++)
    {
        Nod *el = new Nod(p->getInfo());
        q->setNext(el);
        q = q->getNext();
        p = p->getNext();
    }
    q->setNext(primul);
    return Lista_circulara(primul,nr + l2.nr);
}

int main()
{
    Lista_circulara L;
    cout<< "Alegeti optiunea:"<<"\n";
    cout<< "1.Citire si afisare lista"<<"\n";
    cout<< "2.Adaugare element pe o pozitie"<<"\n";
    cout<< "3.Stergerea unui element de pe o pozitie "<<"\n";
    cout<< "4.Inversarea legaturilor listei "<<"\n";
    cout<< "5.Eliminarea elementelor din k in k + afisare "<<"\n";
    cout<< "6.Concatenare 2 liste "<<"\n";
    int op;
    cin>>op;

    while(op != 0)
    {
        if (op == 1)
        {
            cin>>L;
            L.afis_k(0);
            break;
        }

        if (op == 2)
        {
            {
                cout << "Introduceti valoarea elementului de adaugat: ";
                cout << "Introduceti pozitia pe care va fi adaugat: ";
                int val, poz;
                cin >> val;
                cin >> poz;
                if(poz >= 0 && poz < L.getNr())
                {
                    Nod *elem = new Nod(val);
                    L.add(poz,elem);
                    L.afis_k(0);
                }
                else
                    cout << "Eroare pozitie\n";
                break;
            }
        }

        if (op == 3)
        {
            cout<<"Introduceti pozitia de pe care se va sterge: ";
            int poz;
            cin>>poz;
            if(poz >= 0 && poz < L.getNr())
                L.afis_sterg(poz);
            else
                cout << "Eroare pozitie\n";
            break;
        }

        if (op == 4)
        {
            L.invers();
            L.afis_k(0);
            break;
        }

        if (op == 5)
        {
            cout<< "Introduceti k pentru eliminare:";
            int k;
            cin>>k;
            if(k >= 0 && k < L.getNr())
            {
                L.deleteF(k);
                L.afis_k(0);
            }
            else
                cout << "Eroare pozitie\n";
            break;
        }


        if(op == 6)
        {
            if(L.getNr() == 0)
                cout << "Prima lista este goala, nu se poate concatena\n";
            else
            {
                cout << "Introduceti lista de concatenat cu prima: \n";
                Lista_circulara L2;
                cin >> L2;
                (L + L2).afis_k(0);
            }
            break;
        }
    }
}