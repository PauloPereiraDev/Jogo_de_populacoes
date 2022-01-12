#pragma once
#include <math.h>
#include <string>
using namespace std;
/* identifiers dos habitantes
0->habitante
1->hc----campones
2->hm----mioneiro
3->hs----soldado
4->hh----heroi
5->ha----hab mist
*/
 class habitante{
	static int lidh;//last id habitant
	int id,raiovisao,lentidao,custo,tempo;
	int x,y;
	int dx,dy;//destino caso modo=1
	int modo,idatak;//0-sem accao 1-com accao
	bool flgmov;//0->por mover    1->movido
	string cidade_actual;//cidade onde se oncontra
	
public:
	habitante(int c,int l,int rv,int lt,int ct,int tp);
	habitante(int c,int l,int rv,int lt,int ct,int tp,string cid);
	habitante(int c,int l,int rv,int lt,int ct,int tp,string cid,int idh,int desty,int destx,int md,int mv,int idat);
	~habitante(void);
	void setnomecidade(string nom);
	string getnomecidade();
	void setid(int i);
	void setraio(int r);
	void setlent(int l);
	void settipo(char t);
	void setx(int px);
	void sety(int py);
	void setdx(int px);
	void setdy(int py);
	void setflgmove(bool m);
	void setmodo(int m);
	void setidatak(int i);
	int getidatak();
	int getlidh();
	int getid();
	int getraio();
	int getlent();
	char gettipo();
	int getx();
	int gety();
	int getdx();
	int getdy();
	int getmove();
	int getmodo();
	int getcusto();
	int gettempo();
	void settempo(int t);
	void colocaemxy(int l,int c);
	void deslocar(string or);
	void irparaxy(int l, int c);
	virtual int gethabtipo();
	virtual int getcns();
};

class campones:  public habitante{
public:
	campones(int c,int l);
	campones(int c,int l,int t);
	campones(int c,int l,string cid);
	campones(int c,int l,string cid,int idh,int desty,int destx,int md,int mv,int idat);
	int gethabtipo();
	int getcns();
};

class mineiro: public habitante{
public:
	mineiro(int c,int l);
	mineiro(int c,int l,int t);
	mineiro(int c,int l,string cid);
	mineiro(int c,int l,string cid,int idh,int desty,int destx,int md,int mv,int idat);
	int gethabtipo();
	int getcns();
};

class soldado:public habitante{
public:
	soldado(int c,int l);
	soldado(int c,int l,int t);
	soldado(int c,int l,string cid);
	soldado(int c,int l,string cid,int idh,int desty,int destx,int md,int mv,int idat);
	int gethabtipo();
	int getcns();
};

class heroi:public habitante{
public:
	heroi(int c,int l);
	heroi(int c,int l,int t);
	heroi(int c,int l,string cid);
	heroi(int c,int l,string cid,int idh,int desty,int destx,int md,int mv,int idat);
	int gethabtipo();
	int getcns();
};

class catapulta:public habitante{
public:
	catapulta(int c,int l);
	catapulta(int c,int l,int t);
	catapulta(int c,int l,string cid);
	catapulta(int c,int l,string cid,int idh,int desty,int destx,int md,int mv,int idat);
	int gethabtipo();
	int getcns();
};