#include "artefacto.h"


artefacto::artefacto(int c,int l){
	id=++lida;
	x=c;
	y=l;
}

artefacto::artefacto(int c,int l,int ida){
	id=ida;
	x=c;
	y=l;
}

artefacto::~artefacto(void){

}

int artefacto::getidartefacto(){return id;}
int artefacto::getxartefacto(){return x;}
int artefacto::getyartefacto(){return y;}

void artefacto::setidartefacto(int cid){id=cid;}
void artefacto::setxartefacto(int px){x=px;}
void artefacto::setyartefacto(int py){y=py;}

int artefacto::getintipo(){return 0;}
int artefacto::accao(){return 0;}
//seccçao do artefacto das moedas

amoedas::amoedas(int c,int l):artefacto(c,l){
	srand ((int)time(NULL));//inicializar o "randomizer"
	int d=rand()%50;
	nmoedas=d+50;
}
amoedas::amoedas(int c,int l,int ida):artefacto(c,l,ida){
	srand ((int)time(NULL));//inicializar o "randomizer"
	int d=rand()%50;
	nmoedas=d+50;
}
int amoedas::accao(){return nmoedas;}
int amoedas::getintipo(){return 1;}

//seccçao do artefacto de matar

amata::amata(int c,int l):artefacto(c,l){}
amata::amata(int c,int l,int ida):artefacto(c,l,ida){}

int amata::getintipo(){return 2;}

//seccçao do artefacto de duplicar cidade

adup::adup(int c,int l):artefacto(c,l){}
adup::adup(int c,int l,int ida):artefacto(c,l,ida){}

int adup::getintipo(){return 3;}

//seccçao do artefacto de desertar habitante

adeserta::adeserta(int c,int l):artefacto(c,l){}
adeserta::adeserta(int c,int l,int ida):artefacto(c,l,ida){}

int adeserta::getintipo(){return 4;}

//seccçao do artefacto da comida

acomida::acomida(int c,int l):artefacto(c,l){
	srand ((int)time(NULL));//inicializar o "randomizer"
	int d=rand()%50;
	ncomida=d+50;
}
acomida::acomida(int c,int l,int ida):artefacto(c,l,ida){
	srand ((int)time(NULL));//inicializar o "randomizer"
	int d=rand()%50;
	ncomida=d+50;
}
int acomida::accao(){return ncomida;}
int acomida::getintipo(){return 5;}

//seccçao do artefacto de fundar cidade

afunda::afunda(int c,int l):artefacto(c,l){}
afunda::afunda(int c,int l,int ida):artefacto(c,l,ida){}

int afunda::getintipo(){return 6;}


//seccçao do artefacto misterio

amist::amist(int c,int l):artefacto(c,l){}
amist::amist(int c,int l,int ida):artefacto(c,l,ida){}

int amist::getintipo(){return 7;}