#pragma once
#include <string>
#include <vector>
#include "cidade.h"
#include "habitante.h"
using namespace std;

class faccao{
	static int lidf;
	static int lcor;
	int id;
	int cor;
	string nome_faccao;
	vector <cidade> vcidades;
	
	int qtdgold,qtdfood;// quantidade de comida e ouro
	bool ai;//1->ai-----0->player

public:
	faccao(string nome,bool ia);
	faccao(string nome,bool ia,int cor,int qtdg,int qtdf);
	~faccao(void);
	void setnomefaccao(string n);
	void setqtdouro(int o);
	void setqtdcomida(int c);
	void setai(bool a);
	void addouro(int o);
	void addcomida(int c);
	string getnomefaccao();
	string getnomecidade(int c);
	int getqtdouro();
	int getqtdcomida();
	bool getai();
	int getcor();
	int getid();
	string getnomecidhab(int c,int h);
	void setnomecidhab(int c,int h,string cid);
	void setveccid(cidade ci);
	int gettamveccid();
	int getNumeroHab(int cid);
	int getcidx(int f);
	int getcidy(int f);
	int getcidid(int f);
	int gethabx(int c,int h);
	int gethabmodo(int c,int h);
	int gethaby(int c,int h);
	int gethabdx(int c,int h);
	int gethabdy(int c,int h);
	int gethabid(int c,int h);
	int gethabmove(int c,int h);
	int gethabtipo(int c,int h);
	int verificahabitante(int id);//verifica existencia de hab
	void addhabitante(int c,habitante* hab);
	void irparaxy(int cid, int h,int l, int c);
	void deslocarhab(int cid,int h,string or);
	void sethabflgmov(int cid,int h,bool f);
	void colocahabxy(int  cid,int h,int l,int c);
	int gethabtempo(int c,int h);
	void sethabtempo(int c,int h, int t);
	int calculacustos();
	void sethabcidact(int c,int h,string nome);
	void setidatak(int c,int h,int i);
	int getidatak(int c,int h);
	void remhab(int c,int h);
	int gethabvisao(int c, int h);
	void actualizacofres();
	void remcid(int c);
};

