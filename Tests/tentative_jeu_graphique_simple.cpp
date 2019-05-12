
//Doodles d'objets graphiques:
/*______________________________________________________________________________________________________________________________---
	Herbe: \/  \|/   /    \
	
	Oiseau:   -\~_  -_~_  -/~_  -¯~_  ou   -/~_  -\~_
	
	Chat:                           |
			\_-~~­^^    __-~~­^^      \-~~­^^    ou    \_»»»^^      ^^-~~-__
			  /\ /\       /\ /\        /\ /\                         // /\
			  
			\_«¯¯»^^    
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


//Code pour générer le jeu:
//_________________________________________________________________________________________________________________________________---

//Définition de l'environnement

#include <iostream>   //Pour les entrées/sorties
#include <conio.h>    //Pour enregistrer les pressages de touches
#include <stdlib.h>   //Pour les nombres aléatoires

#define _WIN32_WINNT 0x0500    //Nécessaire pour la taille de la fenêtre: informe qu'on est sur Windows 2000 ou plus récent
#include <windows.h>           //Nécessaire pour toute modification de la console sur Windows (utilie "Windows API")

using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

//----------------------------------------------------------------

//Création des dessins
	
	//Création du paysage
														// Les symboles \ et " sont précédés de \, pour les compter comme des characters
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

	//Création du chat:
	string c11a = ""          ;   string c11b = ""          ;   string c11c =  "|";           
	string c12a = "__.''.^^"   ;   string c12b = "\\_.''.^^"   ;   string c12c = "\\.''.^^";   
	string c13a =    "\\\\ \\/";  string c13b =    "/\\ /\\"   ; string c13c =   "// /\\";       //pour une démarche a-b-c-b-a-b-c-b-a... 
	
	string c21a = ""          ;   string c21b = ""          ;   string c21c =      "|";           
	string c22a = "^^.''.__"   ;   string c22b = "^^.''._/"   ;   string c22c = "^^.''./";   
	string c23a =  "// /\\";       string c23b =    "/\\ /\\"   ; string c23c =   "/\\ \\\\";      
		
	/*                                //Design alternatif
	string c11a = ""          ;   string c11b = ""          ;   string c11c =  "|";           
	string c12a = "__-~~­^^"   ;   string c12b = "\\_-~~­^^"   ;   string c12c = "\\-~~­^^";   
	string c13a =    "\\\\ \\/";  string c13b =    "/\\ /\\"   ; string c13c =   "// /\\";       
	
	string c21a = ""          ;   string c21b = ""          ;   string c21c =      "|";           
	string c22a = "^^-~~­__"   ;   string c22b = "^^-~~­_/"   ;   string c22c = "^^-~~­/";   
	string c23a =  "// /\\";       string c23b =    "/\\ /\\"   ; string c23c =   "/\\ \\\\";     
	*/

		//Mise en array du chat:
		//string c[3][3]; c[1] = {c1a,c1b,c1c} ; c[2] = {c2a,c2b,c2c} ; c[3] = {c3a,c3b,c3c;          //ne marche pas...
		/*
		string c11[3] = {c11a,c11b,c11c} ; string c12[3] = {c12a,c12b,c12c} ; string c13[3] = {c13a,c13b,c13c};  //Poche à travailler avec
		string c21[3] = {c21a,c21b,c21c} ; string c22[3] = {c22a,c22b,c22c} ; string c23[3] = {c23a,c23b,c23c};
		*/
		string c[2][3][3];                               //L'attribution de chaque valeur doit se faire dans main(), pour une raison inconnue à moi

//----------------------------------------------------------------
	
//Définition des paramètres de la console (Windows uniquement)       //Doit être placé hors de main() pour marcher!
	
	//Création des objets de console
	HWND consdim = GetConsoleWindow();                        //Objet permettant de modifier les dimensions + la position de la console
	HANDLE constxt = GetStdHandle(STD_OUTPUT_HANDLE);         //Objet permettant de modifier le texte affiché dans la console


//Définition des fonctions utilisées:
	
	//Fonction pour tirer des nombres aléatoires
	int aleat(int min=0, int max=100) {
		int nb = rand() % (max-min+1) + min ;
		return(nb);
		}	
	
	//Fonction pour déplacer le curseur sur la console
	COORD CursorPosition;                                     //Objet permettant de se situer sur la console
	void curspos(int x, int y) { 
		CursorPosition.X = x; CursorPosition.Y = y; 
		SetConsoleCursorPosition(constxt,CursorPosition); 
	}	

	//Fonction pour changer de couleur facilement
	void chgcol(string color) {
		WORD code;                                            //Voir la bibliothèque pour la légende
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

		//Définir les dimensions de l'image
		int nlin = 13;
		int ncol = 27;

		//Créer les objets de limites horizontales à l'image
		int maxlimfen = 94;                                         //Dernière position acceptée (juste avant l'espace-buffer) (120-26 = 94)
		int minlimfen = 0;
		int limfen = 0;                                           //Commencer à l'extrémité gauche de l'image  
                            //Pour obtenir la limite droite de l'image, simplement faire limfen + 26
		
		void affpays(void) {
			//Revenir au coin en haut à gauche de l'image
			curspos(0,0);
			//Dessiner tout le paysage
			for(int j=0; j<nlin ; j++) {
				int ilim = limfen + (ncol-1);                                 //Définir la limite au compteur i
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
				if(j<11) cout << " ";             //Ne pas descendre à la dernière ligne, pour ne pas faire bouger l'image        
			}
		}
		
	//Fonction pour afficher le chat
	
		//Déclarer les variables de position du chat qui seront utiles (tout ce qui est par rapport au chat sera inséré ici)
			//Position du centre du chat
			int mincposx = 6;                                    //Il y aura une marge de 7 entre le rebord de l'image et l'extrême gauche du chat
			int maxcposx = ncol - mincposx;
			int cposx = mincposx;                                //le chat commence à gauche de l'image   
			 
		    int mincposy = 8;
	        int maxcposy = 12;
			int cposy = 10;
						
			//Postures du chat
			int dir = 0;                                        //Par défaut, le chat est orienté vers la droite
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
	
	//Fonction pour se déplacer
	
		//Fonction pour recueillir ce qui a été pressé
		char deplac() {
			
			//Recueillir les touches pressées qui ont un sens ici
			char key = 127; key = _getch();                  //Enregistrer quelle touche a été pressée
			if (key == 0 || key == -32) {                    //La valeur est spéciale: elle nécessite de la ré-examiner
				key = _getch();                              //Re-prendre la valeur (elle change??)
				if (key == 75) key = 'a';       //flèche gauche
				else if (key == 77) key = 'd';  //flèche droite
				else if (key == 72) key = 'w';  //Flèche du haut
				else if (key == 80) key = 's';  //Flèche du bas
			}
			
			//Définir les changements de position
				bool bouge = FALSE;                                                                //Enregistre si le chat s'est déplacée	

				if (key=='a') {  //flèche gauche
					dir = 1;
					if(cposx==mincposx) {if(limfen>minlimfen) {limfen--; bouge = TRUE;} }           //Chat à l'extrême gauche : le paysage recule
					else {cposx--; bouge = TRUE;}                                                   //Le chat recule
				}
				else if (key =='d') {    //flèche droite
					dir = 0 ;
					if(cposx==maxcposx) {if(limfen<maxlimfen) {limfen++; bouge = TRUE;} }           //Chat à l'extrême droite : le paysage avance
					else {cposx++; bouge = TRUE;}                                                   //Le chat avance					
				}
				else if (key =='w') { //Flèche du haut
					if(cposy>mincposy) {cposy-- ; bouge = TRUE;}
				}
				else if (key =='s') { //Flèche du bas
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
				
			//Changer le paysage ou le chat si une flèche a été pressée
			if(bouge) {affpays(); affchat();}
			
			//Mettre le message de sortie
			if(limfen==maxlimfen) chgcol("blanc"); else chgcol("gris sombre"); 
			curspos(0,0) ; cout << "Pressez ESCAPE pour quitter";

			return(key);                                     //Retourne ce qui a été pressé; ESCAPE est la touche '27'
		}


//----------------------------------------------------------------
		
//Main
int main() {

	//Changement de taille et de place de la console                     //Doit être défini à l'intérieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(consdim, 500, 250, 200, 200, TRUE);                   //Les unités sont en pixels!
                                                                         //200x200 pixels = 13 lignes; 27 colonnes

	//Attribution des valeurs à l'array du chat                          //Doit être défini à l'intérieur du main() pour fonctionner!
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
	char touche;                            //déclaration de l'objet "de sortie"
	do{
		touche = deplac();
	} while(touche!=27);

	//Remettre le message de fin à la fin de l'image
	curspos(0,nlin);
}


//_________________________________________________________________________________________________________________________________---
//Bibliothèque:

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
		                                 //   0x : sert à annoncer le type (hexadécimale, deux données)
		                                 //   1er symbole après: sert pour le background.
		                                 //   2e symbole après: sert pour le texte (foreground)

		// ex: 0xF0 : blanc sur fond noir
	
	//Fonction pour recueillir ce qui a été pressé
		char getKeyPress() {
			char key = 127; key = _getch();                  //Enregistrer quelle touche a été pressée
			if (key == 0 || key == -32) { //get a special key
				key = _getch();                              //Re-prendre la valeur (elle change??)
				if (key == 72) key = 'U'; //up arrow
				else if (key == 75) key = 'L'; //left arrow
				else if (key == 77) key = 'R'; //right arrow
				else if (key == 80) key = 'D'; //down arrow
			}
			return key;
		}
		
	
	//Fonction pour tirer des nombres aléatoires
		template <class T>
		T runif(T min, T max) 
			{
			T random = rand() % (max-min+1) + min ;
			return(random);
			}			
