#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>
using namespace std;

//clasa template pentru modificare pretului
template <class P> P suma(P a, P b)
{
	return a + b;
}

//clasa pentru a trata exceptii in cazul in care senzorul nu apartine in sistemul IoT
class apartinesistem :public exception
{
	string mesajConfirmare;
public:
	apartinesistem()
	{
		this->mesajConfirmare = "nu este recunoscut senzorul, deci nu apartine in sistemul IoT.";
	}
	apartinesistem(string mc)
	{
		this->mesajConfirmare = mc;
	}
	apartinesistem operator=(const apartinesistem& as)
	{
		this->mesajConfirmare = as.mesajConfirmare;

		return*this;
	}

	string mesaj()
	{
		return this->mesajConfirmare;
	}

	const char* what() const
	{
		return this->mesajConfirmare.c_str();
	}
};

class functiiconectare
{
protected:
	//functii virtuale pure
	virtual void conecteaza() = 0;
	virtual void deconecteaza() = 0;
	virtual void profil() = 0;
};
 class senzorbaza
{
protected:
	const int id;
	double interactiuni;
	float temperaturaSenzor;
	float opriri;
	int resetari;
	double durataViata;
	string locatie;
	char* identificare;
	int raspunsInteractiune;
	bool conectat;
	bool expusLaApa;
	double pret;
	static int nrSenzori;
public:
	//constructori si operatorul=
	senzorbaza(): id(103)
	{
		nrSenzori++;
		this->interactiuni = 0;
		this->resetari = 0;
		this->durataViata = 0;
		this->opriri = 0;
		this->temperaturaSenzor = 20;
		this->locatie = "neidentificat";
		this->identificare = new char[strlen("A14141") + 1];
		strcpy_s(this->identificare, strlen("A14141") + 1, "A14141");
		this->raspunsInteractiune = 0;
		this->conectat = false;
		this->expusLaApa = false;
		this->pret = 20; //daca esti fraier, platesti pe nimic
	}
	senzorbaza(const int i, double interactiune,float temperaturasenzor,float op, int resetare, double durata, string loca,
	const char* ident, int raspuns, bool conec,bool ex, double p) : id(i)
	{
		nrSenzori++;
		this->interactiuni = interactiune;
		this->resetari = resetare;
		this->opriri = op;
		this->durataViata = durata;
		this->temperaturaSenzor = temperaturasenzor;
		this->locatie = loca;
		this->identificare = new char[strlen(ident) + 1];
		strcpy_s(this->identificare, strlen(ident) + 1, ident);
		this->raspunsInteractiune = raspuns;
		this->conectat = conec;
		this->expusLaApa = ex;
		this->pret = p;
	}
	senzorbaza(const senzorbaza& s) : id(s.id)
	{
		nrSenzori++;
		this->interactiuni = s.interactiuni;
		this->opriri = s.opriri;
		this->resetari = s.resetari;
		this->durataViata = s.durataViata;
		this->temperaturaSenzor = s.temperaturaSenzor;
		this->locatie = s.locatie;
		this->identificare = new char[strlen(s.identificare) + 1];
		strcpy_s(this->identificare, strlen(s.identificare) + 1, s.identificare);
		this->raspunsInteractiune = s.raspunsInteractiune;
		this->conectat = s.conectat;
		this->pret = s.pret;
	}

	senzorbaza operator=(const senzorbaza& s)
	{

		this->interactiuni = s.interactiuni;
		this->opriri = s.opriri;
		this->resetari = s.resetari;
		this->durataViata = s.durataViata;
		this->locatie = s.locatie;
		this->temperaturaSenzor = s.temperaturaSenzor;
		if (identificare)
			delete[] this->identificare;
		this->identificare = new char[strlen(s.identificare) + 1];
		strcpy_s(this->identificare, strlen(s.identificare) + 1, s.identificare);
		this->raspunsInteractiune = s.raspunsInteractiune;
		this->conectat = s.conectat;
		this->pret = s.pret;
		return *this;

	}
	~senzorbaza()
	{
		if (identificare)
			delete[] this->identificare;
	}
	//getteri si setteri
	void setPret(double p)
	{
		this->pret = p;
	}
	void setExpusLaApa(bool ex)
	{
		this->expusLaApa = ex;
	}
	void setInteractiuni(double i)
	{
		this->interactiuni = i;
	}
	void setOpriri(float o)
	{
		this->opriri = o;
	}
	void setResetari(int r)
	{
		this->resetari = r;
	}
	void setDurataViata(double dv)
	{
		this->durataViata = dv;
	}
	void setLocatie(string l)
	{
		this->locatie = l;
	}
	void setIdentificare(const char* iden)
	{
		if (identificare)
			delete[] this->identificare;
		this->identificare = new char[strlen(iden) + 1];
		strcpy_s(this->identificare, strlen(iden) + 1, iden);
	}
	void setRaspunsInteractiune(int ri)
	{
		this->raspunsInteractiune = ri;

	}
	void setTemperatura(float ts)
	{
		this->temperaturaSenzor = ts;
	}
	void setConectat(bool con)
	{
		this->conectat = con;
	}
	double getPret()
	{
		return this->pret;
	}
	bool getExpusLaApa()
	{
		return this->expusLaApa;
	}
	double getInteractiuni()
	{
		return this->interactiuni;
	}
	float getOpriri()
	{
		return this->opriri;
	}
	int getResetari()
	{
		return this->resetari;
	}
	float getTemepraturaSenzor()
	{
		return this->temperaturaSenzor;
	}
	double getDurataViata()
	{
		return this->durataViata;
	}
	string getLocatie()
	{
		return this->locatie;
	}
	char* getIdentificare()
	{
		return this->identificare;
	}
	int getRaspunsInteractiune()
	{
		return this->raspunsInteractiune;
	}

	bool getConectat()
	{
		return this->conectat;
	}
	
	const int getID()
	{
		return id;
	}
	static int getNrSenzori()
	{
		return nrSenzori;
	}
	//metoda
	void esteIdentificat()
	{
		if (strlen(identificare) != 6)
			throw new exception("Codul de inregistrare in sistemul IoT trebuie sa fie de 6 caractere!");
		else
		{
			for (int i = 0; i < strlen(identificare); i++)
				if (identificare[i] >= 'a' && identificare[i] <= 'z')
					throw new exception("Codul de inregistrare nu poate avea decat litere mari de tipar");
		}
		if (strlen(identificare) == 6)
		{
			if ((identificare[0] >= 'A' && identificare[0] <= 'Z')&& (identificare[1] >= 'A' && identificare[1] <= 'Z'))
			    {
					int ok = 1;
					for (int i = 2; i < strlen(identificare); i++)
						if (identificare[i] <= '0' && identificare[i] >= '9')
							ok = 0;
					if (ok == 1)
						throw new apartinesistem("Codul de inregistrare exista, deci senzorul apartine in sistemul IoT.");
						if (ok == 0)
							throw new apartinesistem();
				}
				else
					throw new apartinesistem();
		}
	}
	//supraincarcare operatori
	bool operator>(const senzorbaza& b)
	{
		if (this->raspunsInteractiune > b.raspunsInteractiune)
		{
			return this->raspunsInteractiune > b.raspunsInteractiune;
		}
	}
	bool operator<(const senzorbaza& b)
	{
		if (this->interactiuni < b.interactiuni)
		{
			return this->interactiuni < b.interactiuni;
		}
	}
	senzorbaza& operator--(int)
	{
		this->resetari--;
		return *this;
	}
	senzorbaza operator*(int val)
	{
		raspunsInteractiune = raspunsInteractiune * val;
		return* this;
	}
	int& operator()()
	{
		return this->resetari;
	}

	friend ostream& operator<<(ostream& out, const senzorbaza& s)
	{
		out << "Senzorul cu codul " << s.id << " a avut parte de " << s.interactiuni << " interactiuni luna aceasta." << endl;
		out << "Dupa fiecare interactiune, acesta s-a oprit automat de fiecare data, avand " << s.opriri << " opriri." << endl;
		out <<"Acest senzor a fost resetat de " << s.resetari << " ori:" << endl;
		out << "Acesta functioneaza de " << s.durataViata << " si se afla " << s.locatie << endl;
		out << endl << "De asemenea acesta dispune de o viteza de reactie de " << s.raspunsInteractiune << " milisecunde";
		out << endl << " si costa " << s.pret << " de lei";
		out << endl << "In sistemul Iot, acest senzor este identificat cu codul: " << s.identificare;
		if (s.conectat)
			out << "Senzorul functioneaza in parametrii normali.";
		else
			out << "Senzorul este oprit/defect.";
		return out;
	}
	friend istream& operator>>(istream& in, senzorbaza& s)
	{
		cout << "instrocueti numarul de interactiuni:" << endl;
		in >> s.interactiuni;
		cout << "introduceti numarul de opriri:" << endl;
		in >> s.opriri;
		cout << "Introduceti temperatura senzorului:" << endl;
		in >> s.temperaturaSenzor;
		cout << "introduceti numarul de resetari care au avut lo aceasta luna: " << endl;
		in >> s.resetari;
		cout << " introduceti durata de viata a sensorului:" << endl;
		in >> s.durataViata;
		cout << "introduceti pozitia acestuia: " << endl;
		in.ignore();
		getline(in, s.locatie);
		in.ignore();
		char cod[25];
		in.getline(cod, 25);
		if (s.identificare)
			delete[] s.identificare;
		s.identificare = new char[strlen(cod) + 1];
		strcpy_s(s.identificare, strlen(cod) + 1, cod);
		cout << "Introduceti timpul de reactie in milisecunde:" << endl;
		in >> s.raspunsInteractiune;
		cout << "Vedem daca este conectat sau nu:" << endl;
		in >> s.conectat;
		cout << "Stabiliti pretul senzorului:" << endl;
		in >> s.pret;
		return in;
	}
	friend ofstream& operator<<(ofstream& fout, const senzorbaza& s)
	{
		fout << "Senzorul cu codul " << s.id << " a avut parte de " << s.interactiuni << " interactiuni luna aceasta." << endl;
		fout << "Dupa fiecare interactiune, acesta s-a oprit automat de fiecare data, avand " << s.opriri << " opriri." << endl;
		fout << "Acest sezor a fost resetat de " << s.resetari << " ori:" << endl;
		fout << "Acesta functioneaza de " << s.durataViata << " si se afla " << s.locatie << endl;
		fout << endl << "De asemenea acesta dispune de o viteza de reactie de " << s.raspunsInteractiune << " milisecunde";
		fout << endl << " si costa " << s.pret << " de lei";
		fout << endl << "In sistemul Iot, acest senzor este identificat cu codul: " << s.identificare;
		if (s.conectat)
			fout << "Senzorul functioneaza in parametrii normali.";
		else
			fout << "Senzorul este oprit/defect.";
		return fout;
	}
	friend ifstream& operator>>(ifstream& fin, senzorbaza& s)
	{
		fin >> s.interactiuni;
		fin >> s.opriri;
		fin >> s.temperaturaSenzor;
		fin >> s.resetari;
		fin >> s.durataViata;
		fin.ignore();
		getline(fin, s.locatie);
		fin.ignore();
		char cod[25];
		fin.getline(cod, 25);
		if (s.identificare)
			delete[] s.identificare;
		s.identificare = new char[strlen(cod) + 1];
		strcpy_s(s.identificare, strlen(cod) + 1, cod);
		fin >> s.raspunsInteractiune;
		fin >> s.conectat;
		fin >> s.pret;
		return fin;
	}
};
int senzorbaza::nrSenzori = 0;

class senzortemperatura :public senzorbaza, public functiiconectare
{
	char* detaliiTehnice;
	int temperaturaMinima;
	int temperaturaMaxima;
	double* istoric;
	 string culoare;
	bool rezistent;
public:
	senzortemperatura() :senzorbaza(), culoare("gri generic")
	{
		this->temperaturaMinima = -10;
		this->temperaturaMaxima = 40;
		this->detaliiTehnice = new char[strlen("nu avem detalii") + 1];
		strcpy_s(this->detaliiTehnice, strlen("nu avem detalii") + 1, "nu avem detalii");
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = 0.0;
		this->rezistent = true;
	}
	senzortemperatura(const char* dt, int tmin, int tmax, double* is, string cul, bool r):
		senzorbaza(201,3,20,3,1,3,"in bucatarie","CF1013",1,true, false,45), culoare(cul)
	{
		this->temperaturaMinima = tmin;
		this->temperaturaMaxima = tmax;
		this->detaliiTehnice = new char[strlen(dt) + 1];
		strcpy_s(this->detaliiTehnice, strlen(dt) + 1, dt);
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = is[i];
		this->rezistent = r;
	}
	senzortemperatura(const char* dt, int tmin, int tmax, double *is, string cul, bool r, const int i, double interactiune, 
		float temperaturasenzor,float oprire,int resetare, double durata, string loca, const char* ident,
		int raspuns, bool conec, bool ex,double p) :
		senzorbaza( i, interactiune,temperaturasenzor,oprire,  resetare, durata, loca,
			 ident, raspuns, conec,ex,p), culoare(cul)
	{
		this->temperaturaMinima = tmin;
		this->temperaturaMaxima = tmax;
		this->detaliiTehnice = new char[strlen(dt) + 1];
		strcpy_s(this->detaliiTehnice, strlen(dt) + 1, dt);
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = is[i];
		this->rezistent = r;
	}
	senzortemperatura(const senzortemperatura& szt) : senzorbaza(szt), culoare(szt.culoare)
	{
		this->temperaturaMinima = szt.temperaturaMinima;
		this->temperaturaMaxima = szt.temperaturaMaxima;
		this->detaliiTehnice = new char[strlen(szt.detaliiTehnice) + 1];
		strcpy_s(this->detaliiTehnice, strlen(szt.detaliiTehnice) + 1, szt.detaliiTehnice);
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = szt.istoric[i];
		this->rezistent = szt.rezistent;
	}
	senzortemperatura operator=(const senzortemperatura& szt)
	{
		senzorbaza::operator=(szt);
		this->temperaturaMinima = szt.temperaturaMinima;
		this->temperaturaMaxima = szt.temperaturaMaxima;
		if (detaliiTehnice)
			delete[] this->detaliiTehnice;
		this->detaliiTehnice = new char[strlen(szt.detaliiTehnice) + 1];
		strcpy_s(this->detaliiTehnice, strlen(szt.detaliiTehnice) + 1, szt.detaliiTehnice);
		if (istoric)
			delete[] this->istoric;
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = szt.istoric[i];
		this->rezistent = szt.rezistent;
		return* this;
	}
	~senzortemperatura()
	{
		if(detaliiTehnice)
		delete[] this->detaliiTehnice;
		if(istoric)
		delete[] this->istoric;
	}
	//metoda pentru functiile virtuale
	void conecteaza()
	{
		this->conectat = true;
		this->interactiuni++;
		double rezultat;
		cin >> rezultat;
		int j = interactiuni;
		this->istoric[j - 1] = rezultat;
		cin.ignore();
		char cul[50];
		cin.getline(cul, 50);
		this->culoare = cul;
		int temp = 20;
		if (temp > this->temperaturaSenzor)
		{
			this->temperaturaSenzor = temp;
		}
		else
			if (temp == this->temperaturaSenzor)
			{
				this->temperaturaSenzor = temp + 3;
			}
			else
			{
				setTemperatura(this->temperaturaSenzor + 3);
			}
	}
	void deconecteaza()
	{
		if (this->temperaturaSenzor > 45)
			rezistent = false;
		if (expusLaApa)
			this->rezistent = false;
		if (rezistent)
		{
			this->conectat = false;
			this->opriri++;
		}
		else
		{
			this->conectat = false;
			this->resetari++;
			this->opriri++;
		}
		char cul[50];
		cin.getline(cul, 50);
		this->culoare = cul;
	}
	void profil()
	{
		ofstream fout("Rezultat.txt");
		//afisam culoarea de dupa aprindere
		fout << "La aprindere, senzorul are o culoare de " << culoare << endl;
		//introducem o raza de actiune
		int razaDeActiuneLungime = 0;
		int razaDeActiuneLatime = 0;
		bool razaSiLaEtaj;
		cin >> razaDeActiuneLungime;
		cin >> razaDeActiuneLatime;
		cin >> razaSiLaEtaj;
		if (razaDeActiuneLatime <= 15 && razaDeActiuneLungime <= 25)
		{
			fout << "Senzorul poate actiona doar intr-o camera!" << endl;
		}
		else
			if (razaDeActiuneLatime <= 35 && razaDeActiuneLungime <= 50)
			{
				fout << "Senzorul are raza de actiune in 3 camere!" << endl;
			}
			else
				if (razaDeActiuneLatime > 35 && razaDeActiuneLungime > 50 && razaSiLaEtaj == true)
				{
					fout << "Senzorul are raza de actiune in toata casa!" << endl;
				}
		//verificam forma senzorului
		int ok = 1;
		double dimensiuni[3];
		for (int i = 0; i < 3; i++)
			cin >> dimensiuni[i];
		for (int i = 1; i < 3; i++)
		{
			if (dimensiuni[i] != dimensiuni[i - 1])
				ok = 0;
		}
		if (ok == 1)
		{
			fout << "Senzorul are forma de cub!" << endl;
		}
		else
		{
			fout << "Senzorul are forma de pararelipiped!" << endl;
		}
		//verificam daca e pe baza de baterii sau nu
		bool areBaterii;
		cin >> areBaterii;
		if (areBaterii)
		{
			fout << "Senzorul merge pe baza bateriilor incarcabile/ nereincarcabile!" << endl;
		}
		else
		{
			fout << "Senzorul trebuie conectat la o priza!" << endl;
		}
		//vedem cat de performant este
		if (temperaturaMinima == 15 && temperaturaMaxima == 30)
		{
			fout << "Utilitatea senzorului este limitata la a inregistra caldura generala din camera! " << endl;
		}
		else
			if ((temperaturaMinima >= -10 &&temperaturaMinima<=15)&& (temperaturaMaxima <= 40&&temperaturaMaxima>=30))
			{
				fout << "Senzorul acesta de temperatura poate verifica majoritatea temperaturilor care ar putea fi intr-o clasa  !" << endl;
			}
			else
				if ((temperaturaMaxima <= 80&&temperaturaMaxima>=40 )&& (temperaturaMinima >= -30&&temperaturaMinima<=-10))
				{
					fout << "Senzorul poate prinde valori extreme de temperatura! Cu ajutorul lui putem depista daca exista pericole! " << endl;
				}
				else
				{
					fout << "Nu se incadreaza in parametrii cunoscuti!";
				}
	}
	//metoda
	double valoriMedii()
	{
		double med = 0;
		for (int i = 0; i < this->interactiuni; i++)
			med = med + istoric[i];
		med = med / interactiuni;
		return med;
	}
	//getteri si setteri
	void setTemperaturaMinima(int tmin)
	{
		this->temperaturaMinima = tmin;
	}
	void setTemperaturaMaxima(int tmax)
	{
		this->temperaturaMaxima = tmax;
	}
	void setDetaliiTehnice(const char* d)
	{
		if (detaliiTehnice)
			delete[] this->detaliiTehnice;
		this->detaliiTehnice = new char[strlen(d) + 1];
		strcpy_s(this->detaliiTehnice, strlen(d) + 1, d);
	}
	void setIstoric(double* is, int interac)
	{
		if (istoric)
			delete[] this->istoric;
		this->istoric = new double[interac];
		for (int i = 0; i < interac; i++)
			this->istoric[i] = is[i];
	}
	void setRezistent(bool rez)
	{
		this->rezistent = rez;
	}
	char* getDetaliiTehnice()
	{
		return this->detaliiTehnice;
	}
	double* getIstoric()
	{
		return this->istoric;
	}
	const string getCuloare()
	{
		return this->culoare;
	}
	int getTemperaturaMinima()
	{
		return this->temperaturaMinima;
	}
	int getTemperaturaMaxima()
	{
		return this->temperaturaMaxima;
	}
	bool getRezistent()
	{
		return this->rezistent;
	}
	//operatori supraincarcati
	senzortemperatura operator+(const senzortemperatura& s)
	{
		senzortemperatura szb = *this;
		szb.pret = this->pret + s.pret;
		return szb;
	}
	explicit operator double()
	{
		return valoriMedii();
	}
	senzortemperatura operator++(int)
	{
		senzortemperatura aux = *this;
		double* is = new double[this->interactiuni];
		for (int i = 0; i < this->interactiuni; i++)
			is[i] = aux.istoric[i] + 1;
		delete[] this->istoric;
		this->istoric = is;
		return *this;
	}
	double& operator[](int index)
	{
		if (index >= 0 && index < interactiuni)
			return this->istoric[index];
		else
			throw "Indexul nu exista in instoricul acesta!";
	}
	explicit operator int()
	{
		return this->temperaturaMinima;
	}
	senzortemperatura operator-(int val) {
		
		this->temperaturaMaxima = temperaturaMaxima - val;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const senzortemperatura& szt)
	{
		out << senzorbaza(szt);
		out << "Se pot afla urmatoarele date despre acest senzor: "<< szt.detaliiTehnice << endl;
		out << "Senzorul poate inregistra o valoare minima de " << szt.temperaturaMinima << " si una maxima de " << szt.temperaturaMaxima << endl;
		out << "In interactiunile sale acest senzor a inregistrat urmatoarele rezultate:" << endl;
		for (int i = 0; i < szt.interactiuni; i++)
			out << szt.istoric[i] << ", ";
		out << endl;
		out << endl << "Nu in ultimul rand, atunci cand se porneste, senzorul are culoarea " << szt.culoare;
		if (szt.rezistent)
			out << endl << "De asemenea, senzorul este cu adevarat durabil.";
		else
			out << endl << "Din nefericire, acest senzor nu are o durabilitate prea mare";
		return out;
	}
	friend istream& operator>>(istream& in, senzortemperatura& szt)
	{
		in >> (senzorbaza&)szt;
		char inf[255];
		if (szt.detaliiTehnice)
			delete[] szt.detaliiTehnice;
		in.ignore();
		in.getline(inf, 255);
		szt.detaliiTehnice = new char[strlen(inf) + 1];
		strcpy_s(szt.detaliiTehnice, strlen(inf) + 1, inf);
		if (szt.istoric)
			delete[] szt.istoric;
		szt.istoric = new double[szt.interactiuni];
		for (int i = 0; i < szt.interactiuni; i++)
			in >> szt.istoric[i];
		in >> szt.temperaturaMinima;
		in >> szt.temperaturaMaxima;
		in.ignore();
		getline(in, szt.culoare);
		in >> szt.rezistent;
		return in;
	}
	friend ofstream& operator<<(ofstream& fout, const senzortemperatura& szt)
	{
		fout << senzorbaza(szt);
		fout << "Se pot afla urmatoarele date despre acest senzor: " << szt.detaliiTehnice << endl;
		fout << "Senzorul poate inregistra o valoare minima de " << szt.temperaturaMinima << " si una maxima de " << szt.temperaturaMaxima << endl;
		fout << "In interactiunile sale acest senzor a inregistrat urmatoarele rezultate:" << endl;
		for (int i = 0; i < szt.interactiuni; i++)
			fout << szt.istoric[i] << ", ";
		fout << endl;
		fout << endl << "Nu in ultimul rand, atunci cand se porneste, senzorul are culoarea " << szt.culoare;
		if (szt.rezistent)
			fout << endl << "De asemenea, senzorul este cu adevarat durabil.";
		else
			fout << endl << "Din nefericire, acest senzor nu are o durabilitate prea mare";
		return fout;
	}
	friend ifstream& operator>>(ifstream& fin, senzortemperatura& szt)
	{
		fin >> (senzorbaza&)szt;
		char inf[255];
		if (szt.detaliiTehnice)
			delete[] szt.detaliiTehnice;
		fin.ignore();
		fin.getline(inf, 255);
		szt.detaliiTehnice = new char[strlen(inf) + 1];
		strcpy_s(szt.detaliiTehnice, strlen(inf) + 1, inf);
		if (szt.istoric)
			delete[] szt.istoric;
		szt.istoric = new double[szt.interactiuni];
		for (int i = 0; i < szt.interactiuni; i++)
			fin >> szt.istoric[i];
		fin >> szt.temperaturaMinima;
		fin >> szt.temperaturaMaxima;
		fin.ignore();
		getline(fin, szt.culoare);
		fin >> szt.rezistent;
		return fin;
		
	}
};
class senzorumiditate :public senzorbaza, public functiiconectare
{
	char* detaliiTehnice;
	int umiditateMinima;
	int umiditateMaxima;
	double* istoric;
    string culoare;
	bool rezistent;
	bool alerta;
public:
	senzorumiditate() :senzorbaza(), culoare("albastru neaprins")
	{
		this->umiditateMinima = 0;
		this->umiditateMaxima = 100;
		this->detaliiTehnice = new char[strlen("nu avem detalii") + 1];
		strcpy_s(this->detaliiTehnice, strlen("nu avem detalii") + 1, "nu avem detalii");
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = 0.0;
		this->rezistent = true;
		this->alerta = false;
	}
	senzorumiditate(const char* dt, int umin, int umax, double* is, string cul, bool r, bool a) :
		senzorbaza(404, 5,25,5, 0, 2, "in hol , la etaj", "BD1010", 1, true,false,57), culoare(cul)
	{
		this->umiditateMinima = umin;
		this->umiditateMaxima = umax;
		this->detaliiTehnice = new char[strlen(dt) + 1];
		strcpy_s(this->detaliiTehnice, strlen(dt) + 1, dt);
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = is[i];
		this->rezistent = r;
		this->alerta = a;
	}
	senzorumiditate(const char* dt, int umin, int umax, double* is, string cul, bool r,bool a, 
		const int i, double interactiune, float temperaturasenzor, float op, int resetare, double durata, string loca,
		const char* ident, int raspuns, bool conec, bool ex, double p) :
		senzorbaza(i, interactiune, temperaturasenzor, op, resetare, durata, loca,
			ident, raspuns, conec,ex,p)
	{
		this->umiditateMinima = umin;
		this->umiditateMaxima = umax;
		this->detaliiTehnice = new char[strlen(dt) + 1];
		strcpy_s(this->detaliiTehnice, strlen(dt) + 1, dt);
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = is[i];
		this->rezistent = r;
		this->alerta = a;
	}
	senzorumiditate(const senzorumiditate& szt) : senzorbaza(szt), culoare(szt.culoare)
	{
		this->umiditateMinima = szt.umiditateMinima;
		this->umiditateMaxima = szt.umiditateMaxima;
		this->detaliiTehnice = new char[strlen(szt.detaliiTehnice) + 1];
		strcpy_s(this->detaliiTehnice, strlen(szt.detaliiTehnice) + 1, szt.detaliiTehnice);
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = szt.istoric[i];
		this->rezistent = szt.rezistent;
		this->alerta = szt.alerta;
	}
	senzorumiditate operator=(const senzorumiditate& szt)
	{
		senzorbaza::operator=(szt);
		this->umiditateMinima = szt.umiditateMinima;
		this->umiditateMaxima = szt.umiditateMaxima;
		if (detaliiTehnice)
			delete[] this->detaliiTehnice;
		this->detaliiTehnice = new char[strlen(szt.detaliiTehnice) + 1];
		strcpy_s(this->detaliiTehnice, strlen(szt.detaliiTehnice) + 1, szt.detaliiTehnice);
		if (istoric)
			delete[] this->istoric;
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = szt.istoric[i];
		this->rezistent = szt.rezistent;
		this->alerta = szt.alerta;
		return*this;
	}
	~senzorumiditate()
	{
		if (detaliiTehnice)
			delete[] this->detaliiTehnice;
		if (istoric)
			delete[] this->istoric;
	}
	//metoda pentru functiile virtuale
	void conecteaza()
	{
		this->conectat = true;
		this->interactiuni++;
		double rezultat;
		cin >> rezultat;
		int j = interactiuni;
		this->istoric[j - 1] = rezultat;
		char cul[50];
		cin.getline(cul, 50);
		this->culoare = cul;
		int temp = 20;
		if (temp > this->temperaturaSenzor)
		{
			this->temperaturaSenzor = temp;
		}
		else
			if (temp ==this-> temperaturaSenzor)
			{
				this->temperaturaSenzor = temp + 3;
			}
			else
			{
				setTemperatura(this->temperaturaSenzor + 3);
			}
	}
	void deconecteaza()
	{
		if (this->temperaturaSenzor > 45)
			rezistent = false;
		if (expusLaApa)
			this->rezistent = false;
		if (rezistent)
		{
			this->conectat = false;
			this->opriri++;
		}
		else
		{
			this->conectat = false;
			this->resetari++;
			this->opriri++;
		}
			char cul[50];
			cin.getline(cul, 50);
			this->culoare = cul;
	}
	void profil()
	{
		ofstream fout("Rezultate.txt");
		//executie consecinta interactiune noua
		setTemperatura(temperaturaSenzor + 3);
		//afisam culoarea de dupa aprindere
		fout << "La aprindere, senzorul are o culoare de " << culoare << endl;
		//introducem o raza de actiune
		int razaDeActiuneLungime = 0;
		int razaDeActiuneLatime = 0;
		bool razaSiLaEtaj;
		cin >> razaDeActiuneLungime;
		cin >> razaDeActiuneLatime;
		cin >> razaSiLaEtaj;
		if (razaDeActiuneLatime <= 15 && razaDeActiuneLungime <= 25)
		{
			fout << "Senzorul poate actiona doar intr-o camera!" << endl;
		}
		else
			if (razaDeActiuneLatime <= 35 && razaDeActiuneLungime <= 50)
			{
				fout << "Senzorul are raza de actiune in 3 camere!" << endl;
			}
			else
				if (razaDeActiuneLatime > 35 && razaDeActiuneLungime > 50 && razaSiLaEtaj == true)
				{
					fout << "Senzorul are raza de actiune in toata casa!" << endl;
				}
		//verificam forma senzorului
		int ok = 1;
		double dimensiuni[3];
		for (int i = 0; i < 3; i++)
			cin >> dimensiuni[i];
		for (int i = 1; i < 3; i++)
		{
			if (dimensiuni[i] != dimensiuni[i - 1])
				ok = 0;
		}
		if (ok == 1)
		{
			fout << "Senzorul are forma de cub!" << endl;
		}
		else
		{
			fout << "Senzorul are forma de pararelipiped!" << endl;
		}
		//verificam daca e pe baza de baterii sau nu
		bool areBaterii;
		cin >> areBaterii;
		if (areBaterii)
		{
			fout << "Senzorul merge pe baza bateriilor incarcabile/ nereincarcabile!" << endl;
		}
		else
		{
			fout << "Senzorul trebuie conectat la o priza!" << endl;
		}
		//vedem cat de performant este
		if (umiditateMinima == 25 && umiditateMaxima == 50)
		{
			fout << "Senzorul are limitari tehnice severe! Utilitatea lui este limitata! " << endl;
		}
		else
			if ((umiditateMinima >= 10&&umiditateMinima<=25 )&& (umiditateMaxima <= 70&&umiditateMaxima>=50))
			{
				fout << "Senzorul acesta de umiditate poate fi folosit in majoritatea situatilor!" << endl;
			}
			else
				if ((umiditateMaxima<=100&&umiditateMaxima>=70)&&(umiditateMinima>=0&&umiditateMinima<=10))
				{
					fout << "Senzorul poate prinde orice nivel de umiditate! Este bun in orice situatie!" << endl;
				}
				else
				{
					fout << "Nu se poate incadra in calculele noastre!" << endl;
				}
	}
	//metoda
	void verificareSiguranta()
	{
		int ok = 1;
		for(int i=0;i<interactiuni;i++)
			if (this->istoric[i] > 60 && this->istoric[i] < 30)
			{
				ok = 0;
			}
		if (ok == 0)
		{
			this->alerta = true;
			cout << "Umiditatea nu este in parametrii optimi. Asigurati-va ca totul este in regula.";
		}
	}
	//getteri si setteri
	void setUmiditateMinima(int tmin)
	{
		this->umiditateMinima = tmin;
	}
	void setUmiditateMaxima(int tmax)
	{
		this->umiditateMaxima = tmax;
	}
	void setDetaliiTehnice(const char* d)
	{
		if (detaliiTehnice)
			delete[] this->detaliiTehnice;
		this->detaliiTehnice = new char[strlen(d) + 1];
		strcpy_s(this->detaliiTehnice, strlen(d) + 1, d);
	}
	void setIstoric(double* is, int interac)
	{
		if (istoric)
			delete[] this->istoric;
		this->istoric = new double[interac];
		for (int i = 0; i < interac; i++)
			this->istoric[i] = is[i];
	}
	void setRezistent(bool rez)
	{
		this->rezistent = rez;
	}
	void setAlerta(bool a)
	{
		this->alerta = a;
	}
	char* getDetaliiTehnice()
	{
		return this->detaliiTehnice;
	}
	double* getIstoric()
	{
		return this->istoric;
	}
	const string getCuloare()
	{
		return this->culoare;
	}
	int getUmiditateMinima()
	{
		return this->umiditateMinima;
	}
	int getUmiditateMaxima()
	{
		return this->umiditateMaxima;
	}
	bool getRezistent()
	{
		return this->rezistent;
	}
	bool getAlerta()
	{
		return this->alerta;
	}
	//operatori supraincarcati
	senzorumiditate operator+(const senzorumiditate& s)
	{
		senzorumiditate szb = *this;
		double pret = 0;
		szb.pret = this->pret + s.pret;
		return szb;
	}
	senzorumiditate operator++()
	{
		senzorumiditate aux = *this;
		for (int i = 0; i < this->getInteractiuni(); i++)
		{
			aux.istoric[i] = aux.istoric[i] + 5;
		}
		return aux;
	}
	char& operator[](int index)
	{
		if (index > 0 && index < strlen(detaliiTehnice))
			return this->detaliiTehnice[index];
		else
			throw "Aici nu avem text!";
	}
	senzorumiditate operator+=(int val)
	{
		this->umiditateMaxima = umiditateMaxima + val;
		return *this;
	}
	bool operator==(const senzorumiditate& szu)
	{
		if (this->umiditateMaxima == szu.umiditateMaxima && this->umiditateMinima == szu.umiditateMinima)
			return true;
		else
			return false;
	}
	 bool operator!()
	{
		 verificareSiguranta();
		 if (alerta == true)
			 return true;
		 else
			 return false;

	}
	friend ostream& operator<<(ostream& out, const senzorumiditate& szt)
	{
		out << senzorbaza(szt);
		out << "Se pot afla urmatoarele date despre acest senzor: " << szt.detaliiTehnice << endl;
		out << "Senzorul poate inregistra o valoare minima de " << szt.umiditateMinima << " si una maxima de " << szt.umiditateMaxima << endl;
		out << "In interactiunile sale acest senzor a inregistrat urmatoarele rezultate:" << endl;
		for (int i = 0; i < szt.interactiuni; i++)
			out << szt.istoric[i] << ", ";
		out << endl;
		out << endl << "Nu in ultimul rand, atunci cand se porneste, senzorul are culoarea " << szt.culoare;
		if (szt.rezistent)
			out << endl << "De asemenea, senzorul este cu adevarat durabil.";
		else
			out << endl << "Din nefericire, acest senzor nu are o durabilitate prea mare";
		if (szt.alerta==false)
			out << endl << "Camera se afla in parametrii normail de umiditate.";
		else
			out << endl << "Trebuie luate masuri urgente.";
		return out;
	}
	friend istream& operator>>(istream& in, senzorumiditate& szt)
	{
		in >> (senzorbaza&)szt;
		cout << " descrieti din punct de vedere tehnic produsul:" << endl;
		char inf[255];
		if (szt.detaliiTehnice)
			delete[] szt.detaliiTehnice;
		in.ignore();
		in.getline(inf, 255);
		szt.detaliiTehnice = new char[strlen(inf) + 1];
		strcpy_s(szt.detaliiTehnice, strlen(inf) + 1, inf);
		cout << "Introduceti datele inregistrate in senzor la fiecare interactiune: " << endl;
		if (szt.istoric)
			delete[] szt.istoric;
		szt.istoric = new double[szt.interactiuni];
		for (int i = 0; i < szt.interactiuni; i++)
			in >> szt.istoric[i];
		cout << "Te rog adauga valoarea maxima si minima pe care o poate inregistra aparatul:";
		in >> szt.umiditateMinima;
		in >> szt.umiditateMaxima;
		cout << "Sa confirmam faptul ca acest senzor este durabil:";
		in >> szt.rezistent;
		cout << "Este totul ok?";
		in >> szt.alerta;
		return in;
	}
	friend ofstream& operator<<(ofstream& fout, const senzorumiditate& szt)
	{
		fout << senzorbaza(szt);
		fout << "Se pot afla urmatoarele date despre acest senzor: " << szt.detaliiTehnice << endl;
		fout << "Senzorul poate inregistra o valoare minima de " << szt.umiditateMinima << " si una maxima de " << szt.umiditateMaxima << endl;
		fout << "In interactiunile sale acest senzor a inregistrat urmatoarele rezultate:" << endl;
		for (int i = 0; i < szt.interactiuni; i++)
			fout << szt.istoric[i] << ", ";
		fout << endl;
		fout << endl << "Nu in ultimul rand, atunci cand se porneste, senzorul are culoarea " << szt.culoare;
		if (szt.rezistent)
			fout << endl << "De asemenea, senzorul este cu adevarat durabil.";
		else
			fout << endl << "Din nefericire, acest senzor nu are o durabilitate prea mare";
		if (szt.alerta==false)
			fout << endl << "Camera se afla in parametrii normail de umiditate.";
		else
			fout << endl << "Trebuie luate masuri urgente.";
		return fout;
	}
	friend ifstream& operator>>(ifstream& fin, senzorumiditate& szt)
	{
		fin >> (senzorbaza&)szt;
		char inf[255];
		if (szt.detaliiTehnice)
			delete[] szt.detaliiTehnice;
		fin.ignore();
		fin.getline(inf, 255);
		szt.detaliiTehnice = new char[strlen(inf) + 1];
		strcpy_s(szt.detaliiTehnice, strlen(inf) + 1, inf);
		if (szt.istoric)
			delete[] szt.istoric;
		szt.istoric = new double[szt.interactiuni];
		for (int i = 0; i < szt.interactiuni; i++)
			fin >> szt.istoric[i];
		fin >> szt.umiditateMinima;
		fin >> szt.umiditateMaxima;
		fin.ignore();
		getline(fin, szt.culoare);
		fin >> szt.rezistent;
		return fin;
		fin >> szt.alerta;
		return fin;

	}
};
class senzorCO :public senzorbaza,public functiiconectare
{
	char* detaliiTehnice;
	int coMin;
	int coMax;
	double* istoric;
	string culoare;
	bool rezistent;
	bool alerta;
	double* dimensiuni;
public:
	senzorCO() :senzorbaza(), culoare("gri generic")
	{
		this->coMin = 0;
		this->coMax = 100;
		this->detaliiTehnice = new char[strlen("nu avem detalii") + 1];
		strcpy_s(this->detaliiTehnice, strlen("nu avem detalii") + 1, "nu avem detalii");
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = 0.0;
		this->rezistent = true;
		this->alerta = false;
		this->dimensiuni = new double[3];
		for (int i = 0; i < 3; i++)
			this->dimensiuni[i] = 2.2;
	}
	senzorCO(const char* dt, int comin, int comax, double* is, string cul, bool r, bool a, double* dim) :
		senzorbaza(404, 5,23,5, 0, 2, "in hol , la etaj", "BD1010", 1, true,false,77), culoare(cul)
	{
		this->coMin = comin;
		this->coMax = comax;
		this->detaliiTehnice = new char[strlen(dt) + 1];
		strcpy_s(this->detaliiTehnice, strlen(dt) + 1, dt);
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = is[i];
		this->rezistent = r;
		this->alerta = a;
		this->dimensiuni = new double[3];
		for (int i = 0; i < 3; i++)
			this->dimensiuni[i] = dim[i];
	}
	senzorCO(const char* dt, int comin, int comax, double* is, string cul, bool r,bool a, double*dim, 
		const int i, double interactiune,
		float temperaturasenzor, float oprire, int resetare, double durata, string loca, const char* ident,
		int raspuns, bool conec,bool ex,double p) :
		senzorbaza(i, interactiune, temperaturasenzor, oprire, resetare, durata, loca,
			ident, raspuns, conec,ex,p), culoare(cul)
	{
		this->coMax = comax;
		this->coMin = comin;
		this->detaliiTehnice = new char[strlen(dt) + 1];
		strcpy_s(this->detaliiTehnice, strlen(dt) + 1, dt);
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = is[i];
		this->rezistent = r;
		this->alerta = a;
		this->dimensiuni = new double[3];
		for (int i = 0; i < 3; i++)
			this->dimensiuni[i] = dim[i];
	}
	senzorCO(const senzorCO& szt) : senzorbaza(szt), culoare(szt.culoare)
	{
		this->coMax = szt.coMax;
		this->coMin = szt.coMin;
		this->detaliiTehnice = new char[strlen(szt.detaliiTehnice) + 1];
		strcpy_s(this->detaliiTehnice, strlen(szt.detaliiTehnice) + 1, szt.detaliiTehnice);
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = szt.istoric[i];
		this->rezistent = szt.rezistent;
		this->alerta = szt.alerta;
		this->dimensiuni = new double[3];
		for (int i = 0; i < 3; i++)
			this->dimensiuni[i] = szt.dimensiuni[i];
	}
	senzorCO operator=(const senzorCO& szt)
	{
		senzorbaza::operator=(szt);
		this->coMax = szt.coMax;
		this->coMin = szt.coMin;
		if (detaliiTehnice)
			delete[] this->detaliiTehnice;
		this->detaliiTehnice = new char[strlen(szt.detaliiTehnice) + 1];
		strcpy_s(this->detaliiTehnice, strlen(szt.detaliiTehnice) + 1, szt.detaliiTehnice);
		if (istoric)
			delete[] this->istoric;
		this->istoric = new double[interactiuni];
		for (int i = 0; i < interactiuni; i++)
			this->istoric[i] = szt.istoric[i];
		this->rezistent = szt.rezistent;
		this->alerta = szt.alerta;
		if (dimensiuni)
			delete[] this->dimensiuni;
		this->dimensiuni = new double[3];
		for (int i = 0; i < 3; i++)
			this->dimensiuni[i] = szt.dimensiuni[i];
		return*this;
	}
	~senzorCO()
	{
		if (detaliiTehnice)
			delete[] this->detaliiTehnice;
		if (istoric)
			delete[] this->istoric;
		if (dimensiuni)
			delete[] this->dimensiuni;
	}
	//metoda pentru functiile virtuale
	void conecteaza()
	{
		this->conectat = true;
		this->interactiuni++;
		double rezultat;
		cin >> rezultat;
		int j = interactiuni;
		this->istoric[j - 1] = rezultat;
		char cul[50];
		cin.getline(cul, 50);
		this->culoare = cul;
		this->temperaturaSenzor = 20;
	}
	void deconecteaza()
	{
		if (temperaturaSenzor > 45)
			this->rezistent = false;
		if (expusLaApa)
			this->rezistent = false;
		if (rezistent)
		{
			this->conectat = false;
			this->opriri++;
		}
		else
		{
			this->conectat = false;
			this->resetari++;
			this->opriri++;
		}
		char cul[50];
		cin.getline(cul, 50);
		this->culoare = cul;
	}
	void profil()
	{
		ofstream fout("Rezultate.txt");
		//afisam culoarea de dupa aprindere
		fout << "La aprindere, senzorul are o culoare de " << culoare << endl;
		//introducem o raza de actiune
		int razaDeActiuneLungime = 0;
		int razaDeActiuneLatime = 0;
		bool razaSiLaEtaj;
		cin >> razaDeActiuneLungime;
		cin >> razaDeActiuneLatime;
		cin >> razaSiLaEtaj;
		if (razaDeActiuneLatime <= 15 && razaDeActiuneLungime <= 25)
		{
			fout << "Senzorul poate actiona doar intr-o camera!"<<endl;
		}
		else
			if (razaDeActiuneLatime <= 35 && razaDeActiuneLungime <= 50)
			{
				fout << "Senzorul are raza de actiune in 3 camere!" << endl;
			}
			else
				if (razaDeActiuneLatime > 35 && razaDeActiuneLungime > 50 && razaSiLaEtaj == true)
				{
					fout << "Senzorul are raza de actiune in toata casa!" << endl;
				}
		//verificam forma senzorului
		int ok = 1;
		for (int i = 1; i < 3; i++)
		{
			if (dimensiuni[i] != dimensiuni[i - 1])
				ok = 0;
		}
		if (ok == 1)
		{
			fout << "Senzorul are forma de cub!" << endl;
		}
		else
		{
			fout << "Senzorul are forma de pararelipiped!" << endl;
		}
		//verificam daca e pe baza de baterii sau nu
		bool areBaterii;
		cin >> areBaterii;
		if (areBaterii)
		{
			fout << "Senzorul merge pe baza bateriilor incarcabile/ nereincarcabile!" << endl;
		}
		else
		{
			fout << "Senzorul trebuie conectat la o priza!" << endl;
		}
		//vedem cat de performant este
		if (coMin == 0 && coMax <= 100)
		{
			fout << "Senzorul este bun doar pentru perioade lungi de cateva ore! " << endl;
		}
		else
			if (coMin == 0 && (coMax <= 250&&coMax>=100))
			{
				fout << "Senzorul este bun chiar si pentru reactii mai rapide, gen de 4-8 minute" << endl;
			}
			else
				if(coMin==0&&coMax>250)
			{
					fout << "Senzorul este bun si in cazul in care se intampla ceva imprevizibil!" << endl;
			}
	}
	//metoda
	void verificareSiguranta()
	{
		int ok = 1;
		for (int i = 0; i < interactiuni; i++)
			if (this->istoric[i] > 1000 && this->istoric[i] < 100)
			{
				ok = 0;
			}
		if (ok == 0)
		{
			this->alerta = true;
			cout << "Nivelul de monoxid de carbon este mult prea mare. Parasiti incinta imediat!";
		}
		else
			cout << "Nivelul de monoxid de carbon nu reprezinta un pericol!";
	}
	double getVolum()
	{
		double v = 1;
		for (int i = 0; i < 3; i++)
		{
			v = v * dimensiuni[i];
		}
		return v;
	}
	double getValMin()
	{
		double min = istoric[0];
		for (int i = 1; i < interactiuni; i++)
			if (istoric[i] < min)
				min = istoric[i];
		return min;
	}
	//getteri si setteri
	void setCOmin(int cmin)
	{
		this->coMin = cmin;
	}
	void setCOmax(int cmax)
	{
		this->coMax = cmax;
	}
	void setDetaliiTehnice(const char* d)
	{
		if (detaliiTehnice)
			delete[] this->detaliiTehnice;
		this->detaliiTehnice = new char[strlen(d) + 1];
		strcpy_s(this->detaliiTehnice, strlen(d) + 1, d);
	}
	void setIstoric(double* is, int interac)
	{
		if (istoric)
			delete[] this->istoric;
		this->istoric = new double[interac];
		for (int i = 0; i < interac; i++)
			this->istoric[i] = is[i];
	}
	void setRezistent(bool rez)
	{
		this->rezistent = rez;
	}
	void setAlerta(bool a)
	{
		this->alerta = a;
	}
	void setDimensiuni(double* dim)
	{
		if (dimensiuni)
			delete[] this->dimensiuni;
		this->dimensiuni = new double[3];
		for (int i = 0; i < 3; i++)
			this->dimensiuni[i] = dim[i];
	}
	char* getDetaliiTehnice()
	{
		return this->detaliiTehnice;
	}
	double* getIstoric()
	{
		return this->istoric;
	}
	const string getCuloare()
	{
		return this->culoare;
	}
	int getCOmin()
	{
		return this->coMin;
	}
	int getCOmax()
	{
		return this->coMax;
	}
	bool getRezistent()
	{
		return this->rezistent;
	}
	bool getAlerta()
	{
		return this->alerta;
	}
	double* getDimensiuni()
	{
		return this->dimensiuni;
	}
	//operatori supraincarcati
	senzorCO operator+(const senzorCO& s)
	{
		senzorCO szb = *this;
		szb.pret = this->pret + s.pret;
		return szb;
	}
	senzorCO operator++(int)
	{
		for (int i = 0; i < 3; i++)
			this->dimensiuni[i] = dimensiuni[i] + 2;
		return *this;
	}
	explicit operator double ()
	{
		return this->getValMin();
	}
	double operator()()
	{
		return this->getVolum();
	}
	bool operator!()
	{
		verificareSiguranta();
		if (alerta == true)
			return this->alerta;
		else
			return false;

	}
	senzorCO operator+=(int val)
	{
		this->coMax = coMax + val;
		return *this;
	}
	senzorCO operator-=(int val)
	{
		this->coMin = coMin - val;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const senzorCO& szt)
	{
		out << senzorbaza(szt);
		out << "Se pot afla urmatoarele date despre acest senzor: " << szt.detaliiTehnice << endl;
		out << "Senzorul poate inregistra o valoare minima de " << szt.coMin << " si una maxima de " << szt.coMax << endl;
		out << "In interactiunile sale acest senzor a inregistrat urmatoarele rezultate:" << endl;
		for (int i = 0; i < szt.interactiuni; i++)
			out << szt.istoric[i] << ", ";
		out << endl;
		out << endl << "Nu in ultimul rand, atunci cand se porneste, senzorul are culoarea " << szt.culoare;
		if (szt.rezistent)
			out << endl << "De asemenea, senzorul este cu adevarat durabil.";
		else
			out << endl << "Din nefericire, acest senzor nu are o durabilitate prea mare";
		if (szt.alerta==false)
			out << endl << "Camera se afla in parametrii normail de umiditate.";
		else
			out << endl << "Trebuie luate masuri urgente.";
		out << endl << "Dimensiunile sunzorului sunt urmatoarele:";
		for (int i = 0; i < 3; i++)
			out << szt.dimensiuni[i] << ",";
		return out;
	}
	friend istream& operator>>(istream& in, senzorCO& szt)
	{
		cin >> (senzorbaza&)szt;
		cout << " descrieti din punct de vedere tehnic produsul:" << endl;
		char inf[255];
		if (szt.detaliiTehnice)
			delete[] szt.detaliiTehnice;
		cin.ignore();
		cin.getline(inf, 255);
		szt.detaliiTehnice = new char[strlen(inf) + 1];
		strcpy_s(szt.detaliiTehnice, strlen(inf) + 1, inf);
		cout << "Introduceti datele inregistrate in senzor la fiecare interactiune: " << endl;
		if (szt.istoric)
			delete[] szt.istoric;
		szt.istoric = new double[szt.interactiuni];
		for (int i = 0; i < szt.interactiuni; i++)
			cin >> szt.istoric[i];
		if (szt.dimensiuni)
			delete[] szt.dimensiuni;
		szt.dimensiuni = new double[3];
		for (int i = 0; i < 3; i++)
			cin >> szt.dimensiuni[i];
		cout << "Te rog adauga valoarea maxima si minima pe care o poate inregistra aparatul:";
		cin >> szt.coMax;
		cin >> szt.coMin;
		cout << "Sa confirmam faptul ca acest senzor este durabil:";
		cin >> szt.rezistent;
		cout << "Este totul ok?";
		cin >> szt.alerta;
		return cin;
	}
	friend ofstream& operator<<(ofstream& fout, const senzorCO& szt)
	{
		fout << senzorbaza(szt);
		fout << "Se pot afla urmatoarele date despre acest senzor: " << szt.detaliiTehnice << endl;
		fout << "Senzorul poate inregistra o valoare minima de " << szt.coMin << " si una maxima de " << szt.coMax << endl;
		fout << "In interactiunile sale acest senzor a inregistrat urmatoarele rezultate:" << endl;
		for (int i = 0; i < szt.interactiuni; i++)
			fout << szt.istoric[i] << ", ";
		fout << endl;
		fout << endl << "Nu in ultimul rand, atunci cand se porneste, senzorul are culoarea " << szt.culoare;
		if (szt.rezistent)
			fout << endl << "De asemenea, senzorul este cu adevarat durabil.";
		else
			fout << endl << "Din nefericire, acest senzor nu are o durabilitate prea mare";
		if (szt.alerta==false)
			fout << endl << "Camera se afla in parametrii normail de umiditate.";
		else
			fout << endl << "Trebuie luate masuri urgente.";
		fout << endl << "Dimensiunile sunzorului sunt urmatoarele:";
		for (int i = 0; i < 3; i++)
			fout << szt.dimensiuni[i] << ",";
		return fout;
	}
	friend ifstream& operator>>(ifstream& fin, senzorCO& szt)
	{
		fin >> (senzorbaza&)szt;
		char inf[255];
		if (szt.detaliiTehnice)
			delete[] szt.detaliiTehnice;
		fin.ignore();
		fin.getline(inf, 255);
		szt.detaliiTehnice = new char[strlen(inf) + 1];
		strcpy_s(szt.detaliiTehnice, strlen(inf) + 1, inf);
		if (szt.istoric)
			delete[] szt.istoric;
		szt.istoric = new double[szt.interactiuni];
		for (int i = 0; i < szt.interactiuni; i++)
			fin >> szt.istoric[i];
		if (szt.dimensiuni)
			delete[] szt.dimensiuni;
		szt.dimensiuni = new double[3];
		for (int i = 0; i < 3; i++)
			fin >> szt.dimensiuni[i];
		fin >> szt.coMax;
		fin >> szt.coMin;
		fin >> szt.rezistent;
		fin >> szt.alerta;
		return fin;

	}
};
class sistem
{
	int nrSenzori;
	char* localizare;
	double interconexiuni;
	double gradInteligenta;
	bool* apartine;
public:
	ifstream fin=ifstream("Senzori.txt");
	sistem()
	{
		this->nrSenzori = 3;
		this->localizare = new char[strlen("negasit") + 1];
		strcpy_s(this->localizare, strlen("negasit") + 1, "negasit");
		this->interconexiuni = 1;
		this->gradInteligenta = 1;
		this ->apartine = nullptr;
	}
	sistem(const char* lo, int nrSenzori, double gradInteligenta, double interconexiuni,bool* apartine )
	{
		this->localizare = new char[strlen(lo) + 1];
		strcpy_s(this->localizare, strlen(lo) + 1, lo);
		this->nrSenzori = nrSenzori;
		this->gradInteligenta = gradInteligenta;
		this->interconexiuni = interconexiuni;
		this->apartine = new bool[nrSenzori];
		for (int i = 0; i < nrSenzori; i++)
			this->apartine[i] = apartine[i];
	}
	sistem(const sistem& s)
	{
		this->nrSenzori = s.nrSenzori;
		this->localizare = new char[strlen(s.localizare) + 1];
		strcpy_s(this->localizare, strlen(s.localizare) + 1, s.localizare);
		this->gradInteligenta = s.gradInteligenta;
		this->interconexiuni = s.interconexiuni;
		this->apartine = new bool[nrSenzori];
		for (int i = 0; i < nrSenzori; i++)
			this->apartine[i] = s.apartine[i];
	}
	sistem operator=(const sistem& s)
	{

		this->nrSenzori = s.nrSenzori;
		if (localizare)
			delete[] this->localizare;
		this->localizare = new char[strlen(s.localizare) + 1];
		strcpy_s(this->localizare, strlen(s.localizare) + 1, s.localizare);
		this->gradInteligenta = s.gradInteligenta;
		this->interconexiuni = s.interconexiuni;
		if (apartine)
			delete[] this->apartine;
		this->apartine = new bool[nrSenzori];
		for (int i = 0; i < nrSenzori; i++)
			this->apartine[i] = s.apartine[i];
	 }
	~sistem()
	{
		delete[] this->localizare;
		 this->apartine=nullptr;
	}
    
	void setNrSenzori(int n)
	{
		this->nrSenzori = n;

	}
	void setApartine(bool* apartin, int nrs)
	{
		if (apartine)
			delete[] this->apartine;
		this->apartine = new bool[nrs];
		for (int i = 0; i < nrs; i++)
			this->apartine[i] = apartin[i];
		this->nrSenzori = nrs;
	}
	void setLocalizare(const char* lo)
	{
		if (localizare)
			delete[] this->localizare;
		this->localizare = new char[strlen(lo) + 1];
		strcpy_s(this->localizare, strlen(lo) + 1, lo);
	}
	void setInterconexiuni(double ic)
	{
		this->interconexiuni = ic;
	}
	void setGradInteligenta(double gi)
	{
		this->gradInteligenta = gi;
	}
	bool* getApartine()
	{
		int ok = 0;
		for (int i = 0; i < nrSenzori; i++)
		{
			if (apartine[i] == false)
				ok = 0;
		}
		if (ok == 0)
			throw "Sistemul nu este functional!";
	}
	char* getLocalizare()
	{
		return this->localizare;
	}
	double getInterconexiuni()
	{
		return this->interconexiuni;
	}
	int getNrSenzori()
	{
		return this->nrSenzori;
	}
	double getGradInteligenta()
	{
		return this->gradInteligenta;
	}
	//Metode
	void addSenzorTemperatura()
	{
		this->nrSenzori++;
		setInterconexiuni(this->interconexiuni+1);
		apartine[nrSenzori - 1] = true;

	}
	void addSenzorUmiditate()
	{
		this->nrSenzori++;
		setInterconexiuni(this->interconexiuni + 1);
		apartine[nrSenzori - 1] = true;
	}
	void addSenzorCO()
	{
		this->nrSenzori++;
		setInterconexiuni(this->interconexiuni + 1);
		apartine[nrSenzori - 1] = true;
	}
	void calculareInteligenta()
	{
		double gradMax = 1;
		int n = this->nrSenzori;
		gradMax = n * (n - 1) / 2;
		if (interconexiuni == 0)
		{
			gradInteligenta = 0;
		}
		else
			if (interconexiuni <= 0.2 * gradMax&&interconexiuni>0)
			{
				gradInteligenta = 1;
			}
			else
				if (interconexiuni <= 0.4 * gradMax&&interconexiuni>0.2*gradMax)
				{
					gradInteligenta = 2;
				}
				else
					if (interconexiuni <= 0.6 * gradMax&&interconexiuni>0.4*gradMax)
					{
						gradInteligenta = 3;
					}
					else
						if (interconexiuni <= 0.8 * gradMax && interconexiuni > 0.6 * gradMax)
						{
							gradInteligenta = 4;
						}
						else
							if (interconexiuni > 0.8 * gradMax && interconexiuni <= gradMax)
							{
								gradInteligenta = 5;
							}
	} 

};
int main()
{ 
	ifstream fin("Senzori.txt");
	ofstream fout("Rezultat.txt");
	//constructor senzorumiditate general
	//senzorumiditate generic1, generic2;
	//constructor senzorumiditate doar cu parametrii derivati
	senzorumiditate su2("Fabricat in Mexic, respecta standardele din 2021", 25, 50,new double[5]{43,37,39,48,45},
		"alb-lapte", true, false);
	//constructor senzorumiditate cu toti parametrii
	senzorumiditate su("Fabricat in China, dispune de dotari adecvate anului 2023", 10, 70, new double[4]{25,30,45,31},
		"verde inchis", true, false,
		1023,4,20,4,0,2,"in baia de sus", "AC4321",1,true,false,65 );
	//operatorul --(postinrcementare)
	su--;
	//operatorul []
	cout << su[2]<<endl;
	cout << su[3] << endl;
	//operatroul int()
	if (su() > 0)
		cout << "Senzorul da rateuri" << endl;
	else
		cout << "Functioneaza de minune." << endl;
	//afisarea prin supraincarcarea <<
	cout << su;
	cout << endl;
	//operatorul *
	su * 2;
	//operatorul ==
	//if (generic1 == su)
	//{
	//	cout << "Senzorii au aceleasi valori maxime si minime ca grad de umiditate!" << endl;
	//}
	//else
	//{
	//	cout << "Senzorii nu au aceleasi valori maxime si minime ca grad de umiditate!" << endl;
	//}
	////operatorul >
	//if (su > generic1)
	//{
	//	cout << "Primul senzor raspunde mai greu! " << endl;
	//}
	//else
	//{
	//	cout << "Primul senzor raspunde mai rapid!" << endl;
	//}
	//operatorul <
	if (su < su2)
	{
		cout << "Al doilea senzor a avut parte de mai multe interactiuni!" << endl;
	}
	else
	{
		cout << "Primul senzor a avut parte de mai multe interactiuni!" << endl;
	}
	//operatorul !
	if (!su)
	{
		cout << "Senzorul avertizeaza ca sunt probleme prin casa!" << endl;
	}
	else
	{
		cout << "Nu avem probleme inregistrate pe aici!" << endl;
	}
	//operatorul +=
	su += 5;
	cout << su.getUmiditateMaxima() << endl;
	//Verificam clasa Template
	//dublam pretul senzorului su
	su=suma( su, su);
	cout << su.getPret() << endl;
	//constructor senzortemperatura
	senzortemperatura szbaza;
	//constructor cu parametrii clasei derivate
	senzortemperatura stmic{ "Fabricat in Romania, dispune de tehnica anului 2020",-30,60,new double[3] {21,19,25},"negru",true };
	// constructor cu toti parametrii
	senzortemperatura st("Fabricat in Romania, dispune de tehnica anului 2021", 10, 70, new double[4] {25, 30, 45, 31},
		"verde inchis", true,
		1023, 4, 20, 4, 0, 2, "in baia de sus", "AC4321", 1, true, false, 55);
	//operatorul explicit double
	double medieFinala = (double)st;
	cout << medieFinala << endl;
	//operatorul -
	stmic - 10;
	cout << stmic.getTemperaturaMaxima() << endl;
	//operatorul ++ al senzortemperatura
	st++;
	cout << st.getIstoric() << endl;
	//operatorul [] a senzortemperatura
	cout << st[0]<<endl;
	//operatorul explicit int
	int tempest = (int)st;
		cout << tempest << endl;
	//constructor senzorCO
		senzorCO scob;
		//constructor cu toti parametrii
		senzorCO scop("Fabricat in Japonia, dispune de tehnologie avansata", 0, 255,new double[4] {200, 119, 100, 95},
			"portocaliu inchis", true, false,
			new double[3] {10, 10, 15},
			41, 4,
			15, 4, 2, 3, "in sufragerie, langa scari", "DF5555",
			1, true, false, 100);
      //operator double
		fout << scop() << endl;;


		//operator explicit double
		double s = (double)scop;
		cout << s << endl;

		//operatorul += al clasei senzorCO;
		scob += 5;
		cout << scob.getCOmax() << endl;
		//operatorul -= al clase senzorCO;
		scob -= 5;
		cout << scob.getCOmin() << endl;

		//operatorul ! al clase senzorCO
		if (!scop)
		{
			cout << "Senzorul avertizeaza ca sunt probleme prin casa!" << endl;
		}
		else
		{
			cout << "Nu avem probleme inregistrate pe aici!" << endl;
		}
	//citirea prin supraincarcarea>> si afisarea la consola prin<<
	/*cin >> generic1;
	cout << generic1;*/

	senzortemperatura stb;
	stb++;
	cout << stb;
	cout << endl;
	//verificarea exceptiilor
	try {
		stb.esteIdentificat();
	}
	catch(exception *e)
	{
		cout << e->what() << endl;
	}
	int temp = (int)stb;
	cout << temp << endl;
	stb - 5;
	cout << stb.getTemperaturaMaxima()<<endl;
	//exemplificam functiile virtuale pure din clasa abstracta
	//stb.conecteaza();
	//stb.deconecteaza();
	//stb.profil();
	//vedem sistemul
	sistem siot("GHB3333", 5, 3, 8, new bool[5]{true, true, true, true, true});
	//verificam inteligenta sistemului
	siot.calculareInteligenta();
	fout << siot.getGradInteligenta() << endl;
	if (siot.getGradInteligenta() == 0 || siot.getGradInteligenta() == 1)
	{
		fout << "Sistemul nu este prea inteligent" << endl;
	}
	else
		if (siot.getGradInteligenta() == 2 || siot.getGradInteligenta() == 3)
		{
			fout << "Sistemul are un grad de inteligenta mediu" << endl;
		}
		else
		{
			fout << "Sistemul are un grad ridicat de inteligenta!" << endl;
		}
	//adaugam un nou senzor in sistem
	siot.addSenzorCO();
	senzorCO sco2("Fabricat in Armenia, este accesibil", 0, 255, new double[4] {200, 119, 100, 95},
		"portocaliu inchis", true, false,
		new double[3] {10, 10, 15},
		41, 4,
		15, 4, 2, 3, "in sufragerie, langa scari", "DF5555",
		1, true, false, 73);
	//citirea si afisarea prin fisier text
	senzorumiditate generic2;
	fin >> stb;
	fout << stb;
	fout << endl;
	fin >> generic2;
	fin.close();
	fout << generic2;
	fout.close();
	return 0;
}