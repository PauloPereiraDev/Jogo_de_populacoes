#include "cidade.h"

cidade::cidade(string nome,int l,int c)
{
	id=++lidc;
	x=c;
	y=l;
	nome_cidade=nome;
}

cidade::~cidade(void){


}

void cidade::setidcidade(int nid){
	id=nid;
}
void cidade::setxcidade(int px){
	x=px;
}
void cidade::setycidade(int py){
	y=py;
}
void cidade::setnomecidade(string nmc){
	nome_cidade=nmc;
}

int cidade::getxcidade(){ return x;}
int cidade::getycidade(){ return y;}
int cidade::getidcidade(){ return id;}
int cidade::gettamvechab(){return vhabitantes.size();}
string cidade::getnomecidade(){return nome_cidade;}

void cidade::addhab(habitante* ha){vhabitantes.push_back(ha);}

int cidade::gethabid(int h){return vhabitantes[h]->getid();}
int cidade::gethabx(int h){return vhabitantes[h]->getx();}
int cidade::gethaby(int h){return vhabitantes[h]->gety();}
int cidade::gethabdx(int h){return vhabitantes[h]->getdx();}
int cidade::gethabdy(int h){return vhabitantes[h]->getdy();}
int cidade::gethabmodo(int h){return vhabitantes[h]->getmodo();}
int cidade::gethabmove(int h){return vhabitantes[h]->getmove();}
int cidade::gethabtipo(int h){return vhabitantes[h]->gethabtipo();}
void cidade::irparaxy(int h,int l, int c){vhabitantes[h]->irparaxy(l,c);}
void cidade::deslocarhab(int h,string or){vhabitantes[h]->deslocar(or);}
void cidade::sethabflgmov(int h,bool f){vhabitantes[h]->setflgmove(f);}
void cidade::colocahabxy(int h,int l,int c){vhabitantes[h]->colocaemxy(l,c);}
string cidade::getnomecidhab(int h){ return vhabitantes[h]->getnomecidade();}
void cidade::setnomecidhab(int h,string cid){vhabitantes[h]->setnomecidade(cid);}
int cidade::gethabtempo(int h){return vhabitantes[h]->gettempo();}
void cidade::sethabtempo(int h, int t){vhabitantes[h]->settempo(t);}
int cidade::getcustocidade(){
	int cst=0;
	for(int i=0;i<vhabitantes.size();++i)
		cst+=vhabitantes[i]->getcns();
	return cst;
}
int cidade::getproducaocomida(){
	int pdr=0;
	for(int i=0;i<vhabitantes.size();++i)
		if(vhabitantes[i]->gethabtipo()==1)
			if(vhabitantes[i]->getnomecidade()=="NULL")
				pdr+=3;
			else
				pdr+=1;
	return pdr;
}
int cidade::getproducaogold(){
	int pdr=0;
	for(int i=0;i<vhabitantes.size();++i)
		if(vhabitantes[i]->gethabtipo()==2)
			if(vhabitantes[i]->getnomecidade()=="NULL")
				pdr+=2;
	return pdr;
}
void cidade::sethabcidact(int h,string nome){
	vhabitantes[h]->setnomecidade(nome);
}
void cidade::setidatak(int h,int i){vhabitantes[h]->setidatak(i);}
int cidade::getidatak(int h){return vhabitantes[h]->getidatak();}
void cidade::remhab(int h){vhabitantes.erase(vhabitantes.begin()+h);}
int cidade::gethabvisao(int h){return vhabitantes[h]->getraio();}
