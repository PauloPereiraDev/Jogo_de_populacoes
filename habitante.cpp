#include "habitante.h"
#include <iostream>


habitante::habitante(int c,int l,int rv,int lt,int ct,int tp){
	id=++lidh;
	x=c;
	y=l;
	idatak=0;
	dx=NULL;
	dy=NULL;
	modo=0;
	flgmov=0;
	raiovisao=rv;
	lentidao=lt;
	custo=ct;
	tempo=tp;
	cidade_actual="NULL";
	idatak=0;
}
habitante::habitante(int c,int l,int rv,int lt,int ct,int tp,string cid){
		id=++lidh;
	x=c;
	y=l;
	dx=NULL;
	dy=NULL;
	modo=0;
	flgmov=0;
	raiovisao=rv;
	lentidao=lt;
	custo=ct;
	tempo=tp;
	cidade_actual=cid;
	idatak=0;
}
habitante::habitante(int c,int l,int rv,int lt,int ct,int tp,string cid,int idh,int desty,int destx,int md,int mv,int idat){
	id=idh;
	x=c;
	y=l;
	dx=destx;
	dy=desty;
	modo=md;
	flgmov=mv;
	raiovisao=rv;
	lentidao=lt;
	custo=ct;
	tempo=tp;
	cidade_actual=cid;
	idatak=idat;
}
habitante::~habitante(void){

}
void habitante::setidatak(int i){idatak=i;}
int habitante::getidatak(){return idatak;}
void habitante::setnomecidade(string nom){
		cidade_actual=nom;
}
string habitante::getnomecidade(){
	return cidade_actual;	
}
void habitante::setid(int i){
	id=i;
}
void habitante::setraio(int r){
	raiovisao=r;
}
void habitante::setlent(int l){
	lentidao=l;
}

void habitante::setx(int px){
	x=px;
}
void habitante::sety(int py){
	y=py;
}

void habitante::setdx(int px){
	dx=px;
}
void habitante::setdy(int py){
	dy=py;
}

void habitante::setflgmove(bool m){
	flgmov=m;
}

void habitante::setmodo(int m){
	modo=m;
}


int habitante::getid(){
	return id;
}
int habitante::getraio(){
	return raiovisao;
}
int habitante::getlent(){
	return lentidao;
}

int habitante::getx(){
	return x;
}
int habitante::gety(){
	return y;
}
int habitante::getdx(){
	return dx;
}
int habitante::getdy(){
	return dy;
}

int habitante::getmove(){
	return flgmov;
}

int habitante::getmodo(){
	return modo;
}
int habitante::getcusto(){return custo;}
int habitante::gettempo(){return tempo;}
void habitante::settempo(int t){
	if(tempo!=0){
		if(t==0){
			tempo=0;
		}else
			tempo-=t;
	}
}
void habitante::colocaemxy(int l,int c)
{
	if(l<0)
		l=0;
	if(c<0)
		c=0;
		x=c;
		y=l;
		flgmov=1;
}

void habitante::deslocar(string or)
{
	if(or=="N"||or =="n")
		colocaemxy(gety()-1*getlent(),getx());
	else
		if(or=="S"||or=="s")
			colocaemxy(gety()+1*getlent(),getx());
		else
			if(or=="E"|| or=="e")
				colocaemxy(gety(),getx()+1*getlent());
			else
				if(or=="O"||or=="o")
					colocaemxy(gety(),getx()-1*getlent());
		
				else
					if(or=="NE"||or=="ne")
						colocaemxy(gety()-1*getlent(),getx()+1*getlent());
					else
						if(or=="NO"||or=="no")
							colocaemxy(gety()-1*getlent(),getx()-1*getlent());
						else
							if(or=="SE"||or=="se")
								colocaemxy(gety()+1*getlent(),getx()+1*getlent());
							else
								if(or=="SO"||or=="so")
								colocaemxy(gety()+1*getlent(),getx()-1*getlent());
}

void habitante::irparaxy(int l,int c){
	int nl,nc;
	int la,ca,lent;
	la=gety();
	ca=getx();
	lent=getlent();
	
	if(abs(ca-c)<=lent && abs(la-l)<=lent){
			if(modo==1){
				modo=0;
				dx=NULL;
				dy=NULL;}
			
			colocaemxy(l,c);
	}else{
		if(modo==0){
			modo=1;
			dx=c;
			dy=l;
		}
		if(ca!=c){
			if(ca>c)
				nc=ca-lent;
			else
				nc=ca+lent;
		}else
			nc=ca;
		if(la!=l){
			if(la>l)
				nl=la-lent;
			else
				nl=la+lent;
		}else
			nl=la;
		colocaemxy(nl,nc);
	}



}
int habitante::gethabtipo(){ 
	return 0;
}
int habitante::getcns(){return 0;}	

//secçao do habitante tipo campones

campones::campones(int c,int l):habitante(c,l,2,2,5,3){
}
campones::campones(int c,int l,int t):habitante(c,l,2,2,5,0){
}
campones::campones(int c,int l,string cid):habitante(c,l,2,2,5,3,cid){
}
campones::campones(int c,int l,string cid,int idh,int desty,int destx,int md,int mv,int idat):habitante(c,l,2,2,5,3,cid,idh,desty,destx,md,mv,idat){
}
int campones::gethabtipo(){return 1;}

int campones::getcns(){return 1;}

//secçao do habitante tipo mineiro

mineiro::mineiro(int c,int l):habitante(c,l,2,2,10,5){
}
mineiro::mineiro(int c,int l,int t):habitante(c,l,2,2,10,0){
}
mineiro::mineiro(int c,int l,string cid):habitante(c,l,2,2,10,5,cid){
}
mineiro::mineiro(int c,int l,string cid,int idh,int desty,int destx,int md,int mv,int idat):habitante(c,l,2,2,5,3,cid,idh,desty,destx,md,mv,idat){
}
int mineiro::gethabtipo(){return 2;}
int mineiro::getcns(){return 2;}


//secçao do habitante tipo soldado

soldado::soldado(int c,int l):habitante(c,l,2,3,10,5){
}
soldado::soldado(int c,int l,int t):habitante(c,l,2,3,10,0){
}
soldado::soldado(int c,int l,string cid):habitante(c,l,2,3,10,5,cid){
}
soldado::soldado(int c,int l,string cid,int idh,int desty,int destx,int md,int mv,int idat):habitante(c,l,2,2,5,3,cid,idh,desty,destx,md,mv,idat){
}
int soldado::gethabtipo(){return 3;}
int soldado::getcns(){return 2;}


//secçao do habitante tipo heroi

heroi::heroi(int c,int l):habitante(c,l,4,1,20,8){
}
heroi::heroi(int c,int l,int t):habitante(c,l,4,1,20,0){
}
heroi::heroi(int c,int l,string cid):habitante(c,l,4,1,20,8,cid){
}
heroi::heroi(int c,int l,string cid,int idh,int desty,int destx,int md,int mv,int idat):habitante(c,l,2,2,5,3,cid,idh,desty,destx,md,mv,idat){
}
int heroi::gethabtipo(){return 4;}
int heroi::getcns(){return 3;}

//secçao do habitante tipo catapulta
catapulta::catapulta(int c,int l):habitante(c,l,1,5,25,10){}
catapulta::catapulta(int c,int l,int t):habitante(c,l,1,5,25,0){}
catapulta::catapulta(int c,int l,string cid):habitante(c,l,1,5,25,10,cid){}
catapulta::catapulta(int c,int l,string cid,int idh,int desty,int destx,int md,int mv,int idat):habitante(c,l,2,2,5,3,cid,idh,desty,destx,md,mv,idat){}
int catapulta::gethabtipo(){return 5;}
int catapulta::getcns(){return 4;}