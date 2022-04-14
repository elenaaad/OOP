//Dobre Elena Cristina 133
//Tema 11

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Persoana
{

protected:
    string nume, cnp;

public:
    // constructori
    Persoana();
    Persoana(string nume, string cnp)
    {
        this->nume = nume;
        if (cnp_valid(cnp) == 1)
            this->cnp = cnp;
        else
            this->cnp = "-1";
    }

    //constructor de copiere
    Persoana(const Persoana &p1)
    {
        // cout<<"Persoana: copy constructor called\n";
        nume = p1.nume;
        if (cnp_valid(p1.cnp) == 1)
            cnp = p1.cnp;
        else
            cnp = "-1";
    }

    // destructor
    ~Persoana()
    {
        nume = "\0";
        cnp = "\0";
        // cout<<"Persoana: obiect distrus\n";
    }

    friend istream &operator>>(istream &is, Persoana &p1);
    friend ostream &operator<<(ostream &out, const Persoana &p1);

    Persoana &operator=(const Persoana &p1)
    {
        this->nume = p1.nume;
        this->cnp = p1.cnp;
        return *this;
    }

    // Getters si Setters
    string Get_Nume()
    {
        return nume;
    }

    string Get_CNP()
    {
        return cnp;
    }

    void Set_Nume(string nume)
    {
        this->nume = nume;
    }

    void Set_CNP(string cnp)
    {
        this->cnp = cnp;
    }

    void date_cnp(long long x, int &nr_cifre, int &sex, int &ziuaNasterii, int &lunaNasterii, int &anulNasterii)
    {
        ziuaNasterii = x / 1000000 % 100;
        lunaNasterii = x / 100000000 % 100;
        anulNasterii = x / 10000000000 % 100;
        nr_cifre = 0;
        while (x > 9)
        {
            x /= 10;
            nr_cifre++;
        }
        nr_cifre++;
        sex = x;
    }

    // Functie care calculeaza varsta unei persoane din CNP
    int calcul_varsta(Persoana p)
    {

        time_t now = time(0);
        tm *ltm = localtime(&now); //timpul curent
        long long cnp = stoll(p.cnp); //conversie string la long long
        int anulNasterii, lunaNasterii, ziuaNasterii, sex, an, varsta, nr_cifre;

        date_cnp(cnp, nr_cifre, sex, ziuaNasterii, lunaNasterii, anulNasterii);

        if (sex == 1 || sex == 2)
        {
            an = 1900 + anulNasterii;
        }
        else if (sex == 5 || sex == 6)
            an = 2000 + anulNasterii;
        int an_curent = 1900 + ltm->tm_year; //tm_year: ani trecuti din 1900 pana acum
        varsta = an_curent - an;

        if (ltm->tm_mon <  lunaNasterii) //tm_mon: luni trecute din ianuarie pana acum
            varsta--;
        else if (ltm->tm_mon ==  lunaNasterii)
            if (ltm->tm_mday < ziuaNasterii) // tm_mday: ziua din luna
                varsta--;
        return varsta;
    }

    // Extrage alte date din CNP
    void scurta_descriere(Persoana a)
    {
        long long cnp = stoll(a.cnp);
        int sex, an_nastere, luna_nastere, zi_nastere, an, varsta, numar_cifre;
        date_cnp(cnp, numar_cifre, sex, zi_nastere, luna_nastere, an_nastere);

        cout << "\nPersoana cu numele " << a.nume << ", de sex ";
        if (sex == 1 || sex == 5)
            cout << "M";
        else if (sex == 2 || sex == 6)
            cout << "F";
        if (sex < 3)
            an_nastere += 1900;
        else
            an_nastere += 2000;
        cout <<" este nascut(a) in data de ";
        cout << zi_nastere << "." << luna_nastere << "." << an_nastere << " .\n";
    }

    virtual void afisare_tip(){

        cout<<"\nDatele afisate sunt de tip PERSOANA.\n";
    }

    int cnp_valid(string CNP)
    {
        long long cnp = stoll(CNP);
        int nr_cifre, sex, zi_nastere, luna_nastere, an_nastere;
        date_cnp(cnp, nr_cifre, sex, zi_nastere, luna_nastere, an_nastere);
        if (nr_cifre != 13)
        {
            cout << "\n!!! Eroare: Numarul de cifre din CNP trebuie sa fie 13.\n\n";
            return 0;
        }
        else
        {
            if (sex != 1 && sex != 2 && sex != 5 && sex != 6)
            {
                cout << "\n!!! Eroare: Genul (F/M) invalid!\n\n";
                return 0;
            }
            if (luna_nastere > 12)
            {
                cout << "\n!!! Eroare: Luna nasterii este invalida!\n\n";
                return 0;
            }
            if (an_nastere > 31)
            {
                cout << "\n!!! Eroare: Anul nasterii este invalid!\n\n";
                return 0;
            }
        }
        return 1;
    }
};

istream &operator>>(istream &is, Persoana &p1)
{
    cout << "\nNume persoana: ";
    is >> p1.nume;
    cout << "CNP persoana: ";
    is >> p1.cnp;
    while(p1.cnp_valid(p1.cnp) != 1){
        cout << "CNP persoana: ";
        is >> p1.cnp;
    }
    return is;
}

ostream &operator<<(ostream &out, const Persoana &p1)
{
    cout << "\nNume persoana: ";
    out << p1.nume << '\n';
    cout << "CNP persoana: ";
    cout << p1.cnp << '\n';
    return out;
}

void tip(Persoana *p){
    p->afisare_tip();
}

class Abonat : public Persoana
{

protected:
    int nrMaxCarti, nrCartiImprumutate, pretAbonament;
    int limit = 0;

public:
    // constructors
    Abonat();

    Abonat(string nume,string cnp,int nrMaxCarti, int nrCartiImprumutate, int pretAbonament)
    {

        this->nume = nume;
        if (cnp_valid(cnp) == 1)
            this->cnp = cnp;
        else
            this->cnp = "-1";
        this->nrMaxCarti = nrMaxCarti;
        this->nrCartiImprumutate = nrCartiImprumutate;
        this->pretAbonament = pretAbonament;

        if (nrCartiImprumutate > nrMaxCarti)
        {
            limit = 1;
            cout << "\n Abonatul a depasit limita de ";
            cout << nrCartiImprumutate << " carti imprumutate. Numarul maxim de carti permise in abonamentul sau: ";
            cout << nrMaxCarti;
        }
        else if (nrMaxCarti > pretAbonament)
        {
            limit = 2;
            cout << "\n!!! Abonatul a depasit limita de ";
            cout << nrMaxCarti << " carti permise in abonamentul sau. Pretul abonamentului: ";
            cout << pretAbonament << ") .!!! \n";
        }
        else
            cout << "\nAbonatul se incadreaza in limita.\n";
    }

    // copy constructor
    Abonat(const Abonat &a1)
    {
        nume = a1.nume;
        if (cnp_valid(a1.cnp) == 1)
            cnp = a1.cnp;
        else
            cnp = "-1";
        nrMaxCarti = a1.nrMaxCarti;
        nrCartiImprumutate = a1.nrCartiImprumutate;
        pretAbonament = a1.pretAbonament;
        limit = a1.limit;

        if (limit == 1)
        {
            cout << "\n Abonatul a depasit limita de ";
            cout << nrCartiImprumutate << " carti imprumutate. Numarul maxim de carti permise in abonamentul sau: ";
            cout << nrMaxCarti;
        }
        else if (limit == 2)
        {
            cout << "\n Abonatul a depasit limita de ";
            cout << nrMaxCarti << " carti permise in abonamentul sau. Pretul abonamentului: ";
            cout << pretAbonament;
        }
        else
            cout << "\nAbonatul se incadreaza in limita.\n";
    }

    // destructor
    ~Abonat()
    {
        // cout<<"Abonat: obiect distrus\n";
        nrMaxCarti = nrCartiImprumutate = pretAbonament = 0;
    }

    friend istream &operator>>(istream &is, Abonat &a1);

    friend ostream &operator<<(ostream &out, const Abonat &a1);

    Abonat &operator=(const Abonat &a1)
    {
        Persoana::operator=(a1);
        this->nrMaxCarti = a1.nrMaxCarti;
        this->nrCartiImprumutate = a1.nrCartiImprumutate;
        this->pretAbonament = a1.pretAbonament;
        return *this;
    }

    // Getters si Setters
    int Get_nrMaxCarti()
    {
        return nrMaxCarti;
    }

    int Get_NrCartiImprumutate()
    {
        return nrCartiImprumutate;
    }

    int Get_PretAbonament()
    {
        return pretAbonament;
    }

    int Get_Limita()
    {
        return limit;
    }

    void Set_NrMaxCarti(int nrMaxCarti)
    {
        this->nrMaxCarti = nrMaxCarti;
    }

    void Set_NrCartiImprumutate(int nrCartiImprumutate)
    {
        this->nrCartiImprumutate = nrCartiImprumutate;
    }

    void Set_PretAbonament(int pretAbonament)
    {
        this->pretAbonament = pretAbonament;
    }

    void Set_Limita(int limitt)
    {
        this->limit = limit;
    }

    void afisare_tip(){
        cout<<"\nDatele afisate sunt de tip abonat.\n";
    }
};

istream &operator>>(istream &is, Abonat &a1)
{
    // persoana
    is >> dynamic_cast<Persoana &>(a1);

    // abonat
    cout << "Numarul maxim de carti: ";
    is >> a1.nrMaxCarti;
    cout << "Numarul de carti imprumutate: ";
    is >> a1.nrCartiImprumutate;
    cout << "Pretul abonamentului : ";
    is >> a1.pretAbonament;

    if (a1.nrCartiImprumutate > a1.nrMaxCarti)
    {
        a1.limit = 1;
        cout << "\n Abonatul a depasit limita de ";
        cout << a1.nrCartiImprumutate << " carti imprumutate. Numarul maxim de carti permise in abonamentul sau: ";
        cout << a1.nrMaxCarti;
    }
    else if (a1.nrMaxCarti > a1.pretAbonament)
    {
        a1.limit = 2;
        cout << "\n Abonatul a depasit limita de ";
        cout << a1.nrMaxCarti << " carti permise in abonamentul sau. Pretul abonamentului: ";
        cout << a1.pretAbonament;
    }
    else
    {
        a1.limit = 0;
        cout << "\nAbonatul nu a depasit limita.\n";
    }
    return is;
}

ostream &operator<<(ostream &out, const Abonat &a1)
{
    // persoana
    cout << "\nNumele abonatului: ";
    out << a1.nume << '\n';
    cout << "CNP-ul abonatului: ";
    out << a1.cnp << '\n';

    // abonat
    cout << "Numarul maxim de carti al abonatului: ";
    out << a1.nrMaxCarti << '\n';
    cout << "Numarul cartilor imprumutate ale abonatului: ";
    cout << a1.nrCartiImprumutate << '\n';
    cout << "Pret abonament: ";
    out << a1.pretAbonament;

    if (a1.limit == 1)
    {
        cout << "\n Abonatul a depasit limita de ";
        cout << a1.nrCartiImprumutate << " carti imprumutate. Numarul maxim de carti permise in abonamentul sau: ";
        cout << a1.nrMaxCarti;
    }
    else if (a1.limit == 2)
    {
        cout << "\n!!! Abonatul a depasit limita de ";
        cout << a1.nrMaxCarti << " carti permise in abonamentul sau. Pretul abonamentului: ";
        cout << a1.pretAbonament;
    }
    else
        cout << "\nAbonatul nu a depasit limita.\n";

    return out;
}

class Dosar : public Abonat
{

protected:
    Abonat *abonati;
    int lungime;
    int Nr_Abonati_Stersi=0;
    Persoana abonati_stersi[101];
    static int deleted;

public:
    // constructori
    Dosar()
    {
        abonati = new Abonat[101];
    }

    Dosar(Abonat abonati[], int lungime)
    {
        this->lungime = lungime;
        for (int i = 1; i <= lungime; i++)
        {
            Abonat aux = *abonati;
            this->abonati[i] = aux;
        }
        Nr_Abonati_Stersi = 0;
    }

    // constructor de copiere
    Dosar(const Dosar &d1)
    {
        lungime = d1.lungime;
        for (int i = 1; i <= lungime; i++)
            abonati[i] = d1.abonati[i];
        Nr_Abonati_Stersi = 0;
    }

    // destructor
    ~Dosar()
    {
        delete abonati;
    }

    friend istream &operator>>(istream &is, Dosar &d1);

    friend ostream &operator<<(ostream &out, const Dosar &d1);

    Dosar &operator=(const Dosar &d1)
    {
        Abonat::operator=(d1);
        this->lungime = d1.lungime;
        int i;
        for (i = 1; i <= d1.lungime; i++)
            this->abonati[i] = d1.abonati[i];
        return *this;
    }

    // Getters si Setters
    int Get_Lungime()
    {
        return lungime;
    }

    Abonat *Get_Abonati()
    {
        return abonati;
    }

    Abonat Get_Abonat_Index(int index){
        return abonati[index];
    }

    void Set_Lungime(int lungime)
    {
        this->lungime = lungime;
    }

    void Set_Abonati(Abonat abonati[])
    {
        Set_Lungime(lungime);
        for (int i = 1; i <= lungime; i++)
            this->abonati[i] = abonati[i];
    }

    // Functie de eliminare a unui abonat din dosar
    void eliminare_abonat(Dosar &d, int index)
    {
        cout << "\nSe va elimina abonatul cu urmatoarele date:\n";
        cout << d.abonati[index];
        ;
        d.Nr_Abonati_Stersi++;
        d.abonati_stersi[d.Nr_Abonati_Stersi]=d.abonati[index];
        deleted++;

        for (int i = index + 1; i <= d.lungime; i++)
            d.abonati[i - 1] = d.abonati[i];
        d.lungime--;

    }

    // Funtie de creare a unui nou abonat si de adaugare a lui in dosar.
    void adaugare_abonat(Dosar &d, int index)
    {
        cout << "\nSe va adauga un abonat la pozitia " << index << " cu urmatoarele date:\n\n";

        Abonat a1; cin>>a1;

        for (int i = index; i <= d.lungime; i++)
            d.abonati[i + 1] = d.abonati[i];
        d.lungime++;

        d.abonati[index] = a1;
    }

    // Functie care afiseaza numarul de abonati care au fost stersi din toate dosarele
    static void print_deleted()
    {
        if (deleted == 0)
            cout << "\nNu a fost eliminat niciun abonat din dosare.\n";
        else if (deleted == 1)
            cout << "A fost eliminat un singur abonat din toate dosarele.\n";
        else
            cout << "\nNumarul de abonati care au fost eliminati din toate dosarele este de " << deleted << "." << endl;
    }

    void afisare_nr_abonati_stersi()
    {
        if (Nr_Abonati_Stersi == 0)
            cout << "\nNu a fost eliminat niciun abonat din dosar.\n";
        else if (Nr_Abonati_Stersi == 1)
            cout << "A fost eliminat un singur abonat din dosar.\n";
        else
            cout << "\nNumarul de abonati care au fost eliminati din dosar este de " << Nr_Abonati_Stersi << "." << endl;
    }

    void afisare_abonati_stersi(Dosar &d,int index_dosar){
        int i;
        cout<<"\nDOSARUL "<<index_dosar<<":\n";
        for(i=1;i<=d.Nr_Abonati_Stersi;i++)
            cout<<d.abonati_stersi[i];

        tip(d.abonati_stersi);
    }
};

int Dosar::deleted = 0;

istream &operator>>(istream &is, Dosar &d1)
{
    cout << "\nLungimea dosarului: ";
    is >> d1.lungime;
    if (d1.lungime)
    {
        cout << "\nDate abonati:\n";
        for (int i = 1; i <= d1.lungime; i++)
            is >> d1.abonati[i];
    }
    return is;
}

ostream &operator<<(ostream &out, const Dosar &d1)
{
    if (d1.lungime == 0)
        cout << "\nDosarul este gol.\n";
    else
    {
        if (d1.lungime == 1)
            cout << "\n\nEste un singur abonat in dosar, cu urmatoarele date:\n";
        else
            cout << "\n\nSunt " << d1.lungime << " abonati in dosar, cu urmatoarele date:\n";
        for (int i = 1; i <= d1.lungime; i++)
        {
            out << d1.abonati[i];
            cout << "\n";
        }
    }
    return out;
}

void citire_dosare(int &n, Dosar d[])
{
    int i;
    cout << "\nNumarul de dosare: ";
    cin >> n;
    cout << "\n------------------------------------------------------------------------------------\n\n";
    cout << "Date in fiecare dosar:\n\n";
    for (i = 1; i <= n; i++)
    {
        cout << "DOSARUL " << i << '\n';
        cin >> d[i];
        cout << '\n';
    }
}

void afisare_dosare(int n, Dosar d[])
{
    int i;
    cout << "------------------------------------------------------------------------------------\n\n";
    cout << "EXISTA DATE IN URMATOARELE DOSARE:\n\n";
    for (i = 1; i <= n; i++)
    {
        cout << "DOSARUL " << i << '\n';
        cout << d[i] << "\n";
    }

    tip(d->Get_Abonati());
}

int main()
{
    Dosar dosare[101];
    int n, ok = 0;
    while (true)
    {
        int task;
        cout << "\n------------------------------------------------------------------------------------\n\n";
        cout << " Bine ati venit la biblioteca! Introduceti numarul corespunzator actiunii dorite: \n\n";
        cout << "1. Introducerea datelor in dosare.\n";
        cout << "2. Afisarea datelor din toate dosarele.\n";
        cout << "3. Afisarea datelor dintr-un anumit dosar.\n";
        cout << "4. Prelucrarea datelor dintr-un anumit dosar.\n";
        cout << "5. Afisarea tuturor persoanelor care au fost sterse din dosare.\n";
        cout << "6. Afisarea numarului de abonati stersi din toate dosarele.\n";
        cout << "7. Iesire din program.\n\n";
        cout << "Optiune: ";
        cin >> task;
        switch (task)
        {
            case 1:
            {
                citire_dosare(n, dosare);
                ok = 1;
                break;
            }
            case 2:
            {
                if (ok == 1)
                    afisare_dosare(n, dosare);
                else
                    cout << "\n Nu exista date in niciun dosar. \n";
                break;
            }
            case 3:
            {
                if (ok == 1)
                {
                    cout << "Introduceti numarul dosarului pe care doriti sa il afisati (de la 1 la " << n << "): ";
                    int numar_dosar;
                    cin >> numar_dosar;
                    while (numar_dosar < 1 || numar_dosar > n)
                    {
                        cout << "\n Index invalid, introduceti o valoare cuprinsa intre 1 si " << n << '\n';
                        cout <<"Introduceti numarul dosarului pe care doriti sa il afisati (de la 1 la " << n << "): ";
                        cin >> numar_dosar;
                    }
                    cout << dosare[numar_dosar];
                }
                else
                    cout << "\n Nu exista date in niciun dosar.\n";
                break;
            }
            case 4:
            {
                if (ok == 1)
                {
                    cout << "Introduceti numarul dosarului pe care doriti sa il afisati (de la 1 la " << n << "): ";
                    int numar_dosar;
                    cin >> numar_dosar;
                    while (numar_dosar < 1 || numar_dosar > n)
                    {
                        cout << " Index invalid, introduceti o valoare cuprinsa intre 1 si " << n << '\n';
                        cout << "Introduceti numarul dosarului pe care doriti sa il afisati (de la 1 la " << n << "): ";
                        cin >> numar_dosar;
                    }

                    int task2;
                    while(true)
                    {

                        cout << "\n------------------------------------------------------------------------------------\n\n";
                        cout << "Selectati optiunea: \n\n";
                        cout << "9.  Afisarea datelor din dosarul selectat.\n";
                        cout << "10. Stergerea unui anumit abonat din dosarul selectat.\n";
                        cout << "11. Afisarea datelor (extrase din CNP) ale unui abonat din dosarul selectat.\n";
                        cout << "12. Afisarea numarului de abonati care au fost stersi .\n";
                        cout << "13. Adaugarea unui abonat in dosarul selectat.\n";
                        cout << "14. Iesire din submeniu.\n\n";
                        cout << "Optiune: ";

                        cin>>task2;

                        if(task2==9){
                            cout << "\n------------------------------------------------------------------------------------\n\n";
                            cout << "Se vor afisa datele din dosarul cu numarul "<<numar_dosar<<" .\n";
                            cout<<dosare[numar_dosar];
                        }
                        else
                        if(task2==10){
                            cout << "\n------------------------------------------------------------------------------------\n\n";
                            int index_abonat;
                            cout<<"\nIndexul abonatului pe care doriti sa-l stergeti (de la 1 la "<<dosare[numar_dosar].Get_Lungime()<<") .\n";
                            cin>>index_abonat;
                            while (index_abonat < 1 || index_abonat > dosare[numar_dosar].Get_Lungime())
                            {
                                cout << "\n Index de dosar invalid \n";
                                cout << "Indexul abonatului pe care doriti sa il afisati (de la 1 la " << dosare[numar_dosar].Get_Lungime() << "):";
                                cin >> index_abonat;
                            }
                            cout << "Se va sterge abonatul cu indexul "<<index_abonat<<"\n";
                            dosare[numar_dosar].eliminare_abonat(dosare[numar_dosar],index_abonat);
                        }
                        else
                        if(task2==11){
                            cout << "\n------------------------------------------------------------------------------------\n\n";
                            int index_abonat;
                            cout<<"\nDati indexul abonatului caruia doriti sa-i aflati datele (un numar natural intre 1 si "<<dosare[numar_dosar].Get_Lungime()<<") :\n";
                            cin >> index_abonat;
                            while (index_abonat < 1 || index_abonat > dosare[numar_dosar].Get_Lungime())
                            {
                                cout << "\nAti introdus un index de dosar invalid, va rog introduceti in consola o valoare cuprinsa intre 1 si " << n << '\n';
                                cout <<"\nDati indexul abonatului caruia doriti sa-i aflati datele (un numar natural intre 1 si "<<dosare[numar_dosar].Get_Lungime()<<") :\n";
                                cin >> index_abonat;
                            }
                            cout << "Se vor afisa datele abonatului "<<index_abonat<<" din dosarul selectat .\n";
                            dosare[numar_dosar].scurta_descriere(dosare[numar_dosar].Get_Abonat_Index(index_abonat));
                        }
                        else
                        if(task2==12){
                            cout << "\n------------------------------------------------------------------------------------\n\n";
                            cout<<"Se va afisa numarul de abonati care au fost stersi din dosarul selectat. \n";
                            dosare[numar_dosar].afisare_nr_abonati_stersi();
                        }
                        else
                        if(task2==13){
                            cout << "\n------------------------------------------------------------------------------------\n\n";
                            cout<<"Se va adauga un abonat nou la dosarul selectat la primul index. \n";

                            dosare[numar_dosar].adaugare_abonat(dosare[numar_dosar],1);
                        }
                        else
                        if(task2==14){
                            cout << "\n------------------------------------------------------------------------------------\n\n";
                            cout<<" Iesire submeniu \n";
                            break;
                        }
                        else{
                            cout << "\nOptiune invalida.\n\n";
                            cout << "------------------------------------------------------------------------------------\n\n";
                        }
                    }
                }
                else
                    cout << "\n Nu exista date in niciun dosar, introduceti 1 pt a adauga date \n";
                break;
            }

            case 5:
            {
                if(ok==1){
                    cout<< "\n Lista persoanelor sterse pentru fiecare dosar:\n";
                    for(int i=1;i<=n;i++)
                        dosare[i].afisare_abonati_stersi(dosare[i],i);
                }
                else
                    cout << "\nNu exista date in niciun dosar, introduceti 1 pt a adauga date\n";
                break;
            }

            case 6:
            {
                if(ok==1){
                    cout << "\nNumarul de abonati care au fost stersi din toate dosarele\n";
                    dosare->print_deleted();
                }
                else
                    cout << "\nNu exista date in niciun dosar, introduceti 1 pt a adauga date\n";
                break;
            }

            case 7:
            {
                cout << "\n O zi buna! \n\n";
                exit(0);
                break;
            }

            default:
                cout << "\n Optiune invalida \n\n";
                break;
        }
    }
    return 0;
}