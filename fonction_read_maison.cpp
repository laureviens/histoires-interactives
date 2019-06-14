/*
			///||================================---2018/06/10---================================||\\\
\\\||================================---Fonction read() pour cr�er des outputs � partir des canaux de lecture---================================||///
*/

//Debbugg: pour avoir l'option de "sleep"
#include <unistd.h>

		//ATTENTION!!!!!		
				//Je viens de me rendre compte que, de la mani�re dont je calcule les lignes, �a ressemble �:
				/*
				 0 1 2 3 4 5 6 7 8 
				0
				1
				2
				3
				4
				5
				6
						ce qui peut �tre m�langeant pour l'axe des y. Just bear with me, though, j'pense que c'est la m�thode la plus simple.
				*/

//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entr�es/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round()
#include <chrono>     //Pour avoir un meilleur contr�le du temps (en millisecondes)
#define _WIN32_WINNT 0x0500    //N�cessaire pour la taille de la fen�tre: informe qu'on est sur Windows 2000 ou plus r�cent
#include <windows.h>           //N�cessaire pour toute modification de la console sur Windows (utilie "Windows API")
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)

# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/classe_vect_maison.cpp"  //Pour les vecteurs maisons

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) D�finir les objets de base sur lesquels va s'appuyer la suite
	
		//ix) Fonction : timems ; avoir le temps actuel en millisecondes (depuis l'epoch, soit 1er janvier 1970)
	int timems (void) {
		return(std::chrono::duration_cast< std::chrono::milliseconds >(
	    std::chrono::system_clock::now().time_since_epoch()
	).count());
	}	
	
	//i) Classe : canal ; permet de sauvegarder la position de lecture du canal, le texte restant � lire, la vitesse, etc.
	class canal {
		//Membres
		public:
			int nxtt;           //D�clarer le moment o� la prochaine entr�e sera trait�e         
			int delay;          //D�clarer le d�lai de base entre chaque entr�e
			int posx, posy;		//D�clarer les coordonn�es de la derni�re entr�e dans la m�moire (la pr�c�dente)   
								//les positions de la consoles sont d�finies en d�calant ces derni�res
			StringAsVect txt;   //D�clarer le texte qui reste � lire  				
			bool actif;			//D�clarer le compteur d'activit�
			double vit;         //D�clarer la vitesse actuelle de d�filement et de pauses (toujours par rapport � la base, 1)
		//Constructeur
		canal() {nxtt = timems() ; delay = 400 ; posx = 1; posy = 1; actif = false; vit = 1;}  //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
	};

	//ii) Classe : fen ; permet de sauvegarder les param�tres relatifs aux caract�ristiques de la fen�tre de sortie (console)
	class fen {
		//Membres
		public:
			int charx, chary;     //D�clarer les dimensions de la fen�tre en terme de nombre de caract�res pouvant y �tre contenus
			int consy;             //D�clarer le facteur de d�calement de la console o� appara�t le texte avec la m�moire, o� il est stock�
			bool refoule;          //D�clarer le flag pour voir si le facteur de d�calement entre en compte
		//Constructeurs
		fen() {charx = 1; chary = 1; consy = 0; refoule = false;}      //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
					//� RETRAVAILLER POUR Y METTRE UNE FONCTION PERMETTANT DE DEVINER AUTOMATIQUEMENT LES DIMENSIONS DE LA FEN�TRE!
		fen(int x, int y) {charx = x; chary = y; consy = 0; refoule = false;}      //Cr�er un constructeur permettant d'assigner manuellement les dimensions de la fen�tre	
	};
		//Cr�er l'objet base, qui contiendra les information sur la fen�tre de base
		fen base(27,13);     //EN CE MOMENT, A LES DIMENSIONS DE 27 COLONNES ET 13 LIGNES (VOIR JEU GRAPHIQUE SIMPLE)

	//iii) classe : memoire ; permet de sauvegarder la "m�moire" de la console, c'est-�-dire tous le texte s'y �tant d�j� inscrit
		class memoire{
			//Membres
			public: 
				int nbligne;
				char** souvenir;            //L'objet contient, en fa�ades, des pointeurs pointant � d'autres pointeurs
			//Constructeur par d�faut
			memoire() {
				nbligne = 1;                         //Ce qui suit semble �tre la seule mani�re de cr�er des arrays dynamiques
				souvenir = new char* [base.charx];   //Cr�er un premier array contenant des pointers
				for(int col=0; col<base.charx ; col++) {souvenir[col] = new char [nbligne];}    //Cr�er les lignes pour chaque colonne
			}
			//Destructeur
			~memoire() {
				for(int col=0; col<base.charx ; col++) delete[] souvenir[col] ; delete[] souvenir;   //Bien d�construire tout proprement
			}
			//Fonction d'acc�s : retourner certaines positions
			char acces (int posx, int posy) { //Cr�er une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(souvenir[posx][posy]);
			}
			//Fonction de modification : ajouter une ligne � la suite de la position sp�cifi�e (Op�rateur +) 
			void operator + (int pos) {
				int emptypos = pos + 1;   //Calculer la position qui sera vide
				char** nwsouv = new char* [base.charx] ; for(int xpos = 0; xpos<base.charx ; xpos++) {nwsouv [xpos] = new char [nbligne+1];}  //D�clarer le nouvel array (transitoire)
				int oldpos = 0;  //D�clarer un compteur pour les vieilles positions				
				for(int nwpos=0; nwpos < nbligne; nwpos++) {  //Remplir, en laissant une position vide
					if(nwpos==emptypos) {continue;} 
					for(int xpos = 0; xpos<base.charx ; xpos++) {nwsouv[xpos][nwpos] = souvenir[xpos][oldpos];}
					oldpos++;
				}
				nbligne++;   //Noter qu'on ajoute une ligne
				for(int col=0; col<base.charx ; col++) delete[] souvenir[col] ; delete[] souvenir;  //�liminer le vieil array   
				souvenir = nwsouv;  //Assigner le pointeur � l'array actuel
				for(int col=0; col<base.charx ; col++) delete[] nwsouv[col] ; delete[] nwsouv;  //�liminer l'array transitoire
			}
		};
		memoire mem;

	//iv) Fonction : cdsppos ; retourne la position des caract�res du code sp�cial      //DEBUGGING: CE TYPE RESSORT PAS COMME UN VECT<INT>?????
	vect<int> cdspposition(StringAsVect str){
		vect<int> pos = 0;              //Initier l'objet � retourner
		int a = 1;                      //Commencer � la position [1], le [0] �tant occup� par '�' (et d�j� comptabilis�)
		while(str[a]!='�'&a<str.nb) pos += a;
		return(pos);		
	}

	//v) Fonction : cdspxtr ; extrait une valeur double d'une suite de caract�res encadr�s par '�' (pour extraire les codes sp�ciaux)
	double cdspxtr(StringAsVect str, int cdspnb){
		string nbonly;                  //Initier un string, dans lequel ins�rer seulement les chiffres
		int a = 2;                      //Commencer � la position [2], le [0] �tant occup� par '�' et le [1] par le type de valeur � extraire
		while(a<cdspnb) {nbonly += str[a];}
		return(stod(nbonly));           //La fonction stod convertit les strings en doubles (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}				

				//BTW: POURRAIT FACILEMENT DEVENIR UN TEMPLATE! (ex: pour retourner des int, � la place)
				
	//vi) Objet : canaux ; assemblage de tous les canaux utilis�s
	vect<canal> canaux;

	//vii) Objets : TxtConsole et CursorPosition ; permet de modifier le texte affich� dans la console   		//WINDOWS ONLY
	HANDLE TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);        //Objet permettant de modifier le texte affich� dans la console 
	COORD CursorPosition;                                     	//Objet permettant de se situer sur la console

	//viii) Fonction: curspos ; d�placer le curseur sur la console
	void curspos(int x, int y) { 
		CursorPosition.X = x; CursorPosition.Y = y; 
		SetConsoleCursorPosition(TxtConsole,CursorPosition);            //WINDOWS ONLY
	}	
	
	//x) Fonction : out ; affiche le caract�re dans la console
	void out(char lettre){
		if(lettre=='�') std::wcout << L"\u00C0";
		else if(lettre=='�') std::wcout << L"\u00E0";
		else if(lettre=='�') std::wcout << L"\u00C7";		
		else if(lettre=='�') std::wcout << L"\u00E7";
		else if(lettre=='�') std::wcout << L"\u00C9";		
		else if(lettre=='�') std::wcout << L"\u00E9";
		else if(lettre=='�') std::wcout << L"\u00C8";
		else if(lettre=='�') std::wcout << L"\u00E8";
		else if(lettre=='�') std::wcout << L"\u00CE";
		else if(lettre=='�') std::wcout << L"\u00EE";
		else if(lettre=='�') std::wcout << L"\u00CF";
		else if(lettre=='�') std::wcout << L"\u00EF";						
		else if(lettre=='�') std::wcout << L"\u00D4";
		else if(lettre=='�') std::wcout << L"\u00F4";
		else if(lettre=='�') std::wcout << L"\u00D9";
		else if(lettre=='�') std::wcout << L"\u00F9";	
		else if(lettre=='�') std::wcout << L"\u00DB";
		else if(lettre=='�') std::wcout << L"\u00FB";	
		else {std::wcout << lettre;}
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) �crire la fonction read()
read(canal& can) {
	//Updater le "next time"
	can.nxtt += can.delay;
	//Interpr�ter les "codes sp�ciaux" (�...�)
	if(can.txt[0]=='�'){		
		//D�terminer la position du code sp�cial
		vect<int> cdsppos = cdspposition(can.txt);	
		//Lire le code sp�cial		
			if(can.txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause � la lecture
				double val = cdspxtr(can.txt,cdsppos.nb);       //Extraire le temps que durera la pause
				can.nxtt += round(val * can.vit);                    //Ajouter le temps d'attente        //round() est n�cessaire pour arrondir correctement					
			} else if(can.txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = cdspxtr(can.txt,cdsppos.nb);       //Extraire la nouvelle vitesse
				can.vit = val;
			}  //EN AJOUTER UN (code sp�cial) POUR PLACER LE CURSEUR � LA FIN DE LA CONSOLE		
		//Effacer le code sp�cial du canal
		can.txt-cdsppos;                       
	} else {  //Interpr�ter le reste des caract�res (pas des codes sp�ciaux)
		//Dealer avec la situation o� on a � sauter une ligne (cr�er les lignes suppl�mentaires et updater les diverses positions)
			bool jump = false;
			if(can.txt[0]=='\n'|can.posx>=base.charx) jump = true;
			if(jump) {
				//Sauter une ligne dans la m�moire
				for(int countx = can.posx + 1; countx < base.charx ; countx++) mem.souvenir[countx][can.posy] = ' ';     //Effacer le reste de la ligne avec des espaces    
				mem + can.posy;                         //Cet op�rateur introduit une nouvelle ligne � la suite de la position qui lui est fournie			
				//Updater le correctif de d�calage de la console par rapport � la m�moire
					if(base.refoule) base.consy++; else if(mem.nbligne>base.chary) {base.refoule = true; base.consy++;} 					
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore satur�e: on pousse vers le bas!
						if(can.posy==mem.nbligne-1) {               //Si le canal g�re la derni�re ligne de la console, c'est plus simple    //-1 : � cause de [0]
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-m�me!   //-1 : � cause de [0]
						} else {                             //S'il y a d'autres lignes � repousser vers le bas
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-m�me!   //-1 : � cause de [0]
							//R�-�crire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,can.posy-base.consy + 2);  //Mettre le curseur au d�but de la reconstruction
								for(int county = can.posy + 2 ; county < mem.nbligne ; county++) {    // + 2, parce que la m�moire a d�j� �t� updat�e
									for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
					} else {                         //La console est satur�e: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "rel�guant ce qui y �tait d�j� vers le haut")
							curspos(can.posy-base.consy,0); for(int countx = 0; countx < base.charx ; countx++) out(' '); 					
						//Tout r�-�crire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county < can.posy; county++){             //base.consy : facteur de d�calage de la console
										//V�RIFIER L'INITIATION DE COUNTY: �A SEMBLE UN BEL ADON QUE base.consy, UN "count" EN INTEGER SIMPLE,
										//S'EMBO�TE PARFAITEMENT AVEC L'INDEXATION QUI COMMENCE � 0!
								for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}
/*				//Updater les positions dans les autres canaux    //Parce que leur position dans la m�moire a boug� //la position dans la console est quant � elle g�r�e par base.consy
				for(int countcan = 0 ; countcan < canaux.nb ; countcan++) {        
					if(canaux[countcan].posy > can.posy) canaux[countcan].posy++;         //la m�moire refoule toujours vers le bas!
				}
*/                                                            //FAUDRA Y RETOURNER POUR D�BUGUER!				
				//Updater les positions dans le canal actuel
				if(can.txt[0]=='\n') {can.posx = -1;} else can.posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a chang� de ligne, mais �crire le prochain � la bonne place
	////////										//FLAG POUR POSITION IMPOSSIBLE; PEUT-�TRE QUE �A VA EMMENER UN BUG �VENTUELLEMENT?
				can.posy++;																   //en y 
			} else can.posx++;        //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caract�re       //� partir d'ici, les posx et posy sont la position du charact�re actuel (dans la m�moire)!		
		if(can.txt[0]!='\n') {
			curspos(can.posx,can.posy-base.consy) ; out(can.txt[0]);     //Inscrire dans la console
			mem.souvenir[can.posx][can.posy] = can.txt[0];   //Inscrire dans la m�moire
		}	
		//Effacer le caract�re du canal
		can.txt-0;                          
	}
}

	
//Et maintenant... Tester?
						//Avec les dimensions du jeu graphique simple!


					
HWND DimConsole = GetConsoleWindow();                        //Objet permettant de modifier les dimensions + la position de la console
						
					
							
int main(void) {

	//Changement de taille et de place de la console                     //Doit �tre d�fini � l'int�rieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(DimConsole, 500, 250, 200, 200, TRUE);                   //Les unit�s sont en pixels!
                                                                         //200x200 pixels = 13 lignes; 27 colonnes

	out('H'); out('e'); out('l'); out('l'); out('o'); out('?');	out('\n');  //Fonctionne!

	//cout<< "\nbase.charx:" << base.charx << "  base.chary:" << base.chary;

	//Cr�er les canaux utilis�s
	canal can1;
	string txt0 = "Ceci est du texte! Je dis du texte, maintenant! \n Wouhouuuu! Je suis le canal 1!";
	can1.txt = txt0;
	can1.txt.out();
	int currentt = timems();

	while(true){
		currentt = timems();
			if(can1.nxtt<currentt) {read(can1);}
		}	                                         //Pis �a crashe apr�s pas trop longtemps.
					//Probablement une erreur d'allocation de m�moire?
							//Probablement que je ne nettois pas assez bien ma m�moire?
							
								//Pour cela, Stack Overflow me propose de simplement ajouter � chaque destructeur et constructeur
								//un update de l'utilisation totale de m�moire.
								
								//Pour cela, faudrait d'abord que je comprenne exactement qu'est-ce qui a besoin de constructeur/destructeur dans mes vecteurs.
						//BLargh, j'ai tent� de nettoyer la m�moire, mais �a crash encore plus.
	
	}
			
			/*				
int main(void) {

	//Changement de taille et de place de la console                     //Doit �tre d�fini � l'int�rieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(DimConsole, 500, 250, 200, 200, TRUE);                   //Les unit�s sont en pixels!
                                                                         //200x200 pixels = 13 lignes; 27 colonnes

	//Cr�er les canaux utilis�s
	canal can1;
	canal can2;
	
	//Test: changer les d�lais manuellement
	can1.delay = 240;
	can2.delay = 430;
	
	//Les ajouter � l'objet canaux
	canaux += can1; canaux +=can2;
	
	//Ajouter du texte aux canaux
	string txt0 = "Ceci est du texte! Je dis du texte, maintenant! \n Wouhouuuu! Je suis le canal 1!";
	string txt1 = "Le canal 1 est sooooo boring. Ark. �p10000�\n Je suis le canal 2.";
	canaux[0].txt = txt0;
	//canaux[0].delay = 200;              //Error: using temporary as lvalue [-fpermissive]
	
	canaux[1].txt = txt1;
	//canaux[1].delay = 400;

	//Faire une boucle pour que les canaux s'expriment!
	while(true){
		int currentt = timems();
		for(int canpos = 1; canpos<canaux.nb; canpos++){
			if(canaux[canpos].nxtt>currentt) read(canaux[canpos]);
			}
		}
}					
*/
