#include <string>
#include <vector>
#include "habitante.h"
#include <iostream>
#pragma once

using namespace std;

class cidade{	
	int id;
	string nome_cidade;
	vector <habitante*> vhabitantes;
	static int lidc;
	int x,y;
public:
	cidade(string nome,int x,int y);
	~cidade(void);
	
	void setidcidade(int nid);	
	void setxcidade(int px);
	void setycidade(int py);
	void setnomecidade(string nmc);
	string getnomecidade();
	string getnomecidhab(int h);
	void setnomecidhab(int h,string cid);
	int getxcidade();
	int getycidade();
	int getidcidade();
	void addhab(habitante* ha);
	int gettamvechab();
	int gethabid(int h);
	int gethabx(int h);
	int gethaby(int h);
	int gethabdx(int h);
	int gethabdy(int h);
	int gethabmodo(int h);
	int gethabmove(int h);
	int gethabtipo(int h);
	int gethabtempo(int h);
	void sethabtempo(int h, int t);
	void irparaxy(int h,int l, int c);
	void deslocarhab(int h,string or);
	void sethabflgmov(int h,bool n);
	void colocahabxy(int h,int l, int c);
	int getcustocidade();
	int getproducaocomida();
	int getproducaogold();
	void sethabcidact(int h,string nome);
	void setidatak(int h,int i);
	int getidatak(int h);
	void remhab(int h);
	
	int gethabvisao(int h);

};
