
//Doodles d'objets graphiques:
/*______________________________________________________________________________________________________________________________---
	Herbe: \/  \|/   /    \
	
	Oiseau:   -\~_  -_~_  -/~_  -�~_  ou   -/~_  -\~_
	
	Chat:                           |
			\_-~~�^^    __-~~�^^      \-~~�^^    ou    \_���^^      ^^-~~-__
			  /\ /\       /\ /\        /\ /\                         // /\
			  
			\_����^^    
			  /\ /\  			  
			  
			  
	Nuage:  _        __      __        __     _
	       (_)     	(__)    (__B	  S__)   {_}
			  
	Paysage:
	                             ___                                                              |
	      __                    /   \                              __                             |
	    _/  \     ___          /     \____       _____            /  \___                         |
	   /     \___/   |        /           \     /     \__________/       \                        |
	__/	              \______/             \___/                          \______________________ |      
	                                                                                              |     //94 colonnes de longueur
	     "  " "    \/            .             .     \/        '           ' \/   \/      '       |     //(les lignes horizontales sont exclues
	\/    '  "  '      '    \/         \|/                   "     '          \|/  \/    .  \|/   |
	        \|/' '                                                   \|/         \/               |
	   \/      " '        .     \/          .    \|/          \/              '                   |
*/                                                               


//Code pour g�n�rer le jeu:
//_________________________________________________________________________________________________________________________________---

//D�finition de l'environnement

#include <iostream>   //Pour les entr�es/sorties
#include <conio.h>    //Pour enregistrer les pressages de touches
#include <stdlib.h>   //Pour les nombres al�atoires

#define _WIN32_WINNT 0x0500    //N�cessaire pour la taille de la fen�tre: informe qu'on est sur Windows 2000 ou plus r�cent
#include <windows.h>           //N�cessaire pour toute modification de la console sur Windows (utilie "Windows API")

using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)

//----------------------------------------------------------------

//Cr�ation des dessins
	
	//Cr�ation du paysage
														// Les symboles \ et " sont pr�c�d�s de \, pour les compter comme des characters
	 string p0 = "                            _                         _____          (__)           ____                    (_)         ";
	 string p1 = "                           (_)            __         (     )                      _(    )           __                  ";
	 string p2 = "             __                          (__)         (____)                    _(     )           (  )                 ";
	 string p3 = "            (__)             ___                                               (_______)          (___)                 ";
	 string p4 = "      __                    /   \\                              __                                                  ___  ";
	 string p5 = "    _/  \\     ___          /     \\____       _____            /  \\___                                             |FIN| ";
	 string p6 = "   /     \\___/   |        /           \\     /     \\__________/       \\                                              |   ";
	 string p7 = "__/               \\______/             \\___/                          \\_____________________________________________|__ ";
	 string p8 = "                                                                                                                    |   ";
	 string p9 = "     \"  \" \"    \\/            .             .     \\/        '           ' \\/   \\/      '       . \'     .             |   ";
	string p10 = "\\/    '  \"  '      '    \\/         \\|/                   \"     '          \\|/  \\/    .  \\|/    \"                \\/  |   ";
	string p11 = "        \\|/' '                                                   \\|/         \\/                     .   \\/   '   \"      ";
	string p12 = "   \\/      \" '        .     \\/          .    \\|/          \\/              '                  \"          \\|/             ";

					//13 lignes de hauteur, 
					//120 colonnes de longueur (sans les '\' en surplus)

		//Mise en array du paysage:
		string paysage[13] = {p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12}; 

	//Cr�ation du chat:
	string c11a = ""          ;   string c11b = ""          ;   string c11c =  "|";           
	string c12a = "__.''.^^"   ;   string c12b = "\\_.''.^^"   ;   string c12c = "\\.''.^^";   
	string c13a =    "\\\\ \\/";  string c13b =    "/\\ /\\"   ; string c13c =   "// /\\";       //pour une d�marche a-b-c-b-a-b-c-b-a... 
	
	string c21a = ""          ;   string c21b = ""          ;   string c21c =      "|";           
	string c22a = "^^.''.__"   ;   string c22b = "^^.''._/"   ;   string c22c = "^^.''./";   
	string c23a =  "// /\\";       string c23b =    "/\\ /\\"   ; string c23c =   "/\\ \\\\";      
		
	/*                                //Design alternatif
	string c11a = ""          ;   string c11b = ""          ;   string c11c =  "|";           
	string c12a = "__-~~�^^"   ;   string c12b = "\\_-~~�^^"   ;   string c12c = "\\-~~�^^";   
	string c13a =    "\\\\ \\/";  string c13b =    "/\\ /\\"   ; string c13c =   "// /\\";       
	
	string c21a = ""          ;   string c21b = ""          ;   string c21c =      "|";           
	string c22a = "^^-~~�__"   ;   string c22b = "^^-~~�_/"   ;   string c22c = "^^-~~�/";   
	string c23a =  "// /\\";       string c23b =    "/\\ /\\"   ; string c23c =   "/\\ \\\\";     
	*/

		//Mise en array du chat:
		//string c[3][3]; c[1] = {c1a,c1b,c1c} ; c[2] = {c2a,c2b,c2c} ; c[3] = {c3a,c3b,c3c;          //ne marche pas...
		/*
		string c11[3] = {c11a,c11b,c11c} ; string c12[3] = {c12a,c12b,c12c} ; string c13[3] = {c13a,c13b,c13c};  //Poche � travailler avec
		string c21[3] = {c21a,c21b,c21c} ; string c22[3] = {c22a,c22b,c22c} ; string c23[3] = {c23a,c23b,c23c};
		*/
		string c[2][3][3];                               //L'attribution de chaque valeur doit se faire dans main(), pour une raison inconnue � moi

//----------------------------------------------------------------
	
//D�finition des param�tres de la console (Windows uniquement)       //Doit �tre plac� hors de main() pour marcher!
	
	//Cr�ation des objets de console
	HWND consdim = GetConsoleWindow();                        //Objet permettant de modifier les dimensions + la position de la console
	HANDLE constxt = GetStdHandle(STD_OUTPUT_HANDLE);         //Objet permettant de modifier le texte affich� dans la console


//D�finition des fonctions utilis�es:
	
	//Fonction pour tirer des nombres al�atoires
	int aleat(int min=0, int max=100) {
		int nb = rand() % (max-min+1) + min ;
		return(nb);
		}	
	
	//Fonction pour d�placer le curseur sur la console
	COORD CursorPosition;                                     //Objet permettant de se situer sur la console
	void curspos(int x, int y) { 
		CursorPosition.X = x; CursorPosition.Y = y; 
		SetConsoleCursorPosition(constxt,CursorPosition); 
	}	

	//Fonction pour changer de couleur facilement
	void chgcol(string color) {
		WORD code;                                            //Voir la biblioth�que pour la l�gende
		if(color=="vert sombre") code = 0x02;         
			else if(color=="rouge sombre") code = 0x04;
			else if(color=="brun") code = 0x06;
			else if(color=="gris") code = 0x07;
			else if(color=="gris sombre") code = 0x08;
			else if(color=="vert") code = 0x0A;
			else if(color=="cyan") code = 0x0B;
			else if(color=="rouge") code =0x0C;
			else if(color=="blanc") code =0x0F;
		SetConsoleTextAttribute(constxt, code);}
	
	//Fonction pour afficher le paysage                

		//D�finir les dimensions de l'image
		int nlin = 13;
		int ncol = 27;

		//Cr�er les objets de limites horizontales � l'image
		int maxlimfen = 94;                                         //Derni�re position accept�e (juste avant l'espace-buffer) (120-26 = 94)
		int minlimfen = 0;
		int limfen = 0;                                           //Commencer � l'extr�mit� gauche de l'image  
                            //Pour obtenir la limite droite de l'image, simplement faire limfen + 26
		
		void affpays(void) {
			//Revenir au coin en haut � gauche de l'image
			curspos(0,0);
			//Dessiner tout le paysage
			for(int j=0; j<nlin ; j++) {
				int ilim = limfen + (ncol-1);                                 //D�finir la limite au compteur i
				if(j<4) {                              //Background de nuages                  
					chgcol("blanc"); 
					for(int i=limfen; i<ilim ; i++) cout << (paysage[j]) [i];              
				}
				else if(j<8) {                         //Background de montagnes
					for(int i=limfen; i<ilim ; i++) {
						char symbole = (paysage[j]) [i]; 
						if(symbole == 'F' | symbole == 'I' | symbole == 'N') SetConsoleTextAttribute(constxt, 0xCF);   //Texte blanc, fond rouge
	                    else chgcol("brun");                                    //Montagnes      
						cout << symbole;
					}
				}
				else {                                 //Herbes et cailloux
					for(int i=limfen; i<ilim ; i++) {
						char symbole = (paysage[j]) [i]; 
						if(symbole == '\'' | symbole == '\"' ) chgcol("vert");   //petites herbes
						else if(symbole == '.') chgcol("gris");                  //cailloux
						else chgcol("vert sombre");                              //grandes herbes
						cout << symbole;
					}	
				}	
				if(j<11) cout << " ";             //Ne pas descendre � la derni�re ligne, pour ne pas faire bouger l'image        
			}
		}
		
	//Fonction pour afficher le chat
	
		//D�clarer les variables de position du chat qui seront utiles (tout ce qui est par rapport au chat sera ins�r� ici)
			//Position du centre du chat
			int mincposx = 6;                                    //Il y aura une marge de 7 entre le rebord de l'image et l'extr�me gauche du chat
			int maxcposx = ncol - mincposx;
			int cposx = mincposx;                                //le chat commence � gauche de l'image   
			 
		    int mincposy = 8;
	        int maxcposy = 12;
			int cposy = 10;
						
			//Postures du chat
			int dir = 0;                                        //Par d�faut, le chat est orient� vers la droite
			int posture = 1;
			int pattes = 1;
			
			int dirpattes = 1;                            //Direction de changement dans la posture des pattes	

			//Autres variables utiles au chat
			const int longcorps = 8;
			const int longpattes = 5;
	
		void affchat(void) {
			//Mettre le chat de couleur cyan:
			chgcol("cyan");
			
	        //Dessiner la queue:
			if(posture==2) {
				if(dir==1) curspos(cposx+3,cposy-1); else curspos(cposx-3,cposy-1);
				cout << c[1][0][2];
			}
						
			//Dessiner le corp:
			curspos(cposx-3,cposy); cout << c[dir][1][posture];
			
			//Dessiner les pattes:
			curspos(cposx-2,cposy+1); cout << c[dir][2][pattes];
		}
	
	//Fonction pour se d�placer
	
		//Fonction pour recueillir ce qui a �t� press�
		char deplac() {
			
			//Recueillir les touches press�es qui ont un sens ici
			char key = 127; key = _getch();                  //Enregistrer quelle touche a �t� press�e
			if (key == 0 || key == -32) {                    //La valeur est sp�ciale: elle n�cessite de la r�-examiner
				key = _getch();                              //Re-prendre la valeur (elle change??)
				if (key == 75) key = 'a';       //fl�che gauche
				else if (key == 77) key = 'd';  //fl�che droite
				else if (key == 72) key = 'w';  //Fl�che du haut
				else if (key == 80) key = 's';  //Fl�che du bas
			}
			
			//D�finir les changements de position
				bool bouge = FALSE;                                                                //Enregistre si le chat s'est d�plac�e	

				if (key=='a') {  //fl�che gauche
					dir = 1;
					if(cposx==mincposx) {if(limfen>minlimfen) {limfen--; bouge = TRUE;} }           //Chat � l'extr�me gauche : le paysage recule
					else {cposx--; bouge = TRUE;}                                                   //Le chat recule
				}
				else if (key =='d') {    //fl�che droite
					dir = 0 ;
					if(cposx==maxcposx) {if(limfen<maxlimfen) {limfen++; bouge = TRUE;} }           //Chat � l'extr�me droite : le paysage avance
					else {cposx++; bouge = TRUE;}                                                   //Le chat avance					
				}
				else if (key =='w') { //Fl�che du haut
					if(cposy>mincposy) {cposy-- ; bouge = TRUE;}
				}
				else if (key =='s') { //Fl�che du bas
					if(cposy<maxcposy) {cposy++ ; bouge = TRUE;}
				}
			//Recueillir les changements de posture
				//les pattes
				if(bouge) {
					if(pattes==0) {dirpattes = 1;}
					else if(pattes==2) {dirpattes = -1;}
					pattes += dirpattes;
				}	
				//La posture
				if(aleat(0,100)<40){                                     //Ne change de posture tout le temps
					if(posture==0) posture++;
					else if(posture==1) {if(aleat(0,100)<35) posture++; else posture--;}           //plus de chances de baisser la queue
					else posture--;
				}
				
			//Changer le paysage ou le chat si une fl�che a �t� press�e
			if(bouge) {affpays(); affchat();}
			
			//Mettre le message de sortie
			if(limfen==maxlimfen) chgcol("blanc"); else chgcol("gris sombre"); 
			curspos(0,0) ; cout << "Pressez ESCAPE pour quitter";

			return(key);                                     //Retourne ce qui a �t� press�; ESCAPE est la touche '27'
		}


//----------------------------------------------------------------
		
//Main
int main() {

	//Changement de taille et de place de la console                     //Doit �tre d�fini � l'int�rieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(consdim, 500, 250, 200, 200, TRUE);                   //Les unit�s sont en pixels!
                                                                         //200x200 pixels = 13 lignes; 27 colonnes

	//Attribution des valeurs � l'array du chat                          //Doit �tre d�fini � l'int�rieur du main() pour fonctionner!
		c[0][0][0] = c11a ; c[0][0][1] = c11b ; c[0][0][2] = c11c ;      //[droite/gauche][queue/corps/pattes][posture]
		c[0][1][0] = c12a ; c[0][1][1] = c12b ; c[0][1][2] = c12c ;
		c[0][2][0] = c13a ; c[0][2][1] = c13b ; c[0][2][2] = c13c ;
		c[1][0][0] = c21a ; c[1][0][1] = c21b ; c[1][0][2] = c21c ;
		c[1][1][0] = c22a ; c[1][1][1] = c22b ; c[1][1][2] = c22c ;
		c[1][2][0] = c23a ; c[1][2][1] = c23b ; c[1][2][2] = c23c ;	

	//Afficher le chat et le paysage, et le message d'instruction
	affpays() ; affchat() ; 
	chgcol("blanc") ; curspos(0,0) ; cout << "Utilisez les fleches du clavier pour deplacer le chat";
	
	//Faire bouger le chat
	char touche;                            //d�claration de l'objet "de sortie"
	do{
		touche = deplac();
	} while(touche!=27);

	//Remettre le message de fin � la fin de l'image
	curspos(0,nlin);
}


//_________________________________________________________________________________________________________________________________---
//Biblioth�que:

	//Pour le changement de couleur:   
		/*
		0   BLACK
		1   BLUE
		2   GREEN
		3   CYAN
		4   RED
		5   MAGENTA
		6   BROWN
		7   LIGHTGRAY
		8   DARKGRAY
		9   LIGHTBLUE
		A  LIGHTGREEN         (10)
		B  LIGHTCYAN          (11)
		C  LIGHTRED           (12)
		D  LIGHTMAGENTA       (13)
		E  YELLOW             (14)
		F  WHITE              (15)
		*/
		                                 //   0x : sert � annoncer le type (hexad�cimale, deux donn�es)
		                                 //   1er symbole apr�s: sert pour le background.
		                                 //   2e symbole apr�s: sert pour le texte (foreground)

		// ex: 0xF0 : blanc sur fond noir
	
	//Fonction pour recueillir ce qui a �t� press�
		char getKeyPress() {
			char key = 127; key = _getch();                  //Enregistrer quelle touche a �t� press�e
			if (key == 0 || key == -32) { //get a special key
				key = _getch();                              //Re-prendre la valeur (elle change??)
				if (key == 72) key = 'U'; //up arrow
				else if (key == 75) key = 'L'; //left arrow
				else if (key == 77) key = 'R'; //right arrow
				else if (key == 80) key = 'D'; //down arrow
			}
			return key;
		}
		
	
	//Fonction pour tirer des nombres al�atoires
		template <class T>
		T runif(T min, T max) 
			{
			T random = rand() % (max-min+1) + min ;
			return(random);
			}			
