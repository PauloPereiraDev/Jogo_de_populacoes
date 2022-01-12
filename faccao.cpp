#include "faccao.h"


faccao::faccao(string nome,bool a){
	id=++lidf;
	cor=++lcor;
	nome_faccao=nome;
	qtdgold=1000;
	qtdfood=200;
	ai=a;
}
faccao::faccao(string nome,bool ia,int c,int qtdg,int qtdf){
	id=++lidf;
	cor=c;
	nome_faccao=nome;
	qtdgold=qtdg;
	qtdfood=qtdf;
	ai=ia;

}



faccao::~faccao(void){
	while (!vcidades.empty())
  {
	 vcidades.erase(vcidades.begin());
  }
	
}

void faccao::setnomefaccao(string n){
	nome_faccao=n;
}
void faccao::setqtdouro(int o){
	qtdgold=qtdgold+o;
}


void faccao::setqtdcomida(int c){
	qtdfood=qtdfood+c;
}


void faccao::setai(bool a){
	ai=a;
}

void faccao::addouro(int o){
	if(o>0)
		qtdgold=qtdgold+o;
}

void faccao::addcomida(int c){
	if(c>0)
		qtdfood=qtdfood+c;
}
string faccao::getnomefaccao(){
	return nome_faccao;
}
int faccao::getqtdouro(){
	return qtdgold;
}
int faccao::getqtdcomida(){
	return qtdfood;
}
bool faccao::getai(){
	return ai;
}
void faccao::setveccid(cidade ci){
	vcidades.push_back(ci);
}
string faccao::getnomecidhab(int c,int h){return vcidades[c].getnomecidhab(h);}
void faccao::setnomecidhab(int c,int h,string cid){vcidades[c].setnomecidhab(h,cid);}

string faccao::getnomecidade(int c){
	return this->vcidades[c].getnomecidade();
}
int faccao::verificahabitante(int id){


	int i,j;

	for(i=0;i<(int)vcidades.size();i++)
		for(j=0;j<vcidades[i].gettamvechab();j++)
			if(vcidades[i].gethabid(j)==id)
				return 1;
		
	return 0;	
}

int faccao::getcor(){
	return cor;
}
int faccao::getid(){
	return id;
}

int faccao::gettamveccid(){
	return vcidades.size();
}



int faccao::getcidx(int f){
	return vcidades[f].getxcidade();

}

int faccao::getcidy(int f){
	return vcidades[f].getycidade();

}

int faccao::getcidid(int f){
	return vcidades[f].getidcidade();

}

int faccao::getNumeroHab(int cid){
	return vcidades[cid].gettamvechab();
}

int faccao::gethabid(int c,int h){
	return vcidades[c].gethabid(h);
}

int faccao::gethabx(int c,int h){
	return vcidades[c].gethabx(h);
}

int faccao::gethaby(int c,int h){
	return vcidades[c].gethaby(h);
}
int faccao::gethabdx(int c,int h){
	return vcidades[c].gethabdx(h);
}
int faccao::gethabmodo(int c,int h){
	return vcidades[c].gethabmodo(h);
}
int faccao::gethabmove(int c,int h){
	return vcidades[c].gethabmove(h);
}
int faccao::gethabtipo(int c,int h){
	return vcidades[c].gethabtipo(h);
}
int faccao::gethabdy(int c,int h){
	return vcidades[c].gethabdy(h);
}
void faccao::addhabitante(int c,habitante* hab){
	vcidades[c].addhab(hab);
}
void faccao::irparaxy(int cid,int h,int l, int c){
	vcidades[cid].irparaxy(h,l,c);
}
void faccao::deslocarhab(int cid,int h,string or){
	vcidades[cid].deslocarhab(h,or);
}
void faccao::sethabflgmov(int cid,int h,bool f){
	vcidades[cid].sethabflgmov(h,f);
}
void faccao::colocahabxy(int cid,int h,int l,int c){
	vcidades[cid].colocahabxy(h,l,c);
}
int faccao::gethabtempo(int c,int h){ return vcidades[c].gethabtempo(h);}
void faccao::sethabtempo(int c,int h, int t){vcidades[c].sethabtempo(h,t);}

void faccao::sethabcidact(int c,int h,string nome){
	vcidades[c].sethabcidact(h,nome);
}

void faccao::setidatak(int c,int h,int i){vcidades[c].setidatak(h,i);}
int faccao::getidatak(int c,int h){return vcidades[c].getidatak(h);}
void faccao::remhab(int c,int h){vcidades[c].remhab(h);}
int faccao::gethabvisao(int c, int h){return vcidades[c].gethabvisao(h);}
void faccao::actualizacofres(){
 int pdrgld=0,pdrcmd=0,cns=0;
 for(int c=0;c<vcidades.size();++c){
  pdrgld+=vcidades[c].getproducaogold();
  pdrcmd+=vcidades[c].getproducaocomida();
 }
 qtdgold+=pdrgld;
 qtdfood+=pdrcmd;
 do{
  cns=0;
  for(int c=0;c<vcidades.size();++c)
   cns+=vcidades[c].getcustocidade();
  if(qtdfood<cns)
   remhab(0,0);
 }while(qtdfood<cns);
 qtdfood-=cns;
}
void faccao::remcid(int c){vcidades.erase(vcidades.begin()+c);}