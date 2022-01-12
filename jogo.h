#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include "faccao.h"
#include "habitante.h"
#include "cidade.h"
#include "artefacto.h"
#include "consola.h"
#include "sstream"
#include <fstream>
#pragma once
using namespace std;

class jogo{
	Consola c;
	vector <artefacto*> vart;
	vector <faccao> vfac;
	char comando[50];
	int row,col;
	int turno;
	jogo(const jogo &j);
	jogo &operator=(const jogo &jogo);
	vector <int> mposfac;
	vector <int> mpostipo;

	
public:
	jogo();
	~jogo(void);
	int getnrow();
	int getncol();
	void intrucoes();
	void actualizatela();
	void actualizaelemts();
	int tratacomando(char* stringc,int idf);
	void joga();
	char menu();
	void inicia();
	void pededadosiniciais();
	char sairmesmo();
	void avancaturno(int i);
	void actualizaturno();
	habitante* adicionarhab(int c,int l,cidade* cidade,int rv,int lt,faccao* f);
	cidade* adicionarcid(string nome,int c,int l,faccao* f);
	void adicionarfac(string nome,bool ia);
	void adicionarart(string tp,int c,int l);
	void limpalinhacomand(int i);
	void carregarjogo();
	void gravarjogo();
	void mkcity(string paror,int param1,int param2,int idh);
	void dup(string paror,int param1,int param2,int idh);
	void fac(string paror,int idh);
	void infoc(int param1,int idh);
	void infof(string nmfac,int idh);
	void cmdh(char tipo,string paror,int idh);
	void cmdf(int param1,string paror,int idh);
	void cmddisb(int hid,int idh);
	void mkhab(char tipo, int param1,int param2,int idh);
	void cmdd(string paror,int hid,int idh);
	void cmdg(int param1,int param2,int hid,int idh);
	void vaiparacidade(int idh,string nmcidade,int idf);
	void apanhaart(int aid,int hid,int idh);
	void procuracid(int a,int idh,int hid);
	void producaoimediata(int idh);
	void desertar(int hid,int idh);
	void mkart(char tipo, int param1,int param2);
	void actualizatab();
	void visao(int hid,int pf,int pc,int ph);
	void atacahab(int idhabataca,int idhabatacado);
	int combate(int tphab1,int tphab2);
	void randomartefacto();
};

