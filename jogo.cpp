#include "jogo.h"
int habitante::lidh=0;
int faccao::lidf=0;
int cidade::lidc=0;
int artefacto::lida=0;
int faccao::lcor=2;



	
jogo::jogo(){
	turno=1;
	c.setBackgroundColor(c.PRETO);
	c.setTextSize(8,8);
	c.setScreenSize(60,82);  // linhas colunas. valores grandes pode nao dar
}
char jogo::sairmesmo(){
	char r;
	c.clrscr();
	cout<<"\n\nTem a certeza que quer sair?(s->sim)\n ";
	cin>>r;
	if((r=='s')||(r=='S'))
		return '6';
	else
		return '0';
}
void jogo::inicia(){
	
	char op;
	do{
		while (!vart.empty()){
			vart.erase(vart.begin());
		}
		while(!vfac.empty()){
			vfac.erase(vfac.begin());
		}
		
		op=menu();
		switch(op){
			case '1': pededadosiniciais();break;
			case '2': carregarjogo();break;//continua
			case '3': intrucoes();break;//instrucoes
			case '4': op=sairmesmo();break;
		}
	}while(op!='6');
}
void jogo::pededadosiniciais(){
	c.clrscr();
	int ln,cl;
	int i;
	
	
	cout<<"\nIntroduza o numero de linhas do mapa(m->18,M->60):";
	do{
		cin>>ln;
	}while((ln<18)||(ln>40));
	cout<<"\nIntroduza o numero de colunas do mapa(m->38,M->100):";
	do{
		cin>>cl;
		if((cl<38)||(cl>50))
			cout<<"\nValor incorreto!Introduza de novo o numero de colunas do mapa(m->38,M->100:";
	}while((cl<15)||(cl>100));
	row=ln;
	col=cl;
	cout<<"\n\nIntroduza o numero de jogadores humanos(minimo 1):";
	int j;
	do{
		cin>>j;
	}while(j<1);
	int lim=row*col;
	mposfac.assign(lim,-1);
	mpostipo.assign(lim,0);
	for(int i=0;i<j;++i){
		string nome;
		cout<<"\nIntroduza o nome do jogador "<<(i+1)<<": ";
		cin>>nome;
	faccao a(nome,0);
	
	
	a.setveccid(cidade("cidade hab",rand()%row,rand()%col));
	a.addhabitante(0,new campones(a.getcidx(0),a.getcidy(0)));
	a.sethabtempo(0,0,0);
	vfac.push_back(a);

	
	
	}
	cout<<"\n\nIntroduza o numero de CPU: ";
	int c;
	do{
		cin>>c;
	}while((c+j)<2);
	for(int i=0;i<c;++i){
		stringstream nome;
		nome.clear();
		nome<<"cpu "<<i<<'\0';
		
		faccao b(nome.str(),1);
		nome.clear();
		nome<<"cpu "<<i<<'\0';
		nome<<"cpu"<<i<<"polis"<<"\0";
		b.setveccid(cidade(nome.str(),rand()%row,rand()%col));
		b.addhabitante(0,new campones(b.getcidx(0),b.getcidy(0)));
		b.sethabtempo(0,0,0);
		vfac.push_back(b);
	}
	
	joga();
}
void jogo::actualizatab(){

int lim=row*col;
 mposfac.assign(lim,-1);
 mpostipo.assign(lim,0);
 int f,h,c,a,x;
 int f1,h1,c1;
 int f2,c2,h2;
 int prob;
 int p1,p2;
 int cont=0;
 int fatac,catac,hatac;
 int frem=-1,crem=-1;
 srand((int)time(NULL));
 for(f=0;f<vfac.size();f++){//atualiza as cidades no vector das posicoes
  for(c=0;c<vfac[f].gettamveccid();c++){
   x=(vfac[f].getcidy(c)*col)+vfac[f].getcidx(c);
   mposfac[x]=vfac[f].getid();
   mpostipo[x]=1;
  }
 }
 
 for(int a=0;a<vart.size();a++)//atualiza os artefatos no vector das posicoes
 {
 mpostipo[(vart[a]->getyartefacto()*col)+vart[a]->getxartefacto()]=3;
}




 for(f=0;f<vfac.size();f++){//atualiza os habitantes no vetor das posicoes
  for(c=0;c<vfac[f].gettamveccid();c++){
   for(h=0;h<vfac[f].getNumeroHab(c);h++){

    if(mpostipo[(vfac[f].gethaby(c,h)*col)+vfac[f].gethabx(c,h)]!=0)//verifica se a celula esta vazia(-1)
    {
     if(mposfac[(vfac[f].gethaby(c,h)*col)+vfac[f].gethabx(c,h)]==vfac[f].getid())//verifica se o que esta na celula e da mesma faccao
     {
      if(mpostipo[(vfac[f].gethaby(c,h)*col)+vfac[f].gethabx(c,h)]==1)//verifica se é uma cidade que esta na celula
       {
        for(c2=0;c2<vfac[f].gettamveccid();c2++)//procura a cidade e coloca o hab la dentro
          if(vfac[f].getcidx(c2)==vfac[f].gethabx(c,h) && vfac[f].getcidy(c2)==vfac[f].gethaby(c,h))
              vfac[f].sethabcidact(c,h,vfac[f].getnomecidade(c2));
    
   }
  }
  else//se nao pertence a mesma faccao, vai a procura do que esta naquela celula
      if(mpostipo[(vfac[f].gethaby(c,h)*col)+vfac[f].gethabx(c,h)]==2){//se for habitante
    for(f1=0;f1<vfac.size();f1++)//procura qual é o habitante com quem vai combater
     for(c1=0;c1<vfac[f1].gettamveccid();c1++)
    for(h1=0;h1<vfac[f1].getNumeroHab(c1);h1++){
     if(vfac[f].gethabx(c,h)==vfac[f1].gethabx(c1,h1) && vfac[f].gethaby(c,h)==vfac[f1].gethaby(c1,h1)){//faz a verificacao se do habitante que esta naquela celula
           if(vfac[f].gethabtipo(c,h)==1 && vfac[f1].gethabtipo(c1,h1)==1){// se os dois forem camponeses
        vfac[f].colocahabxy(c,h,vfac[f].gethaby(c,h),vfac[f].gethabx(c,h)-1);
        mposfac[(vfac[f].gethaby(c,h)*col)+vfac[f].gethabx(c,h)]=vfac[f].getid();
        mpostipo[(vfac[f].gethaby(c,h)*col)+vfac[f].gethabx(c,h)]=2;
       }
       else{
        if(vfac[f].gethabtipo(c,h)==1||(vfac[f].gethabtipo(c,h)==2&&vfac[f].getqtdouro()==0))
       p1=1;
        else
       p1=vfac[f].gethabtipo(c,h);

        if(vfac[f1].gethabtipo(c1,h1)==1||(vfac[f1].gethabtipo(c1,h1)==2&&vfac[f1].getqtdouro()==0))
       p2=1;
        else
       p2=vfac[f1].gethabtipo(c1,h1);
       
        int vencedor=combate(p1,p2);
        switch(vencedor){
       case 0:break;
       case 1:
        vfac[f1].remhab(c1,h1);
        break;
       case 2:
        vfac[f].remhab(c,h);
        break;
       case 3:
        vfac[f1].remhab(c1,h1);
        vfac[f].remhab(c,h);
        break;
        
        }

       }
     }
    }
   }
   else
    if(mpostipo[(vfac[f].gethaby(c,h)*col)+vfac[f].gethabx(c,h)]==1){// se for cidade
     for(f1=0;f1<vfac.size();f1++)
      for(c1=0;c1<vfac[f1].gettamveccid();c1++){
		  if(vfac[f].gethabx(c,h)==vfac[f1].getcidx(c1) &&vfac[f].gethaby(c,h)==vfac[f1].getcidy(c1)){

			  for(f2=0;f2<vfac.size();f2++)
					for(c2=0;c2<vfac[f2].gettamveccid();c2++)
						for(h2=0;h2<vfac[f2].getNumeroHab(c2);h2++)
							if(vfac[f2].getnomecidhab(c2,h2)==vfac[f1].getnomecidade(c1))
								cont++;

			  if(cont>0){
				 // if(vfac[f].gethabmodo(c,h)==1){
					  vfac[f].colocahabxy(c,h,vfac[f].gethaby(c,h)-1,vfac[f].gethabx(c,h));
					  if(vfac[f].gethabtipo(c,h)==1||(vfac[f].gethabtipo(c,h)==2&&vfac[f].getqtdouro()==0))
						p1=1;
					  else
						p1=vfac[f].gethabtipo(c,h);

						for(f2=0;f2<vfac.size();f2++)
							for(c2=0;c2<vfac[f2].gettamveccid();c2++)
								for(h2=0;h2<vfac[f2].getNumeroHab(c2);h2++)
									if(vfac[f2].getnomecidhab(c2,h2)==vfac[f1].getnomecidade(c1)){
										fatac=f2;
										catac=c2;
										hatac=h2;
										h2=vfac[f2].getNumeroHab(c2);
										c2=vfac[f2].gettamveccid();
										f2=vfac.size();

									}

					 if(vfac[fatac].gethabtipo(catac,hatac)==1||(vfac[fatac].gethabtipo(catac,hatac)==2&&vfac[fatac].getqtdouro()==0))
						p2=1;
					  else
						p2=vfac[fatac].gethabtipo(catac,hatac);

						  			
					switch(combate(p1,p2)){
					   case 0:break;
					   case 1:
						vfac[fatac].remhab(catac,hatac);
						break;
					   case 2:
						vfac[f].remhab(c,h);
						break;
					   case 3:
						vfac[fatac].remhab(catac,hatac);
						vfac[f].remhab(c,h);
						break;
        
					}
			  
				  //}
			  }
			  else{
				 crem=c1;
				frem=f1;
			  }
		  }  
      
      }
       
	  if(crem!=-1 && frem!=-1){
		  vfac[f].setveccid(cidade(vfac[frem].getnomecidade(crem),vfac[frem].getcidy(crem),vfac[frem].getcidx(crem)));
		  vfac[frem].remcid(crem);
	  
	  
	  }
	}
    else
     if(mpostipo[(vfac[f].gethaby(c,h)*col)+vfac[f].gethabx(c,h)]==3){
       for(a=0;a<vart.size();a++){
     if(vart[a]->getxartefacto()==vfac[f].gethabx(c,h)&&vart[a]->getyartefacto()==vfac[f].gethaby(c,h)){//procura o artefato que esta naquela posicao
      this->apanhaart(vart[a]->getidartefacto(),vfac[f].gethabid(c,h),f);
      
     }
       }
     }
 }

  
 else{
     mposfac[(vfac[f].gethaby(c,h)*col)+vfac[f].gethabx(c,h)]=vfac[f].getid();
     mpostipo[(vfac[f].gethaby(c,h)*col)+vfac[f].gethabx(c,h)]=2;
    }
   }

  }
 }

}
jogo::~jogo(void){
	
	while (!vart.empty())
  {
		vart.erase(vart.begin());
  }
	
	
	while(!vfac.empty()){
		vfac.erase(vfac.begin());
	}
}
char jogo::menu(){
		
		c.clrscr();
		cout<<"\n\t\tTRABALHO DE POO\n\n\n";
		cout<<"\t1-INICIAR\n\n";
		cout<<"\t2-CONTINUAR\n\n";
		cout<<"\t3-INSTRUCOES\n\n\n";
		cout<<"\t4-SAIR\n\n";
		char np;
		do{
			cin>>np;
		}while((np!='1')&&(np!='2')&&(np!='3')&&(np!='4'));
		return np;
}
void jogo::intrucoes(){
	c.clrscr();
	cout<<"\n \n \tINSTRUCOES\n\n O jogo consiste numa batalha até a morte entre 2 ou várias civilizaçoes,\n em que dispoe de habitantes e cidades para aniquilar os adversários,\n o mundo tambem possui artefactos com efeitos mistério\n para ajuda-lo a atingir o seu objectivo,\n também existem artefactos que fazem o contrário :P";
	
	
	getchar();
	getchar();
}
void jogo::actualizatela(){


	
	c.setTextSize(8,8);
	c.setScreenSize(60,82);  // linhas colunas. valores grandes pode nao dar
	c.clrscr();
	c.setBackgroundColor(c.PRETO);


	//====================Numera as celulas======================================================================
	int i;
	c.gotoxy(0,0);
	c.setBackgroundColor(c.PRETO);
	c.setTextColor(c.BRANCO);
	 int x=2,y=0;

	 if(c.getdeslx()%2==1)
		 y=1;
	 else
		 y=0;
	 //====Numera as colunas
	 for(i=0+c.getdeslx();i<(c.getsizex()/2)+c.getdeslx()-2;i++){
		c.gotoxy(x,y);
		if(i<10)
		cout<<"0"<<i;
		else
			cout<<i;
		if(i%2 == 0)
			y++;
		else
			y--;
		x+=2;
	}
	 

	
//=========Numera as linhas
	x=0;
	y=2;

	for(i=0+c.getdesly();i<(c.getsizey()/2)+c.getdesly()-11;i++){
		c.gotoxy(x,y);
		if(i<10)
			cout<<"0"<<i;
		else
			cout<<i;
		y+=2;
	}
//========Coloca setas de scroll=====================

	if(c.getdesly()>0)
	{
	c.gotoxy((c.getsizex()-2),2);
		 cout<<" ^";
	}

	
	if(c.getdesly()+(c.getsizey()-42)<getnrow()-1){
	c.gotoxy((c.getsizex()-2),c.getsizey()-22);
	cout<<" V";
	}
	if(c.getdeslx()+(c.getsizex()-2)/2-2< getncol()-1){
		c.gotoxy((c.getsizex()-2),c.getsizey()-20);
		cout<<" >";
	}
	if(c.getdeslx()>0)
	{
	c.gotoxy(0,c.getsizey()-20);
	cout<<" <";
	}
//===================Coloca o quadriculado======================================
	x=2;
	y=2;
	int ft=0,zt=0;//flg de troca de cor
	for(y=2;y<(c.getsizey()-20);y+=2){
		if((zt+c.getdesly())%2==0)
			ft=1;
		else
			ft=0;
		for(i=0;i<(c.getsizex()-4)/2;i++){	
			if((i+c.getdeslx())%2==0)
				if(ft==0)
					c.setBackgroundColor(c.AZUL_CLARO);
				else
					c.setBackgroundColor(c.BRANCO);
			else
				if(ft==0)
					c.setBackgroundColor(c.BRANCO);
				else
					c.setBackgroundColor(c.AZUL_CLARO);
			c.gotoxy(x+i*2,y);
			cout<<" ";
			c.gotoxy(x+i*2+1,y);
			cout<<" ";
			c.gotoxy(x+i*2,y+1);
			cout<<" ";
			c.gotoxy(x+i*2+1,y+1);
			cout<<" ";
		}
		zt++;
	}	
	c.setBackgroundColor(c.PRETO);
	c.setTextColor(c.BRANCO);
	c.gotoxy(0,41);
	for(i=0;i<80;i++){
		cout<<"-";
		x++;
	}
	cout<<"\n";


	actualizaelemts();	
}
void jogo::actualizaelemts(){
	int i,f,j;
	int x;
	do{
		x=-1;
		for(f=0;f<vfac.size();f++)
			if(vfac[f].gettamveccid()==0)
				x=f;
		if(x!=-1)
			vfac.erase(vfac.begin()+x);
	}while(x!=-1);

	if(vfac.size()>1){
			for(f=0;f<(int)vfac.size();f++)
			{
				for(i=0;i<vfac[f].gettamveccid();i++){
					if((vfac[f].getcidx(i)>=0+c.getdeslx() && vfac[f].getcidx(i)<(c.getdeslx()+39))&&(vfac[f].getcidy(i)>=0+c.getdesly()&& vfac[f].getcidy(i)<c.getdesly()+19))
						c.setCellcolor(vfac[f].getcidx(i)-c.getdeslx(),vfac[f].getcidy(i)-c.getdesly(),vfac[f].getcor(),"CI",vfac[f].getcidid(i));
			
					for(j=0;j<vfac[f].getNumeroHab(i);j++)
					{
						int x=vfac[f].gethabx(i,j);
						int y=vfac[f].gethaby(i,j);
						if((vfac[f].gethabx(i,j)>=0+c.getdeslx() && vfac[f].gethabx(i,j)<c.getdeslx()+39)&&(vfac[f].gethaby(i,j)>=0+c.getdesly() && vfac[f].gethaby(i,j)<c.getdesly()+19)&& vfac[f].getnomecidhab(i,j)=="NULL"){// && vfac[f].gethabtempo(i,j)==0 
							int th;
							th=(&vfac[f])->gethabtipo(i,j);
							switch(th){
								case 1:c.setCellcolor(vfac[f].gethabx(i,j)-c.getdeslx(),vfac[f].gethaby(i,j)-c.getdesly(),vfac[f].getcor(),"HC",vfac[f].gethabid(i,j));break;
								case 2:c.setCellcolor(vfac[f].gethabx(i,j)-c.getdeslx(),vfac[f].gethaby(i,j)-c.getdesly(),vfac[f].getcor(),"HM",vfac[f].gethabid(i,j));break;
								case 3:c.setCellcolor(vfac[f].gethabx(i,j)-c.getdeslx(),vfac[f].gethaby(i,j)-c.getdesly(),vfac[f].getcor(),"HS",vfac[f].gethabid(i,j));break;
								case 4:c.setCellcolor(vfac[f].gethabx(i,j)-c.getdeslx(),vfac[f].gethaby(i,j)-c.getdesly(),vfac[f].getcor(),"HH",vfac[f].gethabid(i,j));break;
								case 5:c.setCellcolor(vfac[f].gethabx(i,j)-c.getdeslx(),vfac[f].gethaby(i,j)-c.getdesly(),vfac[f].getcor(),"HA",vfac[f].gethabid(i,j));break;
						}
				
						}
					}
				}
		
			}
	
			for (i=0;i<(int)vart.size();++i)
				if(((vart[i]->getxartefacto()-c.getdeslx())>=0)&&((vart[i]->getxartefacto())<(c.getdeslx()+39))&&((vart[i]->getyartefacto()-c.getdesly())>=0)&&((vart[i]->getyartefacto())<(c.getdesly()+19)))
					switch(vart[i]->getintipo()){
						case 1:c.setCellcolor(vart[i]->getxartefacto()-c.getdeslx(),vart[i]->getyartefacto()-c.getdesly(),5,"AM",vart[i]->getidartefacto());break;
						case 2:c.setCellcolor(vart[i]->getxartefacto()-c.getdeslx(),vart[i]->getyartefacto()-c.getdesly(),5,"AC",vart[i]->getidartefacto());break;
						case 3:c.setCellcolor(vart[i]->getxartefacto()-c.getdeslx(),vart[i]->getyartefacto()-c.getdesly(),5,"AE",vart[i]->getidartefacto());break;
						case 4:c.setCellcolor(vart[i]->getxartefacto()-c.getdeslx(),vart[i]->getyartefacto()-c.getdesly(),5,"AP",vart[i]->getidartefacto());break;
						case 5:c.setCellcolor(vart[i]->getxartefacto()-c.getdeslx(),vart[i]->getyartefacto()-c.getdesly(),5,"AS",vart[i]->getidartefacto());break;
						case 6:c.setCellcolor(vart[i]->getxartefacto()-c.getdeslx(),vart[i]->getyartefacto()-c.getdesly(),5,"AT",vart[i]->getidartefacto());break;
						case 7:c.setCellcolor(vart[i]->getxartefacto()-c.getdeslx(),vart[i]->getyartefacto()-c.getdesly(),5,"AA",vart[i]->getidartefacto());break;
					}
			actualizatab();
			c.setBackgroundColor(c.PRETO);
			c.setTextColor(c.BRANCO);
			c.gotoxy(0,42);
	}
	else{
		c.clrscr();
		cout<<"\n\n\tvencedor:"<<vfac[0].getnomefaccao()<<endl;
		getchar();
		jogo::inicia();
	
	
	}
}
void jogo::limpalinhacomand(int i){
	string clean(200,' ');
	
	c.gotoxy(0,42);
	for(int j=0;j<6;j++)
		cout<<clean;

	
	c.gotoxy(0,42);
	c.setBackgroundColor(vfac[i].getcor());
	cout<<"<"<<vfac[i].getnomefaccao()<<">";
	c.setBackgroundColor(c.PRETO);

}
void jogo::gravarjogo(){

		int f,c,h,a;
		ofstream out("save.txt");
		out<<this->row<<' '<<this->col<<endl;
		out<<vfac.size()<<endl;
		for(f=0;f<vfac.size();f++){
			out<<vfac[f].getnomefaccao()<<" "<<vfac[f].getcor()<<" "<<vfac[f].getqtdouro()<<" "<<vfac[f].getqtdcomida()<<endl;
			out<<vfac[f].gettamveccid()<<endl;
			for(c=0;c<vfac[f].gettamveccid();c++){
				out<<vfac[f].getnomecidade(c)<<' '<<vfac[f].getcidx(c)<<' '<<vfac[f].getcidy(c)<<' '<<vfac[f].getNumeroHab(c)<<endl;
				for(h=0;h<vfac[f].getNumeroHab(c);h++){
					out<<vfac[f].gethabtipo(c,h)<<' '<<vfac[f].gethabid(c,h)<<' '<<vfac[f].gethabx(c,h)<<' '<<vfac[f].gethaby(c,h)<<' '<<vfac[f].getnomecidhab(c,h)<<' '<<vfac[f].gethabdy(c,h)<<' '<<vfac[f].gethabdx(c,h)<<' '<<vfac[f].gethabmodo(c,h)<<' '<<vfac[f].gethabmove(c,h)<<' '<<vfac[f].getidatak(c,h)<<endl;
				}
			}
			
		}	
		out<<endl;
		int x=vart.size();
		out<<x<<endl;
		for(a=0;a<vart.size();a++){
			out<<vart[a]->getintipo()<<" "<<vart[a]->getidartefacto()<<" "<<vart[a]->getxartefacto()<<" "<<vart[a]->getyartefacto();
			out<<endl;
		}
			

}
void jogo::carregarjogo(){
	
	ifstream infile;
	stringstream buff;
	string STRING,nome;
	int id,x,y,tipo,nhab,ncid,nfac,nart,cor,qtdg,qtdf,a,dx,dy,modo,mve,idat;
	char tar;
	infile.open ("save.txt");
			getline(infile,STRING);
			buff.clear();
			buff<<STRING;
			buff>>this->row>>this->col;
			
			infile>>nfac;
			getline(infile,STRING);
			for(int f=0;f<nfac;f++){
					getline(infile,STRING);
					buff.clear();
					buff<<STRING;
					buff>>nome>>cor>>qtdg>>qtdf;
					faccao a(nome,0,cor,qtdg,qtdf);
					infile>>ncid;
					getline(infile,STRING);
					for(int c=0;c<ncid;c++){
						buff.clear();
						getline(infile,STRING);
						buff<<STRING;
						buff>>nome>>x>>y>>nhab;
						a.setveccid(cidade(nome,y,x));
						for(int h=0;h<nhab;h++){
							buff.clear();
							getline(infile,STRING);
							buff<<STRING;
							buff>>tipo>>id>>x>>y>>nome>>dy>>dx>>modo>>mve>>idat;
							switch(tipo){
								case 1:
									a.addhabitante(0,new campones(x,y,nome,id,dy,dx,modo,mve,idat));
									break;
								case 2:
									a.addhabitante(0,new mineiro(x,y,nome,id,dy,dx,modo,mve,idat));
									break;
								case 3:
									a.addhabitante(0,new soldado(x,y,nome,id,dy,dx,modo,mve,idat));
									break;
								case 4:
									a.addhabitante(0,new heroi(x,y,nome,id,dy,dx,modo,mve,idat));
									break;
								case 5:
									a.addhabitante(0,new catapulta(x,y,nome,id,dy,dx,modo,mve,idat));
									break;
							}
						}
					}
			vfac.push_back(a);
			}
			getline(infile,STRING);
			getline(infile,STRING);
			buff.clear();
			buff<<STRING;
			buff>>nart;
			for(a=0;a<nart;a++){
				getline(infile,STRING);
				buff.clear();
				buff<<STRING;
				buff>>tipo>>id>>x>>y;
							switch(tipo){
					case 1:vart.push_back(new amoedas(x,y,id));break;
					case 2:vart.push_back(new amata(x,y,id));break;
					case 3:vart.push_back(new adup(x,y,id));break;
					case 4:vart.push_back(new adeserta(x,y,id));break;
					case 5:vart.push_back(new acomida(x,y,id));break;
					case 6:vart.push_back(new afunda(x,y,id));break;
					case 7:vart.push_back(new amist(x,y,id));break;
				}
			
			}
	
	        
        
	infile.close();

	joga();
}
int jogo::tratacomando(char* stringc,int idh){

	stringstream strcmd;
	int i=0;
	int c,h,f;
	string paror,nmfac,nome;
	int param1=0,param2=0,hid;
	param1=param2=hid=NULL;
	char tipo;
	
	char idcom[50];//nome do comando

	srand ((int)time(NULL));
	strcmd.clear();
	strcmd<<stringc;
	strcmd>>idcom;
	if(strcmp(idcom,"bot")==0)
		return 1;
	/*for(c=0;c<vfac[idh].gettamveccid();c++)
	{
		for(h=0;h<vfac[idh].getNumeroHab(c);h++)
		{
			if(vfac[idh].gethabmodo(c,h)==0)
			{
				param1=rand()% getnrow();
				param2=rand()% getncol();
			}
			vfac[idh].colocahabxy(c,h,param1,param2);
		}
	}*/
	if(strcmp(idcom,"g")==0){
		
		strcmd>>hid>>param1>>param2;
		if(param1!=NULL && param2!=NULL && hid!=NULL)
			cmdg(param1,param2,hid,idh);
	actualizatela();
	return 0;
	}
	if(strcmp(idcom,"d")==0||strcmp(idcom,"D")==0)
	{

		strcmd>>paror>>hid;
		if(hid!=NULL){
			cmdd(paror,hid,idh);
		}
	return 0;
	}
	
	if(strcmp(idcom,"MKHAB")==0||strcmp(idcom,"mkhab")==0)
	{
			
		strcmd>>tipo>>param1>>param2;
		mkhab(tipo,param1,param2,idh);
		//actualizaelemts();	
		return 2;
	}
	if(strcmp(idcom,"MKART")==0||strcmp(idcom,"mkart")==0)
	{
			
		strcmd>>tipo>>param1>>param2;
		mkart(tipo,param1,param2);
		actualizaelemts();	
		return 2;
	}
	
	
	if(strcmp(idcom,"DISB")==0||strcmp(idcom,"disb")==0){
		strcmd>>hid;
		if(hid!=NULL){
			cmddisb(hid,idh);
			return 0;
		}
	}

	if(strcmp(idcom,"NEXT")==0||strcmp(idcom,"next")==0){
		strcmd>>hid;
		if(hid==NULL)
			avancaturno(1);
		else
			avancaturno(hid);
		
		return 0;
	}
	
	
	if(strcmp(idcom,"M")==0||strcmp(idcom,"m")==0)
	{
		strcmd>>param1>>nome;
		vaiparacidade(param1,nome,idh);
		
	}
	if(strcmp(idcom,"A")==0||strcmp(idcom,"a")==0)
	{
		strcmd>>param1>>param2;
		atacahab(param1,param2);
	}
	if(strcmp(idcom,"F")==0||strcmp(idcom,"f")==0){
		strcmd>>param1>>paror;
		cmdf(param1,paror,idh);
	}
	if(strcmp(idcom,"H")==0||strcmp(idcom,"h")==0){
		strcmd>>tipo>>paror;
		cmdh(tipo,paror,idh);
	}
	if(strcmp(idcom,"INFOF")==0||strcmp(idcom,"infof")==0)
	{
		strcmd>>nmfac;
		infof(nmfac,idh);
		return 3;
	}
	if(strcmp(idcom,"INFOC")==0||strcmp(idcom,"infoc")==0){
		strcmd>>param1;
		infoc(param1,idh);
		return 3;
	}
	if(strcmp(idcom,"END")==0||strcmp(idcom,"end")==0){
		return 1;
	}	

	if(strcmp(idcom,"FAC")==0||strcmp(idcom,"fac")==0){
		strcmd>>paror;
		fac(paror,idh);
	}
	if(strcmp(idcom,"SAVE")==0||strcmp(idcom,"save")==0)
	{
		gravarjogo();
		return 4;
		
	}
	if(strcmp(idcom,"LOAD")==0||strcmp(idcom,"load")==0)
	{
		carregarjogo();
		return 0;
	}


	if(strcmp(idcom,"GOLD")==0||strcmp(idcom,"gold")==0)
	{
		strcmd>>param1;
		(int)param1;
		if(param1>0)
			vfac[idh].addouro(param1);
	}
	if(strcmp(idcom,"FOOD")==0||strcmp(idcom,"food")==0)
	{
		strcmd>>param1;
		(int)param1;
		if(param1>0)
			vfac[idh].addcomida(param1);
	}
	if(strcmp(idcom,"DUP")==0||strcmp(idcom,"dup")==0){
		strcmd>>paror>>param1>>param2;
		dup( paror, param1, param2, idh);
		return 1;

	}
	if(strcmp(idcom,"MKCITY")==0||strcmp(idcom,"mkcity")==0){
		strcmd>>paror>>param1>>param2;
		mkcity( paror, param1, param2, idh);
		return 2;
	}



	if(strcmp(idcom,"exit")==0)
		return 5;
	else
		return -1;

	
}
void jogo::joga(){
	int fj=0,i=0,fa=1;
	actualizatela();
	while(1){

		if(i<(int)vfac.size()){
			
			if(vfac[i].getai()==1)
				fj=tratacomando("bot",i);
			else
				{
				limpalinhacomand(i);
				cout<<"use as setas do teclado para navegar pelo mapa[ enter para terminar]";
				int fnv=0;//flg de verificacao s exisitiu navegaçao
				while(1){
						char tecla = c.getch();
						if(tecla == c.ENTER){break;}
						else
							if (tecla == c.ESQUERDA)fa=c.setdeslx(-1,col-1);
							else 
								if (tecla == c.DIREITA)fa=c.setdeslx(+1,col-1);
								else
									if (tecla == c.CIMA)fa=c.setdesly(-1,row-1);
									else
										if (tecla == c.BAIXO)fa=c.setdesly(1,row-1);
										else
											fa=0;
							if(fa==1){
								actualizatela();
								limpalinhacomand(i);
								cout<<"use as setas do teclado para navegar pelo mapa[ enter para terminar]";
							}
				}
				
				limpalinhacomand(i);
				fflush(stdin);
				while(1){
					cin.getline(comando,25);
					if(comando[0]!=0)
						break;
					limpalinhacomand(i);
				}
				fj=tratacomando(comando,i);
				if(fj==5)
					break;
				if(fj<2)
					actualizatela();
				if(fj<3){

					actualizaelemts();
				}
				if(fj==3)
				{
					cout<<endl;
					cout<<"clique enter para continuar..."<<endl;
					while(1){
						char tecla=c.getch();
						if(tecla==c.ENTER)
							break;
					}
				}	
			}
			if(fj==1)
						i++;
		}else{
			i=0;
			avancaturno(1);
		}
	}
}
void jogo::avancaturno(int i){
	int f,c,h,d;
	string dir;
	srand ((int)time(NULL));//inicializar o "randomizer"
	for(int j=0;j<i;++j){
	for(f=0;f<(int)vfac.size();f++){
		vfac[f].actualizacofres();
		for(c=0;c<vfac[f].gettamveccid();c++)
			for(h=0;h<vfac[f].getNumeroHab(c);h++){
		
				if(vfac[f].gethabmove(c,h)==false && vfac[f].gethabtempo(c,h)==0 && vfac[f].getnomecidhab(c,h)=="NULL"){
					if(vfac[f].gethabmodo(c,h)==1){
						if(vfac[f].getidatak(c,h)!=0){
							atacahab(vfac[f].gethabid(c,h),vfac[f].getidatak(c,h));
						}else
							vfac[f].irparaxy(c,h,vfac[f].gethabdy(c,h),vfac[f].gethabdx(c,h));

					}else
						visao( vfac[f].gethabid(c,h), f,c,h);
				}
				
				if(vfac[f].getNumeroHab(c)>h&&vfac[f].gethabtipo(c,h)!=3&&vfac[f].gethabmove(c,h)==0 && vfac[f].gethabmodo(c,h)==0 && vfac[f].gethabtempo(c,h)==0 && vfac[f].getnomecidhab(c,h)=="NULL"){
						d=rand()%8;
						switch(d){
							case 0:
									dir="N";
									break;
							case 1:
									dir="NE";
									break;
							case 2:
									dir="E";
									break;
							case 3:
									dir="SE";
									break;
							case 4:
									dir="S";
									break;
							case 5:
									dir="SO";
									break;
							 case 6:
									dir="O";
									break;
							case 7:
									dir="NO";
									break;
							}
						//vfac[f].deslocarhab(c,h,);
						cmdd(dir,vfac[f].gethabid(c,h),f);
				}
				if(vfac[f].getNumeroHab(c)>h)
					vfac[f].sethabflgmov(c,h,0);
				actualizatab();
			}
		}
	randomartefacto();
	actualizaturno();
	}
}
int jogo::getncol(){
return col;
}
int jogo::getnrow(){
return row;
}
void jogo::actualizaturno(){
	int f,c,h;
++turno;
	for(f=0;f<(int)vfac.size();f++)
		for(c=0;c<vfac[f].gettamveccid();c++)
			for(h=0;h<vfac[f].getNumeroHab(c);h++){
				if(vfac[f].gethabtempo(c,h)>0)
					vfac[f].sethabtempo(c,h,1);
			}




}
void jogo::mkcity(string paror,int param1,int param2,int idh){
		int flg=0;
		
		if(paror!="NULL"){
			for(int i=0;i<vfac[idh].gettamveccid();++i)
				if(vfac[idh].getnomecidade(i)==paror)
					flg=1;
			if(flg==0&&param1>=0&&param2>=0&&param1<=row&&param2<=col){
				vfac[idh].setveccid(cidade(paror,param1,param2));
				vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new campones(param2,param1,paror));
				vfac[idh].sethabtempo(vfac[idh].gettamveccid()-1,0,0);
			}
		}
}
void jogo::dup(string paror,int param1,int param2,int idh){
			for(int c=0;c<vfac[idh].gettamveccid();++c)
			if(vfac[idh].getnomecidade(c)==paror)
				if(param1>=0&&param1<=row&&param2>=0&&param2<=col){
					string newname;
					newname=paror;
					newname+="DUP";//junta dup ao nome
					vfac[idh].setveccid(cidade(newname,param1,param2));
					int x;
					for(int i=0;i<vfac[idh].getNumeroHab(c);++i){
						x=vfac[idh].gethabtipo(c,i);
						switch(x){
							case 1:vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new campones(param2,param1,newname));vfac[idh].sethabtempo(vfac[idh].gettamveccid()-1,i,0);break;
							case 2:vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new mineiro(param2,param1,newname));vfac[idh].sethabtempo(vfac[idh].gettamveccid()-1,i,0);break;
							case 3:vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new soldado(param2,param1,newname));vfac[idh].sethabtempo(vfac[idh].gettamveccid()-1,i,0);break;
							case 4:vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new heroi(param2,param1,newname));vfac[idh].sethabtempo(vfac[idh].gettamveccid()-1,i,0);break;
							case 5:vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new catapulta(param2,param1,newname));vfac[idh].sethabtempo(vfac[idh].gettamveccid()-1,i,0);break;
						}
					}
					paror="xpto";
				}
}
void jogo::fac(string paror,int idh){
	int x=-1;
		for(int f=0;f<vfac.size();++f)
			if(vfac[f].getnomefaccao()==paror)
				int x=f;
		int t=vfac.size();
		if(x!=-1){
			if(idh>x){
				for(int i=idh;idh<t;++i)
					avancaturno(1);
				for(int i=0;i<x;++i)
					avancaturno(1);
			}
			else
				for(int i=idh;i<x;++i)
					avancaturno(1);
		}
}
void jogo::infoc(int param1,int idh){
	int cid,fid=-1,x;
		for(int f=0;f<vfac.size();f++){
			for(int cc=0;cc<vfac[f].gettamveccid();cc++){
				if(vfac[f].getcidid(cc)==param1)
				{
					fid=f;
					cid=cc;
					cout<<"Nome cidade: "<<vfac[f].getnomecidade(cc)<<endl;
					cout<<"Faccao que a controla: "<<vfac[f].getnomefaccao()<<endl;
				}
			}
		}
		if(fid!=-1){
			cout<<"ID  || habitantes || tempo restante:"<<endl;
			for(int cc=0;cc<vfac[fid].gettamveccid();cc++){
				for(int h=0;h<vfac[fid].getNumeroHab(cc);h++)
					
					if(vfac[fid].getnomecidhab(cc,h)==vfac[fid].getnomecidade(cid)){
							x=(&vfac[fid])->gethabtipo(cc,h);
							switch(x){
								case 1:	cout<<" "<<vfac[fid].gethabid(cc,h)<< "\tCampones   "<<vfac[fid].gethabtempo(cc,h)<<"\n";break;
								case 2:	cout<<" "<<vfac[fid].gethabid(cc,h)<< "\tMineiro    "<<vfac[fid].gethabtempo(cc,h)<<"\n";break;
								case 3:	cout<<" "<<vfac[fid].gethabid(cc,h)<< "\tSoldado    "<<vfac[fid].gethabtempo(cc,h)<<"\n";break;
								case 4:	cout<<" "<<vfac[fid].gethabid(cc,h)<< "\tHeroi      "<<vfac[fid].gethabtempo(cc,h)<<"\n";break;
								case 5:	cout<<" "<<vfac[fid].gethabid(cc,h)<< "\tCatapulta  "<<vfac[fid].gethabtempo(cc,h)<<"\n";break;
							}
						}
			
				}
		}
}
void jogo::infof(string nmfac,int idh){
for(int f=0;f<vfac.size();f++)
   if(vfac[f].getnomefaccao()==nmfac){ 
    cout<<"Nome faccao: "<<vfac[f].getnomefaccao()<<endl;
    cout<<"Ouro: "<<vfac[f].getqtdouro()<<endl;
    cout<<"Food: "<<vfac[f].getqtdcomida()<<endl;
    for(int t=1;t<6;t++){
     int cont=0;
     switch(t){
      case 1:
       cout<<"Numero de camponeses: ";
       break;
      case 2:
       cout<<"Numero de mineiros: ";
       break;
      case 3:
       cout<<"Numero de soldados: ";
       break;
      case 4:
       cout<<"Numero de heróis: ";
       break;
      case 5:
       cout<<"Numero de Catapultas: ";
       break;
     }
     int cc;
     cont=0;
     for(cc=0;cc<vfac[f].gettamveccid();cc++){
      for(int h=0;h<vfac[f].getNumeroHab(cc);h++){
       int x=(&vfac[f])->gethabtipo(cc,h);
       if(x==t)
        cont++;
      }
     }
     cout<<cont<<endl;
    }
   }
}
void jogo::cmdh(char tipo,string paror,int idh){
			for(int cc=0;cc<vfac[idh].gettamveccid();++cc)
			if(vfac[idh].getnomecidade(cc)==paror){
				
				if(tipo=='c' || tipo=='C'){
					habitante* aux=new campones(vfac[idh].getcidx(cc),vfac[idh].getcidx(cc),paror);
					if(vfac[idh].getqtdouro()>=aux->getcusto()){
						vfac[idh].setqtdouro(-aux->getcusto());
						vfac[idh].addhabitante(cc,aux);
					}
				}
				if(tipo=='m' || tipo=='M'){
					habitante* aux=new mineiro(vfac[idh].getcidx(cc),vfac[idh].getcidx(cc),paror);
					if(vfac[idh].getqtdouro()>=aux->getcusto()){
						vfac[idh].setqtdouro(-aux->getcusto());
						vfac[idh].addhabitante(cc,aux);
					}
				}
				if(tipo=='s' || tipo=='S'){
					habitante* aux=new soldado(vfac[idh].getcidx(cc),vfac[idh].getcidx(cc),paror);
					if(vfac[idh].getqtdouro()>=aux->getcusto()){
						vfac[idh].setqtdouro(-aux->getcusto());
						vfac[idh].addhabitante(cc,aux);
					}
				}
				if(tipo=='h' || tipo=='H'){
					habitante* aux=new heroi(vfac[idh].getcidx(cc),vfac[idh].getcidx(cc),paror);
					if(vfac[idh].getqtdouro()>=aux->getcusto()){
						vfac[idh].setqtdouro(-aux->getcusto());
						vfac[idh].addhabitante(cc,aux);
					}
				}
				if(tipo=='a' || tipo=='A'){
					 habitante* aux=new catapulta(vfac[idh].getcidx(cc),vfac[idh].getcidx(cc),paror);
					 if(vfac[idh].getqtdouro()>=aux->getcusto()){
						 vfac[idh].setqtdouro(-aux->getcusto());
						 vfac[idh].addhabitante(cc,aux);
					}
				 }

			}
}
void jogo::cmdf(int param1,string paror,int idh){
	int c;
			if(vfac[idh].getqtdouro()>=10){
			for(c=0;c<vfac[idh].gettamveccid();++c)
				for(int h=0;h<vfac[idh].getNumeroHab(c);++h)
					if(vfac[idh].gethabid(c,h)==param1&&vfac[idh].gethabtipo(c,h)==1){
						int flg=0;
						for(int i=0;i<vfac[idh].gettamveccid();++i)
							if(vfac[idh].getnomecidade(i)==paror)
								flg=1;
						if(flg==0){
							vfac[idh].setveccid(cidade(paror,vfac[idh].gethaby(c,h),vfac[idh].gethabx(c,h)));
							vfac[idh].setnomecidhab(c,h,paror);
							vfac[idh].setqtdouro(-10);
						}
					}


			}
}
void jogo::cmddisb(int hid,int idh){
	
		int c,h,i=-1,j;
		for(c=0;c<vfac[idh].gettamveccid();c++)
			for(h=0;h<vfac[idh].getNumeroHab(c);h++)
				if(vfac[idh].verificahabitante(hid)==1)
					if(vfac[idh].gethabid(c,h)==hid){
						i=h;
						j=c;
					}
		if(i!=-1)
			vfac[idh].remhab(j,i);

}
void jogo::mkhab(char tipo, int param1,int param2,int idh){
		if(param2>=0 && param2<=col && param1>=0 && param1<=row)
			{
				tipo=toupper(tipo);
				switch(tipo){
				case 'C':vfac[idh].addhabitante(0,new campones(param2,param1,0));break;
				case 'M':vfac[idh].addhabitante(0,new mineiro(param2,param1,0));break;
				case 'S':vfac[idh].addhabitante(0,new soldado(param2,param1,0));break;
				case 'H':vfac[idh].addhabitante(0,new heroi(param2,param1,0));break;
				case 'A':vfac[idh].addhabitante(0,new catapulta(param2,param1,0));break;	
				}
			}
		
}
void jogo::mkart(char tipo, int param1,int param2){
		if(param2>=0 && param2<=col && param1>=0 && param1<=row)
			{
				tipo=toupper(tipo);
				switch(tipo){
					case 'M':vart.push_back(new amoedas(param2,param1));break;
					case 'C':vart.push_back(new amata(param2,param1));break;
					case 'E':vart.push_back(new adup(param2,param1));break;
					case 'P':vart.push_back(new adeserta(param2,param1));break;
					case 'S':vart.push_back(new acomida(param2,param1));break;
					case 'T':vart.push_back(new afunda(param2,param1));break;
					case 'A':vart.push_back(new amist(param2,param1));break;
				}
			
			}
		
}
void jogo::cmdd(string paror,int hid,int idh){
	int c,h,x=-1;
	for(c=0;c<vfac[idh].gettamveccid();c++)
				for(h=0;h<vfac[idh].getNumeroHab(c);h++)
					if(vfac[idh].verificahabitante(hid)==1)
						if(vfac[idh].gethabid(c,h)==hid && vfac[idh].gethabmove(c,h)==0&& vfac[idh].gethabtempo(c,h)==0){
							if(vfac[idh].getnomecidhab(c,h)!="NULL")
								vfac[idh].setnomecidhab(c,h,"NULL");
							vfac[idh].deslocarhab(c,h,paror);
							vfac[idh].sethabflgmov(c,h,1);
							
							if(vfac[idh].gethabtipo(c,h)==2)
								if(1==rand()%9)
									x=vfac[idh].gethabid(c,h);
								
						}
	actualizatela();
	if(x!=-1)
		cmddisb(x,idh);
}
void jogo::cmdg(int param1,int param2,int hid,int idh){
	int c,h,x=-1;
	for(c=0;c<vfac[idh].gettamveccid();c++)
				for(h=0;h<vfac[idh].getNumeroHab(c);h++){
					if(vfac[idh].verificahabitante(hid)==1)
						if(vfac[idh].gethabid(c,h)==hid && vfac[idh].gethabmove(c,h)==0&& vfac[idh].gethabtempo(c,h)==0){
							if(vfac[idh].getnomecidhab(c,h)!="NULL")
								vfac[idh].setnomecidhab(c,h,"NULL");
							if(vfac[idh].gethabmodo(c,h)==1)
								vfac[idh].irparaxy(c,h,vfac[idh].gethabdy(c,h),vfac[idh].gethabdx(c,h));
							else
								vfac[idh].irparaxy(c,h,param1,param2);
							vfac[idh].sethabflgmov(c,h,1);
							srand ((int)time(NULL));//inicializar o "randomizer"
							if(vfac[idh].gethabtipo(c,h)==2)
								if(1==rand()%9)
									x=vfac[idh].gethabid(c,h);
								
						}
			
				}
	if(x!=-1)
		cmddisb(x,idh);

}
void jogo::vaiparacidade(int idh,string nmcidade,int idf){
	int f,c,h;
	int destx=NULL,desty=NULL;

	for(f=0;f<vfac.size();f++)
		for(c=0;c<vfac[f].gettamveccid();c++){
			if(vfac[f].getnomecidade(c)==nmcidade){
				destx=vfac[f].getcidx(c);
				desty=vfac[f].getcidy(c);
			}
		}
		if(destx!=NULL && desty!=NULL)
			cmdg(destx,desty,idh,idf);
	
}
void jogo::apanhaart(int aid,int hid,int idh){
	int x;
	for(int a=0;a<vart.size();++a)
		if(vart[a]->getidartefacto()==aid){
			x=a;
			srand((int)time(NULL));
			int ar=vart[a]->getintipo();
			switch(ar){
				case 1:vfac[idh].addouro(vart[a]->accao());break;
				case 2:cmddisb(hid,idh);break;
				case 3:procuracid(a,idh,hid);break;
				case 4:desertar( hid, idh);break;
				case 5:vfac[idh].addcomida(vart[a]->accao());break;
				case 6: vfac[idh].setveccid(cidade("tubo de cola",vart[a]->getyartefacto(),vart[a]->getxartefacto()));
					for(int c=0;c<vfac[idh].gettamveccid();++c)
						 for(int h=0;h<vfac[idh].getNumeroHab(c);++h)
							 if(vfac[idh].gethabid(c,h)==hid)
								 vfac[idh].setnomecidhab(c,h,"tubo de cola"); break;
				case 7:producaoimediata(idh);break;
		}
	}
	vart.erase(vart.begin()+x);
}
void jogo::producaoimediata(int idh){
	for(int c=0;c<vfac[idh].gettamveccid();++c){
		for(int h=0;h<vfac[idh].getNumeroHab(c);++h)
			vfac[idh].sethabtempo(c,h,0);
	}
}
void jogo::procuracid(int a,int idh,int hid){
 int xi,yi,c,aux,id=0;
 if(vfac[idh].gettamveccid()>0){
  xi=vfac[idh].getcidx(0);
  yi=vfac[idh].getcidy(0);
  for(c=1;c<vfac[idh].gettamveccid();++c){
   aux=abs(vfac[idh].getcidx(c)-vart[a]->getxartefacto())+abs(vfac[idh].getcidy(c)-vart[a]->getyartefacto());
   if(aux<(xi+yi))
    id=c;
  }
  string newname;
  newname=vfac[idh].getnomecidade(id);
  newname+="DUP";//junta dup ao nome
  vfac[idh].setveccid(cidade(newname,vart[a]->getyartefacto(),vart[a]->getxartefacto()));
  int x;
  for(int i=0;i<vfac[idh].getNumeroHab(id);++i){
   x=vfac[idh].gethabtipo(id,i);
   switch(x){
    case 1:vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new campones(vart[a]->getxartefacto(),vart[a]->getyartefacto(),newname));break;
    case 2:vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new mineiro(vart[a]->getxartefacto(),vart[a]->getyartefacto(),newname));break;
    case 3:vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new soldado(vart[a]->getxartefacto(),vart[a]->getyartefacto(),newname));break;
    case 4:vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new heroi(vart[a]->getxartefacto(),vart[a]->getyartefacto(),newname));break;
    case 5:vfac[idh].addhabitante(vfac[idh].gettamveccid()-1,new catapulta(vart[a]->getxartefacto(),vart[a]->getyartefacto(),newname));break;
   }
   vfac[idh].sethabtempo(vfac[idh].gettamveccid()-1,i,0);
  }
  for(int c=0;c<vfac[idh].gettamveccid();++c)
   for(int h=0;h<vfac[idh].getNumeroHab(c);++h)
    if(vfac[idh].gethabid(c,h)==hid)
        vfac[idh].setnomecidhab(c,h,newname); 
 }
}
void jogo::desertar(int hid,int idh){
  for(int cc=0;cc<vfac[idh].gettamveccid();++cc)
   for(int h=0;h<vfac[idh].getNumeroHab(cc);++h)
    if(vfac[idh].gethabid(cc,h)==hid){
     int x=vfac[idh].gethabtipo(cc,h);
  int fa;
  srand((int)time(NULL));
  do{
   fa=rand()%vfac.size();
  }while(fa==idh);
   switch(x){
     case 1:vfac[fa].addhabitante(0,new campones(vfac[idh].gethabx(cc,h),vfac[idh].gethaby(cc,h)));break;
     case 2:vfac[fa].addhabitante(0,new mineiro(vfac[idh].gethabx(cc,h),vfac[idh].gethaby(cc,h)));break;
     case 3:vfac[fa].addhabitante(0,new soldado(vfac[idh].gethabx(cc,h),vfac[idh].gethaby(cc,h)));break;
     case 4:vfac[fa].addhabitante(0,new heroi(vfac[idh].gethabx(cc,h),vfac[idh].gethaby(cc,h)));break;
     case 5:vfac[fa].addhabitante(0,new catapulta(vfac[idh].gethabx(cc,h),vfac[idh].gethaby(cc,h)));break;
    }
   vfac[fa].sethabtempo(0,vfac[fa].getNumeroHab(0)-1,0);
    }
   
  cmddisb(hid,idh);  
}
void jogo::visao(int hid,int pf,int pc,int ph){
	int v=-1,x,y;
	v=vfac[pf].gethabvisao(pc,ph);
	x=vfac[pf].gethabx(pc,ph);
	y=vfac[pf].gethaby(pc,ph);
	for(int i=x-v;i<=x+v;++i)
		if(i>=0&&i<col)
			for(int j=y-v;j<=y+v;++j)
				if(j>=0&&j<row)
					if(mpostipo[j*col+i]==2){//verifica se é hab
						if(mposfac[j*col+i]!=vfac[pf].getid())//verifica se n é da mesma fac
							for(int u=0;u<vfac.size();++u)
								if(mposfac[j*col+i]==vfac[u].getid())//descobre qual é a facçao
									for(int cc=0;cc<vfac[u].gettamveccid();++cc)
										for(int hh=0;hh<vfac[u].getNumeroHab(cc);++hh){
											int xh=vfac[u].gethabx(cc,hh);
											int yh=vfac[u].gethaby(cc,hh);
											if(xh==i&&yh==j)//confere posiçao
												if((&vfac[pf])->gethabtipo(pc,ph)>2){
													atacahab(hid,vfac[u].gethabid(cc,hh));
												}else
													cmdg(vfac[pf].getcidy(pc),vfac[pf].getcidx(pc),hid,pf);
										}
					}else if(mpostipo[j*col+i]==3&&vfac[pf].gethabtipo(pc,ph)!=1&&vfac[pf].gethabtipo(pc,ph)!=4)
							cmdg(j,i,hid,pf);
}
void jogo::atacahab(int idhabataca,int idhabatacado){
 int f,c,h;
 int f1,c1,h1;
 int pfatc,pcatc,phatc;
 for(f=0;f<vfac.size();f++)
  for(c=0;c<vfac[f].gettamveccid();c++)
   for(h=0;h<vfac[f].getNumeroHab(c);h++)
    if(vfac[f].gethabid(c,h)==idhabataca){
     
	 for(f1=0;f1<vfac.size();f1++)
	  for(c1=0;c1<vfac[f1].gettamveccid();c1++)
	   for(h1=0;h1<vfac[f1].getNumeroHab(c1);h1++)
		if(vfac[f1].gethabid(c1,h1)==idhabatacado)
		 if(f1!=f){//significa que o hab a atacar nao e da mesma faccao
		  vfac[f].setidatak(c,h,vfac[f1].gethabid(c1,h1));
		  cmdg(vfac[f1].gethaby(c1,h1),vfac[f1].gethabx(c1,h1),idhabataca,f);
		 }
	}
}
int jogo::combate(int tphab1,int tphab2){

	int probv1,probv2;
	int p,p2;
	srand((int)time(NULL));
	switch(tphab1){
		case 1:
			probv1=0;
			break;
		case 2:
			probv1=20;
			break;
		case 3:
			probv1=75;
				break;
		case 4:
			probv1=100;
			break;
		case 5:break;
	}
	switch(tphab2){
		case 1:
			probv2=0;
			break;
		case 2:
			probv2=20;
			break;
		case 3:
			probv2=75;
				break;
		case 4:
			probv2=100;
			break;
		case 5:break;
	}
	p=rand()%100;
	if(p<probv1){
		p2=rand()%100;
		if(p2<probv2)
			return 3;
		else
			return 1;
	}
	else{
		p2=rand()%100;
		if(p2<probv2)
			return 2;
		else
			return 0;
	}

}
void jogo::randomartefacto(){
	int c=0,l=0,t=0;
	srand ((int)time(NULL));//inicializar o "randomizer"
	if(1==rand()%9){
		 c=rand()%col;
		 l=rand()%row;
		if(mpostipo[l*col+c]==0){
			t=rand()%6;
			switch(t){
				case 0:vart.push_back(new amoedas(c,l));break;
				case 1:vart.push_back(new amata(c,l));break;
				case 2:vart.push_back(new adup(c,l));break;
				case 3:vart.push_back(new adeserta(c,l));break;
				case 4:vart.push_back(new acomida(c,l));break;
				case 5:vart.push_back(new afunda(c,l));break;
				case 6:vart.push_back(new amist(c,l));break;
			}
		}
	}

}