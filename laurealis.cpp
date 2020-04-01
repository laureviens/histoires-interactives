/*
			///||================================---2020/03/28---================================||\\\
\\\||================================--- Laur�alis? Du moins, un brouillon ---================================||///
*/

//-----------------------------------------------------------------|  Pr�paration technique  |--------------------------------------------------------------------------------\\
 
# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/cadre_fonctionnel_global.cpp"
int main(void) {
	univers u;
	
//-----------------------------------------------------------------|      Biblioth�que       |--------------------------------------------------------------------------------\\
 
 	u.nvrayon("didascalie");
 		u.nvlivre("LAURE");
 
	u.nvrayon("instanciation");					
		u.nvlivre("desuet");			
		u.nvlivre("tuesmoi");				
		u.nvlivre("voixquali");				
		u.nvlivre("tuasmoncorps");				
		u.nvlivre("incarnation");				

//-----------------------------------------------------------------|       Instanciation      |--------------------------------------------------------------------------------\\		

	//Cr�er un canal
	u.nvcanal("descriptif"); u.canaldelai(120); 
	u.nvcanal("autours"); u.canaldelai(100); 
	u.nvcanal("sens"); u.canaldelai(80); 	
	u.nvcanal("LAURE"); u.canaldelai(130); u.canalalinea(7); u.canalterminaison("�p400�\"");			//L'alin�a = le nombre de caract�res de "LAURE: " (mettre � chaque fois cette indication (didascalie), comme au th��tre)
	
	//D�buter un chapitre : les didascalies des diff�rents personnages
	u.nvchapt();
		u.ccond("true");
			
			u.nvauto(); u.acanal("msn"); u.acond("didascalie�LAURE==1"); u.adeb("�b didascalie�LAURE>~0��d100�"); u.afin("�p2000�");				
			u.atexte("LAURE: ");
			//u.apos()					INDIQUER UNE POSITION D'APPARITION : (0, poscan-> "LAURE" )
				
	//D�buter un chapitre : l'instanciation
	u.nvchapt();
	u.ccond("instanciation�desuet==0");
		
		//LAURE: "Tu es moi."
			u.nvauto(); u.acanal("LAURE"); u.acond("instanciation�tuesmoi==1");	
			u.adeb("�b instanciation�tuesmoi~>0��p1200�"); u.afin("�b instanciation�voixquali~>1�");
			u.atexte("�d11000�\n\n\n\n�d120��b didascalie�LAURE>~1�"
					"\"Tu incarnes�d200� moi.�d120��p1500� �g tu~Une;Un.e;Un� des �d160�multiples�d120� moi.\"");
					
		//Qualificatifs de la voix (de LAURE)
			u.nvauto(); u.acanal("descriptif");	u.acond("instanciation�voixquali==1"); u.adeb("�b instanciation�voixquali~>0��p1200�"); u.afin("�b instanciation�tuasmoncorps~>1�");
								//METTRE ICI LA FORMULE DES PROBABILIT�S DES ENCHA�NEMENTS!!!
			u.atexte("La voix est froide.");

			u.nvauto(); u.acanal("descriptif");	u.acond("instanciation�voixquali==1"); u.adeb("�b instanciation�voixquali~>0��p1200�"); u.afin("�b instanciation�tuasmoncorps~>1�");
								//METTRE ICI LA FORMULE DES PROBABILIT�S DES ENCHA�NEMENTS!!!
			u.atexte("Le ton est frais et asceptis�.");
			
			u.nvauto(); u.acanal("descriptif");	u.acond("instanciation�voixquali==1"); u.adeb("�b instanciation�voixquali~>0��p1200�"); u.afin("�b instanciation�tuasmoncorps~>1�");
								//METTRE ICI LA FORMULE DES PROBABILIT�S DES ENCHA�NEMENTS!!!
			u.atexte("Le ton est sans contamination �motionelle.");
			
			u.nvauto(); u.acanal("descriptif");	u.acond("instanciation�voixquali==1"); u.adeb("�b instanciation�voixquali~>0��p1200�"); u.afin("�b instanciation�tuasmoncorps~>1�");
								//METTRE ICI LA FORMULE DES PROBABILIT�S DES ENCHA�NEMENTS!!!
			u.atexte("Une voix mate et chrom�e.");						

			u.nvauto(); u.acanal("descriptif");	u.acond("instanciation�voixquali==1"); u.adeb("�b instanciation�voixquali~>0��p1200�"); u.afin("�b instanciation�tuasmoncorps~>1�");
								//METTRE ICI LA FORMULE DES PROBABILIT�S DES ENCHA�NEMENTS!!!
			u.atexte("Les m�tadonn�es te font �"	//1
					"percevoir�"						//2
					"sentir�"							//3
					" un d�bit �"					//4
					"neutre.�"							//5
					"impersonnel.");					//6
			u.aordre("1-2-4-5;1-2-4-6;1-3-4-5;1-3-4-6");

		//LAURE: "Tu as mon corps."
			u.nvauto(); u.acanal("LAURE"); u.acond("instanciation�tuasmoncorps==1"); u.adeb("�b instanciation�tuasmoncorps~>0��p1200�"); u.afin("�b instanciation�incarnation~>1�");
			u.atexte("�d11000�\n\n�d120��b didascalie�LAURE>~1�"
					"\"Tu poss�de�d200� mon corps.�d120��p1800� Dans les �d170�moindres d�tails.�p800�\"");

		//Incarnation: ses sensations
			u.nvauto(); u.acanal("sens"); u.acond("instanciation�incarnation==1"); u.adeb("�b instanciation�incarnation~>0��p1200�"); u.afin("�b instanciation�?????~>1�");
			u.atexte("\n�"							//1
					"\n�"					//2
					"Des �"							//3
					"octets �"					//4
					"bytes �"					//5
					"roulent �"							//6
					"s'unissent �"						//7
					"sur �"						//8
					"sous �"					//9
					"tes extr�mit�s; �"					//10
					"tes appendices; �"					//11
					"ach�vent de les �"				//12
					"cr�er.�"					//13
					"mat�rialiser.");			//14
			//CR�ER UNE FORMULE POUR R�ALISER TOUTES LES POSSIBILIT�S! C'EST PAS VRAI QUE JE ME CLAQUE �A � CHAQUE FOIS!
								//METTRE ICI LA FORMULE DES PROBABILIT�S DES ENCHA�NEMENTS!!!

						
										
//-----------------------------------------------------------------|     Menu principal      |--------------------------------------------------------------------------------\\

//Dessin de la sc�ne "enti�re" � mettre comme arri�re-plan du menu principal:

/*

"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"												|��������������������|��|                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"              �       {)                       |                    |  |                                          "
"     ________/|\/k__/\|)_______                | � � � � � � � � �  |��|                                          "
"    /         ��     �        /|               |                    |  |                                          " 
"   /                         /_|_______        | � � � � � � � � �  |��|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | � � � � � � � � �  |��|                                          "
"|                     _____|/       /  |_/\____|__________          |  |                                          "
"|  |���|    |���|    /             /  /  ||              /|� � � �  |��|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |� � � �  |��|                                          "	//115 colonnes
"|__________________|__��__��__��__|/__________________/___|_________|__|_______                                   "	//43 lignes
"��������\�����������\\�����������\�����������\�����������\�����������\��������\\                                  "
"���������\�����������\\�����������\�����������\�����������\�����������\��������\\                                 "
"���������������������||���������������������������������������������������������||_____________________________   "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "

*/

		//La sc�ne id�ale (en utiliser les dimensions pour d�finir la taille de la fen�tre par d�faut)

/*

"                                                                       " 
"                                                                       "		//Espace vertical requis pour le titre  
"                                                                       "		//
"                                                                       "		//
"                                                                       "		//
"                                                                       "		//
"                                                                       "		//
"                                                                       "		//
"                                                                       "		
"                                                                       "		
"                                                                       "
"                                                                       "
"                                                                       "                                                                                                              "
"                                                                       "
"                                       |��������������������|��|       "
"                                       | � � � � � � � � �  |��|       "
"                                       |                    |  |       "		//71 colonnes
"                                       | � � � � � � � � �  |��|       "		//37 lignes
"                                   x   |                    |  |       "
"                                       | � � � � � � � � �  |��|       "			x = milieu
"      �       {)                       |                    |  |       "
"_____/|\/k__/\|)_______                | � � � � � � � � �  |��|       "
"      ��     �        /|               |                    |  |       " 
"                     /_|_______        | � � � � � � � � �  |��|       "			//Version alternative du titre (plus longue)
"                    / /       /|       |                    |  |       "
"___________________/ /       / |       | � � � � � � � � �  |��|       "		"          /\                  |                  "
"              _____|/       /  |_/\____|__________          |  |       "		"          \                   |   _   /\         "
"    |���|    /             /  /  ||              /|� � � �  |��|       "		"           \   | |   |/       |  /_\  \          "
"    |   |   /_____________/  /                  / |         |  |       "		"          \/   \_|\  |        |  \_  \/          "		//9 lignes de haut
"    |___|  |              | /               ~  /  |� � � �  |��|       "		"                                                 "
"___________|__��__��__��__|/__________________/___|_________|__|_____  "		"               |            |                    "
"\�����������\\�����������\�����������\�����������\�����������\��������\"		"              ���       *  ���   /\              "
"�\�����������\\�����������\�����������\�����������\�����������\��������"		"               |   /\   |   |    \               "
"�������������||��������������������������������������������������������"		"               |   \/   |   |   \/               "
"/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"		"                                                 "
"\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\"
"/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"

*/
	//D�finir la taille par d�faut de la fen�tre de jeu
	u.setfenetredefaut(71,37);
	
		//La sc�ne "minimale", avec titre et menu (la plus petite version que je juge possible - tout en restant belle et compl�te)
/*
		
"           /\                 |   _              "		//7 lignes de haut, le titre abr�g�
"           \   | |   |/       |  /_\  /\         "
"          \/   \_|\  |        |  \_  \/          "
"                                                 "
"               |        *   |                    "
"              ���  /\   |  ���   /\              "
"               |   \/   |   |   \/               "
"                                                 "							//49 colonnes
"                                    |������������"							//31 lignes
"               |�����������������|  | � � � � � �"
"               |     D�buter     |  |            "
"               |_________________|  | � � � � � �"
"                                    |            "
"                                    | � � � � � �"
"   �       {)  |�����������������|  |            "
"__/|\/k__/\|)__|     Options     |  | � � � � � �"					//Le bouton central est compl�tement centr�.
"   ��     �    |_________________|  |            " 
"                  /_|_______        | � � � � � �"
"                 / /        |       |            "
"_______________|�����������������|  | � � � � � �"
"           ____|     Quitter     |_____________  "
" |���|    /    |_________________|            /|�"
" |   |   /_____________/  /                  / | "
" |___|  |              | /               ~  /  |�"
"________|__��__��__��__|/__________________/___|_"
"���������\\�����������\�����������\�����������\��"
"����������\\�����������\�����������\�����������\�"
"����������||�������������������������������������"
"\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\"
"/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"

*/
	//D�finir la taille minimale possible de la fen�tre � l'aide de ce que je juge �tre la plus petite fen�tre acceptable possible
	u.setfenetremin(49,31);

	//Cr�er le menu principal de d�part, celui qui commence le jeu
	u.nvmenu("principal commencement");
	
		//D�finir l'arri�re-plan du menu
			//Attention! Ici, les caract�res '\' doivent �tre doubl�s ("\\") pour que le code se lise bien. �a d�cale le dessin, mais il s'affichera correctement � l'�cran!
		u.menubg("                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                               |��������������������|��|                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"              �       {)                       |                    |  |                                          "
"     ________/|\\/k__/\\|)_______                | � � � � � � � � �  |��|                                          "
"    /         ��     �        /|               |                    |  |                                          "
"   /                         /_|_______        | � � � � � � � � �  |��|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | � � � � � � � � �  |��|                                          "
"|                     _____|/       /  |_/\\____|__________          |  |                                          "
"|  |���|    |���|    /             /  /  ||              /|� � � �  |��|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |� � � �  |��|                                          "
"|__________________|__��__��__��__|/__________________/___|_________|__|_______                                   "
"��������\\�����������\\\\�����������\\�����������\\�����������\\�����������\\��������\\\\                                  "
"���������\\�����������\\\\�����������\\�����������\\�����������\\�����������\\��������\\\\                                 "
"���������������������||���������������������������������������������������������||_____________________________   "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  ",43);		//Indiquer le nombre de lignes du dessin comme second argument

		//D�finir les rebords du dessin qui ne doivent pas �tre remplac�s par des espaces (si la fen�tre est plus grande que le dessin, des espaces viendront remplir le c�t� oppos�)
		u.menubglock("left"); u.menubglock("bottom");
		
		//D�finir le point d'int�r�t du dessin
			//C'est l'outil dont je me suis dot� pour pouvoir minimalement positionner le dessin correctement, peu importe la taille de la fen�tre.
			//Il faut d�finir une cellule du dessin (l'origine (0,0) est le coin en haut � gauche) qui va servir de point d'int�r�t.
			//Il faut ensuite d�finir une position pr�cise � laquelle on souhaite voir ce point d'int�r�t. Cette position sera exprim�e en fractions de la largeur et de la hauteur de la fen�tre.
			//Ici, je souhaite que les personnages soient situ�s dans le coin en bas � gauche de l'image:
		u.menubgpointinteret(18,21,0.2,0.7);
		
		//D�finir le titre � afficher � l'�cran
		u.menutitredessin("          /\\                  |                  "
"          \\                   |   _   /\\         "
"           \\   | |   |/       |  /_\\  \\          "
"          \\/   \\_|\\  |        |  \\_  \\/          "		//9 lignes de haut
"                                                 "
"               |            |                    "
"              ���       *  ���   /\\              "
"               |   /\\   |   |    \\               "
"               |   \\/   |   |   \\/               ",9);
		
		//D�finir sa hauteur par rapport � la fen�tre totale (0 = dans le haut compl�tement)
		u.menutitrehauteur(0.0285714286);		// = 1/35; mais �a ne marche pas quand on l'�crit en tant que fraction...
		
		//D�finir le premier bouton de mon menu principal, ainsi que son effet
		u.menunvbouton("Lancer le jeu","�m��bintro�je~>1��j�");
			//Ce bouton aura pour effet de r�initialiser les objets de sauvegarde, de modifier un rayon de la biblioth�que, puis de lancer la boucle "jouer" (�j�, 'j' pour "jouer"), qui lance le programme. 

		//D�finir le deuxi�me bouton, ainsi que son effet
		u.menunvbouton("Options","�zoptions�");	
			//Ce bouton aura pour effet d'appeler le menu d'options (�z�, 'z' pour... rien en fait. 'm' �tait d�j� pris dans les codes sp�ciaux de canaux, alors j'ai pris z. Que je r�-utilise ici).			
	
		//D�finir le troisi�me bouton, ainsi que son effet
		u.menunvbouton("Quitter","�a�");	
			//Ce bouton aura pour effet de terminer le programme (�a�, 'a' pour "abort()").


	//�a, c'�tait le menu principal de d�part. Maitenant, j'ai besoin d'un autre menu; qui lui ne va pas COMMENCER le jeu, mais bien le REPRENDRE
	
	//Cr�er ce deuxi�me menu principal
	u.nvmenu("principal retour");
	
		//Mettre encore les m�mes param�tres:
		//Arri�re-plan:
		u.menubg("                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                               |��������������������|��|                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"              �       {)                       |                    |  |                                          "
"     ________/|\\/k__/\\|)_______                | � � � � � � � � �  |��|                                          "
"    /         ��     �        /|               |                    |  |                                          "
"   /                         /_|_______        | � � � � � � � � �  |��|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | � � � � � � � � �  |��|                                          "
"|                     _____|/       /  |_/\\____|__________          |  |                                          "
"|  |���|    |���|    /             /  /  ||              /|� � � �  |��|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |� � � �  |��|                                          "
"|__________________|__��__��__��__|/__________________/___|_________|__|_______                                   "
"��������\\�����������\\\\�����������\\�����������\\�����������\\�����������\\��������\\\\                                  "
"���������\\�����������\\\\�����������\\�����������\\�����������\\�����������\\��������\\\\                                 "
"���������������������||���������������������������������������������������������||_____________________________   "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  ",43);		//Indiquer le nombre de lignes du dessin comme second argument

		//Rebords fixes:
		u.menubglock("left"); u.menubglock("bottom");
		
		//Point d'int�r�t du dessin:
		u.menubgpointinteret(18,21,0.2,0.7);
		
		//Titre � afficher � l'�cran:
		u.menutitredessin("          /\\                  |                  "
"          \\                   |   _   /\\         "
"           \\   | |   |/       |  /_\\  \\          "
"          \\/   \\_|\\  |        |  \\_  \\/          "		//9 lignes de haut
"                                                 "
"               |            |                    "
"              ���       *  ���   /\\              "
"               |   /\\   |   |    \\               "
"               |   \\/   |   |   \\/               ",9);
		
		//Hauteur par rapport � la fen�tre totale (0 = dans le haut compl�tement):
		u.menutitrehauteur(0.0285714286);		// = 1/35; mais �a ne marche pas quand on l'�crit en tant que fraction...
		
		//Premier bouton de mon menu principal, ainsi que son effet
		u.menunvbouton("Retour au jeu","�u�");
			//Ce bouton, contrairement � l'autre, ne fera que "un-pause" le jeu: "�u�" ('u' pour "unpause", repart tous les canaux/msn/etc. qui ne sont pas gel�s)
	
		//Deuxi�me bouton, ainsi que son effet
		u.menunvbouton("Options","�zoptions�");	
		
		//Troisi�me bouton, ainsi que son effet
		u.menunvbouton("Quitter","�a�");	

//-----------------------------------------------------------------|     Menus d'options     |--------------------------------------------------------------------------------\\

	//Cr�er le menu d'options
	u.nvmenu("options");		

		//Mettre l'arri�re-plan
		u.menubg("                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                               |��������������������|��|                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"              �       {)                       |                    |  |                                          "
"     ________/|\\/k__/\\|)_______                | � � � � � � � � �  |��|                                          "
"    /         ��     �        /|               |                    |  |                                          "
"   /                         /_|_______        | � � � � � � � � �  |��|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | � � � � � � � � �  |��|                                          "
"|                     _____|/       /  |_/\\____|__________          |  |                                          "
"|  |���|    |���|    /             /  /  ||              /|� � � �  |��|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |� � � �  |��|                                          "
"|__________________|__��__��__��__|/__________________/___|_________|__|_______                                   "
"��������\\�����������\\\\�����������\\�����������\\�����������\\�����������\\��������\\\\                                  "
"���������\\�����������\\\\�����������\\�����������\\�����������\\�����������\\��������\\\\                                 "
"���������������������||���������������������������������������������������������||_____________________________   "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  ",43);
		u.menubglock("left"); u.menubglock("bottom");
		u.menubgpointinteret(18,21,0.2,0.7);
		
		//D�finir le titre � afficher � l'�cran
		u.menutitredessin(
" /��������������������������\\ "
"/          OPTIONS           \\"
"|                            |"
"|         ATTENTION!         |"
"|  Si tu modifies la taille  |"
"|  de la fen�tre, il faudra  |"
"|    que tu commences une    |"
"\\      nouvelle partie!      /"
" \\__________________________/ ",9);

			//Comme le premier bouton a un texte plut�t long, je vais agrandir les boutons (par d�faut: largeur de 19 caract�res, dont 15 pouvant h�berger du texte; hauteur de 3 caract�res, dont une ligne dispo pour du texte)
			u.menulargeurbouton(31);
			u.menuhauteurbouton(4);

		//Premier bouton, ainsi que son effet
		u.menunvbouton("Modifier la taille \nde la fen�tre de jeu","�zmodiffen�");
		
		//Deuxi�me bouton, ainsi que son effet
		u.menunvbouton("Retour","�y�");
			//Ce bouton aura comme effet de faire r�-appara�tre le menu pr�c�dent: "�y�", 'y' pour "pr�c�dent"
			
		//D�finir l'effet de la touche "escape"
		u.menuescape("�y�");
		
	//Cr�er le menu de modification de la taille de la fen�tre de jeu
	u.nvmenu("modiffen");

		//Mettre l'arri�re-plan
		u.menubg("                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                               |��������������������|��|                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"              �       {)                       |                    |  |                                          "
"     ________/|\\/k__/\\|)_______                | � � � � � � � � �  |��|                                          "
"    /         ��     �        /|               |                    |  |                                          "
"   /                         /_|_______        | � � � � � � � � �  |��|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | � � � � � � � � �  |��|                                          "
"|                     _____|/       /  |_/\\____|__________          |  |                                          "
"|  |���|    |���|    /             /  /  ||              /|� � � �  |��|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |� � � �  |��|                                          "
"|__________________|__��__��__��__|/__________________/___|_________|__|_______                                   "
"��������\\�����������\\\\�����������\\�����������\\�����������\\�����������\\��������\\\\                                  "
"���������\\�����������\\\\�����������\\�����������\\�����������\\�����������\\��������\\\\                                 "
"���������������������||���������������������������������������������������������||_____________________________   "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  ",43);
		u.menubglock("left"); u.menubglock("bottom");
		u.menubgpointinteret(18,21,0.2,0.7);		

			//S'assurer que le texte rentre	
			u.menulargeurbouton(21);
	
		//Premier bouton, ainsi que son effet
		u.menunvbouton("Plus de hauteur","�fh+��x�");
			//Ce bouton aura comme effet d'ajouter une ligne � la hauteur de la fen�tre: "�f�", 'f' pour fen�tre; 'h' = hauteur, '+' = augmenter; puis de rester au m�me menu: "�x�" pour "remettre le m�me menu"
			
		//Deuxi�me bouton, ainsi que son effet
		u.menunvbouton("Moins de hauteur","�fh-��x�");
		
		//Troisi�me bouton, ainsi que son effet
		u.menunvbouton("Plus de largeur","�fl+��x�");
			//'l' = largeur.
		
		//Quatri�me bouton, ainsi que son effet
		u.menunvbouton("Moins de largeur","�fl-��x�");				
			
		//Cinqui�me bouton, ainsi que son effet
		u.menunvbouton("Retour","�m��y�");
			//�m� ('m' pour "m�moire") r�-initialise les sauvegarde du texte du jeu; ce qui est n�cessaire, puisque celles-ci sont conserv�es dans un format qui prend appui sur la taille de la fen�tre.
		
		//D�finir l'effet de la touche "escape"
		u.menuescape("�y�");
		
		//Acc�l�rer les effets de s�lection
		u.menuenterdelay(200);
		u.menuselectdelay(300);
					
//-----------------------------------------------------------------|      Menu de pause      |--------------------------------------------------------------------------------\\

	//Cr�er le menu de pause
	u.nvmenu("pause");	

		//Sp�cifier que c'est ce menu qu'on veut voir affich� quand le bouton [ESC] sera enfonc�
		u.menuingameescape("pause");
		
		//Par d�faut, si on ne sp�cifie pas d'arri�re-plan, le contenu des m�moires sera utilis�
			
		//D�finir le titre � afficher � l'�cran
		u.menutitredessin("/---------\\"
"|  PAUSE  |"
"\\---------/",3);
		
		//D�finir sa hauteur par rapport � la fen�tre totale (0 = dans le haut compl�tement)
		u.menutitrehauteur(0.05);
		
		//D�finir le premier bouton du menu, ainsi que son effet
		u.menunvbouton("Retour au jeu","�u�");			
			//Ce bouton aura pour effet de remettre le jeu en action (�u�, 'u' pour "unpause").

		//D�finir le deuxi�me bouton, ainsi que son effet
		u.menunvbouton("Revenir au \nmenu principal","�zprincipal retour�");
			//Ce bouton aura pour effet d'appeler le menu principal (�z�, 'z' pour... rien en fait. 'm' �tait d�j� pris dans les codes sp�ciaux de canaux, alors j'ai pris z. Que je r�-utilise ici).			

			//Comme le deuxi�me bouton a deux lignes, je vais agrandir tous les boutons � une hauteur de 4 (� la place de 3):
			u.menuhauteurbouton(4);

		//D�finir le troisi�me bouton, ainsi que son effet
		u.menunvbouton("Quitter le jeu","�a�");	
			//Ce bouton aura pour effet de terminer le programme (�a�, 'a' pour "abort()").		

		//D�finir l'action de la touche [ESCAPE]
			//Par d�faut, cette touche a pour cons�quence la fermeture du programme.
		u.menuescape("�u�");		//R�gler [ESCAPE] pour revenir au jeu

//-----------------------------------------------------------------|       Menu de fin       |--------------------------------------------------------------------------------\\

	//Cr�er le menu de pause
	u.nvmenu("end");				//Par d�faut, si on ne sp�cifie pas d'arri�re-plan, le contenu des m�moires sera utilis�

		//D�finir le titre � afficher � l'�cran
		u.menutitredessin(" /�����������������\\ "
"/  POUR L'INSTANT,  \\"
"|   C'EST TOUT CE   |"
"| QUE J'AI � OFFRIR |"
"|                   |"
"|   MAIS REVENEZ    |"
"\\    PLUS TARD!     /"
" \\_________________/ ",8);
		
		//D�finir sa hauteur par rapport � la fen�tre totale (0 = dans le haut compl�tement)
		u.menutitrehauteur(0.05);
		
		//D�finir le premier bouton, ainsi que son effet
		u.menunvbouton("Revenir au \nmenu principal","�c��zprincipal commencement�");	
			//Ce bouton aura pour effet d'appeler le menu principal (�z�, 'z' pour... rien en fait. 'm' �tait d�j� pris dans les codes sp�ciaux de canaux, alors j'ai pris z. Que je r�-utilise ici).			

			//Comme le premier bouton a deux lignes, je vais agrandir tous les boutons � une hauteur de 4 (� la place de 3):
			u.menuhauteurbouton(4);

		//D�finir le deuxi�me bouton, ainsi que son effet
		u.menunvbouton("Quitter","�a�");	
			//Ce bouton aura pour effet de terminer le programme (�a�, 'a' pour "abort()").		


//-----------------------------------------------------------------|        Ex�cuter         |--------------------------------------------------------------------------------\\		
		
	//Commencer proprement
	u.debuter("principal commencement");

}		
