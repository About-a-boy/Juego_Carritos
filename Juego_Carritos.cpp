#include<iostream>
#include<conio.h>
#include<dos.h>
#include<windows.h>
#include<time.h>

#define ancho 100
#define largo 30
#define ancho_ganar 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4]={' ','±','±',' ',
                '±','±','±','±',
                ' ','±','±',' ',
                '±','±','±','±'};
int carPos = ancho_ganar/2;
int puntuacion=0;
void gotoxy(int x,int y){
    CursorPosition.X=x;
    CursorPosition.Y=y;
    SetConsoleCursorPosition(console,CursorPosition);
}
void setCursor(bool visible,DWORD size){
    if(size==0)
        size=20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible= visible;
    lpCursor.dwSize=size;
    SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){
	for(int i=0;i<ancho;i++){
		for(int j=0;j<17;j++){
			gotoxy(0+j,i);cout<<"�";
			gotoxy(ancho_ganar-j,i);cout<<"�";
		}
	}
	for(int i=0;i<ancho;i++){
		gotoxy(ancho,i);cout<<"�";
	}
}
void getEnemy(int ind){
	enemyX[ind]=17+rand()%(33);
}
void drawEnemy(int ind){
	if(enemyFlag[ind]==true){
	   gotoxy(enemyX[ind],enemyY[ind]);  cout<<"****";
	   gotoxy(enemyX[ind],enemyY[ind]+1);cout<<" ** ";
	   gotoxy(enemyX[ind],enemyY[ind]+2);cout<<"****";
	   gotoxy(enemyX[ind],enemyY[ind]+3);cout<<" ** ";
	}
}
void eraseEnemy(int ind){
	if(enemyFlag[ind]==true){
	   gotoxy(enemyX[ind],enemyY[ind]);  cout<<"    ";
	   gotoxy(enemyX[ind],enemyY[ind]+1);cout<<"    ";
	   gotoxy(enemyX[ind],enemyY[ind]+2);cout<<"    ";
	   gotoxy(enemyX[ind],enemyY[ind]+3);cout<<"    ";
	}
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind]=1;
	getEnemy(ind);
}
void drawCar(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			gotoxy(j+carPos,i+22);cout<<car[i][j];
		}
	}
}
void eraseCar(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			gotoxy(j+carPos,i+22);cout<<" ";
		}
	}	
}
int collision(){
	if(enemyY[0]+4>=23){
		if(enemyX[0]+4-carPos>=0 && enemyX[0]+4-carPos<9){
			return 1;
		}
	}
	return 0;
}

void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t----------------------"<<endl;
	cout<<"\t\t-------Game Over------"<<endl;
	cout<<"\t\t----------------------"<<endl<<endl;
	cout<<"\t\tPresiona cualquier tecla para ir al menu"<<endl;
	getch();
}
void updateScore(){
	gotoxy(ancho_ganar+7,5);cout<<" Puntuacion: "<<puntuacion<<endl;
}
void instrucciones(){
	system("cls");
	cout<<"\n\n\t\t\t\t\t\t\tInstrucciones\n\n";
	cout<<"\n------------------------------------------------------------------------------------------------------------------------";
	cout<<"\n\n\t\t\t\t\tEvita que el coche choque contra los obstaculos\n";
	cout<<"\n\t\t\t\t\tPresiona 'a' para moverlo a la izquierda\n";
	cout<<"\n\t\t\t\t\tPresiona 'b' para moverlo a la derecha\n";
	cout<<"\n\t\t\t\t\tPresiona 'Esc' para salir\n";
	cout<<"\n\t\t\t\t\tPresiona cualquier tecla para ir al menu\n";
	getch();
}
void play(){
	system("color 10");
	carPos= -1+ancho_ganar/2;
	puntuacion=0;
	enemyFlag[0]=1;
	enemyFlag[1]=0;
	enemyY[0]=enemyY[1]=1;
	
	system("cls");
	drawBorder();
	updateScore();
	getEnemy(0);
	getEnemy(1);
	
	gotoxy(ancho_ganar+10,2);cout<<"Car Game";
	gotoxy(ancho_ganar+6,4); cout<<"----------------";
	gotoxy(ancho_ganar+6,6); cout<<"----------------";
	gotoxy(ancho_ganar+7,12);cout<<"    Controles";
	gotoxy(ancho_ganar+7,13);cout<<"---------------------";
	gotoxy(ancho_ganar+2,14);cout<<"     Tecla A -> Izquierda";
	gotoxy(ancho_ganar+7,15);cout<<"Tecla D -> Derecha";
	
	gotoxy(18,5);cout<<"Presiona cualquier tecla para iniciar";
	getch();
	gotoxy(18,5);cout<<"                                     ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if(ch=='a'||ch=='A'){
			   if(carPos>18)
			   	carPos-=4;
			}
			if(ch=='d'||ch=='D'){
			   if(carPos<50)
				carPos+=4;
			}
			if(ch==27){
				break;
			}
		}
		drawCar();
		drawEnemy(0);
		drawEnemy(1);
		if(collision()==1){
			gameover();
			return;
		}
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);
		
		if(enemyY[0]==10)
			if(enemyFlag[1]==0)
			   enemyFlag[1]=1;
		
		if(enemyFlag[0]==1)
		   enemyY[0]+=1;
		
		if(enemyFlag[1]==1)
		   enemyY[1]+=1;
		   
		if(enemyY[0]>largo-4){
			resetEnemy(0);
			puntuacion++;
			updateScore();
		}
		if(enemyY[1]>largo-4){
			resetEnemy(1);
			puntuacion++;
			updateScore();
		}
	}
}
int main(){
	setCursor(0,0);
	srand((unsigned)time(NULL));
	do{
		system("cls");
		system("color 10");
		gotoxy(50,5); cout<<"---------------------";
		gotoxy(50,6); cout<<"|     Car Game      |";
		gotoxy(50,7); cout<<"---------------------";
		gotoxy(53,9); cout<<"1- Iniciar juego";
		gotoxy(53,10); cout<<"2- Instrucciones";
		gotoxy(53,11); cout<<"3- Quitar";
		gotoxy(50,13); cout<<"Selecciona una opcion ";
		char op = getche();
		if(op=='1')
			play();
		if(op=='2')
			instrucciones();
		if(op=='3')
			exit(0);
	}while(1);
	return 0;
}