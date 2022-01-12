#pragma once
#include <string>
#include <time.h>
#include <iostream>
using namespace std;
/* identifiers dos artefactos
0->artefacto 
1->am----amoedas
2->ac----amata
3->ae----adup
4->ap----adeserta
5->as----acomida
6->at----afunda
7->aa----amist
*/
class artefacto
{
	static int lida;
	int id,x,y;
public:
	artefacto(int c,int l);
	artefacto(int c,int l,int ida);
	~artefacto(void);
	int getidartefacto();
	int getxartefacto();
	int getyartefacto();
	void setidartefacto(int cid);
	void setxartefacto(int px);
	void setyartefacto(int py);
	virtual int getintipo();
	virtual int accao();
};

class amoedas: public artefacto{
	int nmoedas;
public:
	amoedas(int c,int l);
	amoedas(int c,int l,int ida);
	virtual int accao();
	virtual int getintipo();
};

class amata:public artefacto{
public:
	amata(int c,int l);
	amata(int c,int l,int ida);
	virtual int getintipo();
};

class adup:public artefacto{
public:
	adup(int c,int l);
	adup(int c,int l,int ida);
	virtual int getintipo();
};

class adeserta:public artefacto{
public:
	adeserta(int c,int l);
	adeserta(int c,int l,int ida);
	virtual int getintipo();
};

class acomida:public artefacto{
	int ncomida;
public:
	acomida(int c,int l);
	acomida(int c,int l,int ida);
	virtual int accao();
	virtual int getintipo();
};

class afunda:public artefacto{
public:
	afunda(int c,int l);
	afunda(int c,int l,int ida);
	virtual int getintipo();
};

class amist:public artefacto{
public:
	amist(int c,int l);
	amist(int c,int l,int ida);

	virtual int getintipo();
};