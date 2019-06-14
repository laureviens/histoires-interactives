/*
			///||================================---2018/06/10---================================||\\\
\\\||================================---Fonction read() pour cr�er des outputs � partir des canaux de lecture---================================||///
*/


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
#include <chrono>     //Pour avoir un meilleur contr�le du temps (en millisecondes)
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)

# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/classe_vect_maison.cpp"  //Pour les vecteurs maisons

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) D�finir les objets de base sur lesquels va s'appuyer la suite
	
		//ix) Fonction : timems ; avoir le temps actuel en millisecondes (depuis l'epoch, soit 1er janvier 1970)
	int timems {
		return(std::chrono::duration_cast< std::chrono::milliseconds >(
	    std::chrono::system_clock::now().time_since_epoch()
	).count())
	}	
	
	//i) Classe : canal ; permet de sauvegarder la position de lecture du canal, le texte restant � lire, la vitesse, etc.
	class canal {
		//Membres
		public:
			int nxtt;           //D�clarer le moment o� la prochaine entr�e sera trait�e         
			int delay;          //D�clarer le d�lai de base entre chaque entr�e
			int posx, posy;		//D�clarer les coordonn�es de la derni�re entr�e dans la m�moire (la pr�c�dente)   
								//les positions de la consoles sont d�finies en d�calant ces derni�res
			vect<char> txt;     //D�clarer le texte qui reste � lire  				
			bool actif;			//D�clarer le compteur d'activit�
			double vit;         //D�clarer la vitesse actuelle de d�filement et de pauses (toujours par rapport � la base, 1)
		//Constructeur
		canal() {nextt = timems() ; delay = 400 ; posx = 1; posy = 1; actif = F; vit = 1}  //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
	};

	//ii) Classe : cons ; permet de sauvegarder les param�tres relatifs aux caract�ristiques de la fen�tre de sortie (console)
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
		fen base;

	//iii) Objet : mem ; permet de sauvegarder la "m�moire" de la console, c'est-�-dire tous le texte s'y �tant d�j� inscrit
		vect <char[base.charx]>	mem;  		//D�clarer l'objet				

	//iv) Fonction : cdsppos ; retourne la position des caract�res du code sp�cial
	vect<int> cdsppos(vect<char> str){
		vect<int> pos = 0;              //Initier l'objet � retourner
		int a = 1;                      //Commencer � la position [1], le [0] �tant occup� par '�' (et d�j� comptabilis�)
		while(str[a]!='�'&a<str.nb) pos += a;
		return(pos);		
	}

	//v) Fonction : cdspxtr ; extrait une valeur double d'une suite de caract�res encadr�s par '�' (pour extraire les codes sp�ciaux)
	double cdspxtr(vect<char> str, vect<int> pos){
		string nbonly;                  //Initier un string, dans lequel ins�rer seulement les chiffres
		int a = 2;                      //Commencer � la position [2], le [0] �tant occup� par '�' et le [1] par le type de valeur � extraire
		while(a<pos.nb) {nbonly += str[a];}
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
		SetConsoleCursorPosition(constxt,CursorPosition);            //WINDOWS ONLY
	}	
	


//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) �crire la fonction read()
read(canal can) {
	//Interpr�ter les "codes sp�ciaux" (�...�)
	if(can.txt[0]=='�'){		
		//D�terminer la position du code sp�cial
		vect<int> pos = cdsppos(can.txt);	
		//Lire le code sp�cial		
			if(can.txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause � la lecture
				double val = cdspxtr(can.txt,cdsppos);       //Extraire le temps que durera la pause
				can.nxtt += round(val * can.vit)                    //Ajouter le temps d'attente        //round() est n�cessaire pour arrondir correctement					
			} else if(can.txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = cdspxtr(can.txt,cdsppos);       //Extraire la nouvelle vitesse
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
				for(int countx = can.posx + 1; countx < base.charx ; countx++) mem [can.posy] [countx] = ' ';     //Effacer le reste de la ligne avec des espaces    
				mem + can.posy;                         //Cet op�rateur introduit une nouvelle ligne � la suite de la position qui lui est fournie			
				//Updater le correctif de d�calage de la console par rapport � la m�moire
					if(base.refoule) base.consy++; else if(mem.nb>base.chary) {base.refoule = true; base.consy++;} 					
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore satur�e: on pousse vers le bas!
						if(can.posy==mem.nb-1) {               //Si le canal g�re la derni�re ligne de la console, c'est plus simple    //-1 : � cause de [0]
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-m�me!   //-1 : � cause de [0]
						} else {                             //S'il y a d'autres lignes � repousser vers le bas
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-m�me!   //-1 : � cause de [0]
							//R�-�crire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,can.posy-base.consy + 2);  //Mettre le curseur au d�but de la reconstruction
								for(int county = can.posy + 2 ; county < mem.nb ; county++) {    // + 2, parce que la m�moire a d�j� �t� updat�e
									for(int countx = 0 ; countx < base.charx ; countx++) out(mem[county][countx]);
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
								for(int countx = 0 ; countx < base.charx ; countx++) out(mem[county][countx]);
							}				                 
					}
				//Updater les positions dans les autres canaux    //Parce que leur position dans la m�moire a boug� //la position dans la console est quant � elle g�r�e par base.consy
				for(int countcan = 0 ; countcan < canaux.nb ; countcan++) {        
					if(canaux[countcan].posy > can.posy) canaux[countcan].posy++;         //la m�moire refoule toujours vers le bas!
				}
				//Updater les positions dans le canal actuel
				if(can.txt[0]=='\n') {can.posx = -1;} else can.posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a chang� de ligne, mais �crire le prochain � la bonne place
	////////										//FLAG POUR POSITION IMPOSSIBLE; PEUT-�TRE QUE �A VA EMMENER UN BUG �VENTUELLEMENT?
				can.posy++;																   //en y 
			} else can.posx++;        //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caract�re       //� partir d'ici, les posx et posy sont la position du charact�re actuel (dans la m�moire)!
		if(can.txt[0]!='\n') {
			curspos(can.posx,can.posy-base.consy) ; ~can.txt[0];     //Inscrire dans la console
									//ATTENTION: ~ CORRESPOND � UNE FCT DE STYLE COUT(); OP�RATEUR QUI VA PEUT-�TRE CHANGER.
			mem[can.posy][can.posx] = can.txt[0];   //Inscrire dans la m�moire
		}	
		//Effacer le caract�re du canal
		can.txt-0;                          
	}
}

	
//Et maintenant... Tester?
						//Avec les dimensions du jeu graphique simple!
						
int main {



}						
