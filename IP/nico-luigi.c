// Luigi Tramontin de Paula 12727987 / Nicoly G S Alfenas 12696607
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define VALOR_MAXIMO 255
#define RETA "RETA"
#define RETANGULO_CONTORNO "RETANGULO_CONTORNO"
#define RETANGULO_PREENCHIDO "RETANGULO_PREENCHIDO"
#define CLONA "CLONA"
#define CLONA_INV "CLONA_INV"
#define CLONA_HOR "CLONA_HOR"
#define CLONA_VER "CLONA_VER"
#define FIM "FIM"

typedef struct{
	int alt;
	int larg;
	int **mtz;
} Img;

typedef struct{
	int x;
	int y;
} Ponto2D;

void clnEspVert(Img *img,Ponto2D p01,Ponto2D p02,Ponto2D p3)
{
	int dx=p01.x>p02.x?p01.x-p02.x:p02.x-p01.x;
	int dy=p01.y>p02.y?p01.y-p02.y:p02.y-p01.y;
	int xc=p3.x;
	int yc=p3.y+dy;
	for (int i=0;i<=dy;i++){
		for (int j=0;j<=dx;j++)
		{
			img->mtz[yc-i][xc+j]=img->mtz[p01.y+i][p01.x+j];
		}
	}
}

void line(Img *img,Ponto2D p01,Ponto2D p02,int cor){
	int dx=abs(p01.x-p02.x),sx=p01.x<p02.x?1:-1;
	int dy=-abs(p02.y-p01.y),sy=p01.y<p02.y?1:-1;
	int err=dx+dy,e2;
	for (;;){
		img->mtz[p01.y][p01.x]=cor;
		if (p01.x==p02.x && p01.y==p02.y)
			break;
		e2=2*err;
		if (e2>=dy){
			err+=dy;
			p01.x+=sx;
		}
		if (e2<=dx){
			err+=dx;
			p01.y+=sy;
		}
	}
}

void l_img(Img *img){
	int lin;
	for (lin=0;lin<img->alt;lin++)
		free(img->mtz[lin]);
	free(img->mtz);
	free(img);
}

void save(Img *img,char *nArq){
	int lin,col;
	FILE *out=fopen(nArq,"w");
	if (out){
		fprintf(out,"P2\n%d %d\n%d\n",img->larg,img->alt,VALOR_MAXIMO);
		for (lin=0;lin<img->alt;lin++){
			for (col=0;col<img->larg;col++){
				fprintf(out,(col==0?"%d":" %d"),img->mtz[lin][col]);
			}
			fprintf(out,"\n");
		}
	}
	fclose(out);
}

void retCont(Img *img,Ponto2D p01,Ponto2D p02,int cor){
	Ponto2D pq;
	pq.x=p02.x;
	pq.y=p01.y;
	Ponto2D pr;
	pr.x=p01.x;
	pr.y=p02.y;
	line(img,p01,pq,cor);
	line(img,p01,pr,cor);
	line(img,p02,pq,cor);
	line(img,p02,pr,cor);
}

Img *new_img(int larg,int alt){
	Img *img=(Img *)malloc(sizeof(Img));
	img->alt=alt;
	img->larg=larg;
	img->mtz=(int **)malloc(alt*sizeof(int *));
	for (int i=0;i<alt;i++){
		img->mtz[i]=(int *)malloc(larg*sizeof(int *));
		for (int j=0;j<larg;j++){
			img->mtz[i][j]=0;
		}
	}
	return img;
}

void retPre(Img *img,Ponto2D p01,Ponto2D p02,int cor){
	Ponto2D mr=p01.x>p02.x?p01:p02;
	Ponto2D mnr=p01.x<p02.x?p01:p02;
	Ponto2D pr;
	pr.x=mnr.x;
	pr.y=mr.y;
	Ponto2D pq;
	pq.x=mnr.x;
	pq.y=mnr.y;
	for (;;){
		line(img,pq,pr,cor);
		if (pq.x==mr.x){
			line(img,pq,pr,cor);
			break;
		}
		pq.x++;
		pr.x++;
	}
}

void cln(Img *img,Ponto2D p01,Ponto2D p02,Ponto2D p3){
	int dx=p01.x>p02.x?p01.x-p02.x:p02.x-p01.x;
	int dy=p01.y>p02.y?p01.y-p02.y:p02.y-p01.y;
	for (int i=0;i<=dx;i++){
		for (int j=0;j<=dy;j++){
			img->mtz[p3.y+j][p3.x+i]=img->mtz[j][i];
		}
	}
}

void clnEspHor(Img *img,Ponto2D p01,Ponto2D p02,Ponto2D p3){
	int dx=p01.x>p02.x?p01.x-p02.x:p02.x-p01.x;
	int dy=p01.y>p02.y?p01.y-p02.y:p02.y-p01.y;
	int xc=p3.x+dx;
	int yc=p3.y;
	for (int i=0;i<=dx;i++){
		for (int j=0;j<=dy;j++){
			img->mtz[yc+j][xc-i]=img->mtz[p01.y+j][p01.x+i];
		}
	}
}

void clnInvCor(Img *img,Ponto2D p01,Ponto2D p02,Ponto2D p3){
	int dx=p01.x>p02.x?p01.x-p02.x:p02.x-p01.x;
	int dy=p01.y>p02.y?p01.y-p02.y:p02.y-p01.y;
	int cor=0;
	for (int i=0;i<=dx;i++){
		for (int j=0;j<=dy;j++){
			cor=VALOR_MAXIMO-img->mtz[j][i];
			img->mtz[p3.y+j][p3.x+i]=cor;
		}
	}
}

int main(){
	int larg,alt,cor;
	char opc[32],n_arq[256];
	Img *img;
	Ponto2D p01;
	Ponto2D p02;
	Ponto2D p3;
	scanf("%s %d %d",n_arq,&larg,&alt);
	img=new_img(larg,alt);
	while (scanf("%s",opc)==1 && strcmp(opc,"FIM") != 0){
		p01.x=0,p01.y=0,p02.x=0,p02.y=0,cor=0;
		if (strcmp(opc,RETA)==0){
			scanf("%d %d %d %d %d",&p01.x,&p01.y,&p02.x,&p02.y,&cor);
			line(img,p01,p02,cor);
		}
		else if (strcmp(opc,RETANGULO_CONTORNO)==0){
			scanf("%d %d %d %d %d",&p01.x,&p01.y,&p02.x,&p02.y,&cor);
			retCont(img,p01,p02,cor);
		}
		else if (strcmp(opc,RETANGULO_PREENCHIDO)==0){
			scanf("%d %d %d %d %d",&p01.x,&p01.y,&p02.x,&p02.y,&cor);
			retPre(img,p01,p02,cor);
		}
		else{
			p3.x=0;
			p3.y=0;
			if (strcmp(opc,CLONA)==0){
				scanf("%d %d %d %d %d %d",&p01.x,&p01.y,&p02.x,&p02.y,&p3.x,&p3.y);
				cln(img,p01,p02,p3);
			}
			else if (strcmp(opc,CLONA_HOR)==0){
				scanf("%d %d %d %d %d %d",&p01.x,&p01.y,&p02.x,&p02.y,&p3.x,&p3.y);
				clnEspHor(img,p01,p02,p3);
			}
			else if (strcmp(opc,CLONA_INV)==0){
				scanf("%d %d %d %d %d %d",&p01.x,&p01.y,&p02.x,&p02.y,&p3.x,&p3.y);
				clnInvCor(img,p01,p02,p3);
			}
			else if (strcmp(opc,CLONA_VER)==0){
				scanf("%d %d %d %d %d %d",&p01.x,&p01.y,&p02.x,&p02.y,&p3.x,&p3.y);
				clnEspVert(img,p01,p02,p3);
			}
			else
				continue;
		}
	}
	save(img,n_arq);
	l_img(img);
	return 0;
}
