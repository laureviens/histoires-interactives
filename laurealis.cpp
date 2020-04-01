/*
			///||================================---2020/03/28---================================||\\\
\\\||================================--- Lauréalis? Du moins, un brouillon ---================================||///
*/

//-----------------------------------------------------------------|  Préparation technique  |--------------------------------------------------------------------------------\\
 
# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/cadre_fonctionnel_global.cpp"
int main(void) {
	univers u;
	
//-----------------------------------------------------------------|      Bibliothèque       |--------------------------------------------------------------------------------\\
 
 	u.nvrayon("didascalie");
 		u.nvlivre("LAURE");
 
	u.nvrayon("instanciation");					
		u.nvlivre("desuet");			
		u.nvlivre("tuesmoi");				
		u.nvlivre("voixquali");				
		u.nvlivre("tuasmoncorps");				
		u.nvlivre("incarnation");				

//-----------------------------------------------------------------|       Instanciation      |--------------------------------------------------------------------------------\\		

	//Créer un canal
	u.nvcanal("descriptif"); u.canaldelai(120); 
	u.nvcanal("autours"); u.canaldelai(100); 
	u.nvcanal("sens"); u.canaldelai(80); 	
	u.nvcanal("LAURE"); u.canaldelai(130); u.canalalinea(7); u.canalterminaison("§p400§\"");			//L'alinéa = le nombre de caractères de "LAURE: " (mettre à chaque fois cette indication (didascalie), comme au théâtre)
	
	//Débuter un chapitre : les didascalies des différents personnages
	u.nvchapt();
		u.ccond("true");
			
			u.nvauto(); u.acanal("msn"); u.acond("didascalie¶LAURE==1"); u.adeb("§b didascalie¶LAURE>~0§§d100§"); u.afin("§p2000§");				
			u.atexte("LAURE: ");
			//u.apos()					INDIQUER UNE POSITION D'APPARITION : (0, poscan-> "LAURE" )
				
	//Débuter un chapitre : l'instanciation
	u.nvchapt();
	u.ccond("instanciation¶desuet==0");
		
		//LAURE: "Tu es moi."
			u.nvauto(); u.acanal("LAURE"); u.acond("instanciation¶tuesmoi==1");	
			u.adeb("§b instanciation¶tuesmoi~>0§§p1200§"); u.afin("§b instanciation¶voixquali~>1§");
			u.atexte("§d11000§\n\n\n\n§d120§§b didascalie¶LAURE>~1§"
					"\"Tu incarnes§d200§ moi.§d120§§p1500§ §g tu~Une;Un.e;Un§ des §d160§multiples§d120§ moi.\"");
					
		//Qualificatifs de la voix (de LAURE)
			u.nvauto(); u.acanal("descriptif");	u.acond("instanciation¶voixquali==1"); u.adeb("§b instanciation¶voixquali~>0§§p1200§"); u.afin("§b instanciation¶tuasmoncorps~>1§");
								//METTRE ICI LA FORMULE DES PROBABILITÉS DES ENCHAÎNEMENTS!!!
			u.atexte("La voix est froide.");

			u.nvauto(); u.acanal("descriptif");	u.acond("instanciation¶voixquali==1"); u.adeb("§b instanciation¶voixquali~>0§§p1200§"); u.afin("§b instanciation¶tuasmoncorps~>1§");
								//METTRE ICI LA FORMULE DES PROBABILITÉS DES ENCHAÎNEMENTS!!!
			u.atexte("Le ton est frais et asceptisé.");
			
			u.nvauto(); u.acanal("descriptif");	u.acond("instanciation¶voixquali==1"); u.adeb("§b instanciation¶voixquali~>0§§p1200§"); u.afin("§b instanciation¶tuasmoncorps~>1§");
								//METTRE ICI LA FORMULE DES PROBABILITÉS DES ENCHAÎNEMENTS!!!
			u.atexte("Le ton est sans contamination émotionelle.");
			
			u.nvauto(); u.acanal("descriptif");	u.acond("instanciation¶voixquali==1"); u.adeb("§b instanciation¶voixquali~>0§§p1200§"); u.afin("§b instanciation¶tuasmoncorps~>1§");
								//METTRE ICI LA FORMULE DES PROBABILITÉS DES ENCHAÎNEMENTS!!!
			u.atexte("Une voix mate et chromée.");						

			u.nvauto(); u.acanal("descriptif");	u.acond("instanciation¶voixquali==1"); u.adeb("§b instanciation¶voixquali~>0§§p1200§"); u.afin("§b instanciation¶tuasmoncorps~>1§");
								//METTRE ICI LA FORMULE DES PROBABILITÉS DES ENCHAÎNEMENTS!!!
			u.atexte("Les métadonnées te font µ"	//1
					"percevoirµ"						//2
					"sentirµ"							//3
					" un débit µ"					//4
					"neutre.µ"							//5
					"impersonnel.");					//6
			u.aordre("1-2-4-5;1-2-4-6;1-3-4-5;1-3-4-6");

		//LAURE: "Tu as mon corps."
			u.nvauto(); u.acanal("LAURE"); u.acond("instanciation¶tuasmoncorps==1"); u.adeb("§b instanciation¶tuasmoncorps~>0§§p1200§"); u.afin("§b instanciation¶incarnation~>1§");
			u.atexte("§d11000§\n\n§d120§§b didascalie¶LAURE>~1§"
					"\"Tu possède§d200§ mon corps.§d120§§p1800§ Dans les §d170§moindres détails.§p800§\"");

		//Incarnation: ses sensations
			u.nvauto(); u.acanal("sens"); u.acond("instanciation¶incarnation==1"); u.adeb("§b instanciation¶incarnation~>0§§p1200§"); u.afin("§b instanciation¶?????~>1§");
			u.atexte("\nµ"							//1
					"\nµ"					//2
					"Des µ"							//3
					"octets µ"					//4
					"bytes µ"					//5
					"roulent µ"							//6
					"s'unissent µ"						//7
					"sur µ"						//8
					"sous µ"					//9
					"tes extrémités; µ"					//10
					"tes appendices; µ"					//11
					"achèvent de les µ"				//12
					"créer.µ"					//13
					"matérialiser.");			//14
			//CRÉER UNE FORMULE POUR RÉALISER TOUTES LES POSSIBILITÉS! C'EST PAS VRAI QUE JE ME CLAQUE ÇA À CHAQUE FOIS!
								//METTRE ICI LA FORMULE DES PROBABILITÉS DES ENCHAÎNEMENTS!!!

						
										
//-----------------------------------------------------------------|     Menu principal      |--------------------------------------------------------------------------------\\

//Dessin de la scène "entière" à mettre comme arrière-plan du menu principal:

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
"												|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|¯¯|                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"                                               |                    |  |                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"                                               |                    |  |                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"              ¢       {)                       |                    |  |                                          "
"     ________/|\/k__/\|)_______                | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"    /         ¯¯     ¯        /|               |                    |  |                                          " 
"   /                         /_|_______        | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"|                     _____|/       /  |_/\____|__________          |  |                                          "
"|  |¯¯¯|    |¯¯¯|    /             /  /  ||              /|¤ ¤ ¤ ¤  |¤¤|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |¤ ¤ ¤ ¤  |¤¤|                                          "	//115 colonnes
"|__________________|__¯¯__¯¯__¯¯__|/__________________/___|_________|__|_______                                   "	//43 lignes
"««««««««\«««««««««««\\«««««««««««\«««««««««««\«««««««««««\«««««««««««\««««««««\\                                  "
"«««««««««\«««««««««««\\«««««««««««\«««««««««««\«««««««««««\«««««««««««\««««««««\\                                 "
"¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||_____________________________   "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "

*/

		//La scène idéale (en utiliser les dimensions pour définir la taille de la fenêtre par défaut)

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
"                                       |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|¯¯|       "
"                                       | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|       "
"                                       |                    |  |       "		//71 colonnes
"                                       | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|       "		//37 lignes
"                                   x   |                    |  |       "
"                                       | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|       "			x = milieu
"      ¢       {)                       |                    |  |       "
"_____/|\/k__/\|)_______                | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|       "
"      ¯¯     ¯        /|               |                    |  |       " 
"                     /_|_______        | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|       "			//Version alternative du titre (plus longue)
"                    / /       /|       |                    |  |       "
"___________________/ /       / |       | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|       "		"          /\                  |                  "
"              _____|/       /  |_/\____|__________          |  |       "		"          \                   |   _   /\         "
"    |¯¯¯|    /             /  /  ||              /|¤ ¤ ¤ ¤  |¤¤|       "		"           \   | |   |/       |  /_\  \          "
"    |   |   /_____________/  /                  / |         |  |       "		"          \/   \_|\  |        |  \_  \/          "		//9 lignes de haut
"    |___|  |              | /               ~  /  |¤ ¤ ¤ ¤  |¤¤|       "		"                                                 "
"___________|__¯¯__¯¯__¯¯__|/__________________/___|_________|__|_____  "		"               |            |                    "
"\«««««««««««\\«««««««««««\«««««««««««\«««««««««««\«««««««««««\««««««««\"		"              ¯¯¯       *  ¯¯¯   /\              "
"«\«««««««««««\\«««««««««««\«««««««««««\«««««««««««\«««««««««««\««««««««"		"               |   /\   |   |    \               "
"¯¯¯¯¯¯¯¯¯¯¯¯¯||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯"		"               |   \/   |   |   \/               "
"/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"		"                                                 "
"\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\"
"/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"

*/
	//Définir la taille par défaut de la fenêtre de jeu
	u.setfenetredefaut(71,37);
	
		//La scène "minimale", avec titre et menu (la plus petite version que je juge possible - tout en restant belle et complète)
/*
		
"           /\                 |   _              "		//7 lignes de haut, le titre abrégé
"           \   | |   |/       |  /_\  /\         "
"          \/   \_|\  |        |  \_  \/          "
"                                                 "
"               |        *   |                    "
"              ¯¯¯  /\   |  ¯¯¯   /\              "
"               |   \/   |   |   \/               "
"                                                 "							//49 colonnes
"                                    |¯¯¯¯¯¯¯¯¯¯¯¯"							//31 lignes
"               |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|  | ¤ ¤ ¤ ¤ ¤ ¤"
"               |     Débuter     |  |            "
"               |_________________|  | ¤ ¤ ¤ ¤ ¤ ¤"
"                                    |            "
"                                    | ¤ ¤ ¤ ¤ ¤ ¤"
"   ¢       {)  |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|  |            "
"__/|\/k__/\|)__|     Options     |  | ¤ ¤ ¤ ¤ ¤ ¤"					//Le bouton central est complètement centré.
"   ¯¯     ¯    |_________________|  |            " 
"                  /_|_______        | ¤ ¤ ¤ ¤ ¤ ¤"
"                 / /        |       |            "
"_______________|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|  | ¤ ¤ ¤ ¤ ¤ ¤"
"           ____|     Quitter     |_____________  "
" |¯¯¯|    /    |_________________|            /|¤"
" |   |   /_____________/  /                  / | "
" |___|  |              | /               ~  /  |¤"
"________|__¯¯__¯¯__¯¯__|/__________________/___|_"
"«««««««««\\«««««««««««\«««««««««««\«««««««««««\««"
"««««««««««\\«««««««««««\«««««««««««\«««««««««««\«"
"¯¯¯¯¯¯¯¯¯¯||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯"
"\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\"
"/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"

*/
	//Définir la taille minimale possible de la fenêtre à l'aide de ce que je juge être la plus petite fenêtre acceptable possible
	u.setfenetremin(49,31);

	//Créer le menu principal de départ, celui qui commence le jeu
	u.nvmenu("principal commencement");
	
		//Définir l'arrière-plan du menu
			//Attention! Ici, les caractères '\' doivent être doublés ("\\") pour que le code se lise bien. Ça décale le dessin, mais il s'affichera correctement à l'écran!
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
"                                               |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|¯¯|                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"                                               |                    |  |                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"                                               |                    |  |                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"              ¢       {)                       |                    |  |                                          "
"     ________/|\\/k__/\\|)_______                | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"    /         ¯¯     ¯        /|               |                    |  |                                          "
"   /                         /_|_______        | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"|                     _____|/       /  |_/\\____|__________          |  |                                          "
"|  |¯¯¯|    |¯¯¯|    /             /  /  ||              /|¤ ¤ ¤ ¤  |¤¤|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |¤ ¤ ¤ ¤  |¤¤|                                          "
"|__________________|__¯¯__¯¯__¯¯__|/__________________/___|_________|__|_______                                   "
"««««««««\\«««««««««««\\\\«««««««««««\\«««««««««««\\«««««««««««\\«««««««««««\\««««««««\\\\                                  "
"«««««««««\\«««««««««««\\\\«««««««««««\\«««««««««««\\«««««««««««\\«««««««««««\\««««««««\\\\                                 "
"¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||_____________________________   "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  ",43);		//Indiquer le nombre de lignes du dessin comme second argument

		//Définir les rebords du dessin qui ne doivent pas être remplacés par des espaces (si la fenêtre est plus grande que le dessin, des espaces viendront remplir le côté opposé)
		u.menubglock("left"); u.menubglock("bottom");
		
		//Définir le point d'intérêt du dessin
			//C'est l'outil dont je me suis doté pour pouvoir minimalement positionner le dessin correctement, peu importe la taille de la fenêtre.
			//Il faut définir une cellule du dessin (l'origine (0,0) est le coin en haut à gauche) qui va servir de point d'intérêt.
			//Il faut ensuite définir une position précise à laquelle on souhaite voir ce point d'intérêt. Cette position sera exprimée en fractions de la largeur et de la hauteur de la fenêtre.
			//Ici, je souhaite que les personnages soient situés dans le coin en bas à gauche de l'image:
		u.menubgpointinteret(18,21,0.2,0.7);
		
		//Définir le titre à afficher à l'écran
		u.menutitredessin("          /\\                  |                  "
"          \\                   |   _   /\\         "
"           \\   | |   |/       |  /_\\  \\          "
"          \\/   \\_|\\  |        |  \\_  \\/          "		//9 lignes de haut
"                                                 "
"               |            |                    "
"              ¯¯¯       *  ¯¯¯   /\\              "
"               |   /\\   |   |    \\               "
"               |   \\/   |   |   \\/               ",9);
		
		//Définir sa hauteur par rapport à la fenêtre totale (0 = dans le haut complètement)
		u.menutitrehauteur(0.0285714286);		// = 1/35; mais ça ne marche pas quand on l'écrit en tant que fraction...
		
		//Définir le premier bouton de mon menu principal, ainsi que son effet
		u.menunvbouton("Lancer le jeu","§m§§bintro¶je~>1§§j§");
			//Ce bouton aura pour effet de réinitialiser les objets de sauvegarde, de modifier un rayon de la bibliothèque, puis de lancer la boucle "jouer" (§j§, 'j' pour "jouer"), qui lance le programme. 

		//Définir le deuxième bouton, ainsi que son effet
		u.menunvbouton("Options","§zoptions§");	
			//Ce bouton aura pour effet d'appeler le menu d'options (§z§, 'z' pour... rien en fait. 'm' était déjà pris dans les codes spéciaux de canaux, alors j'ai pris z. Que je ré-utilise ici).			
	
		//Définir le troisième bouton, ainsi que son effet
		u.menunvbouton("Quitter","§a§");	
			//Ce bouton aura pour effet de terminer le programme (§a§, 'a' pour "abort()").


	//Ça, c'était le menu principal de départ. Maitenant, j'ai besoin d'un autre menu; qui lui ne va pas COMMENCER le jeu, mais bien le REPRENDRE
	
	//Créer ce deuxième menu principal
	u.nvmenu("principal retour");
	
		//Mettre encore les mêmes paramètres:
		//Arrière-plan:
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
"                                               |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|¯¯|                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"                                               |                    |  |                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"                                               |                    |  |                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"              ¢       {)                       |                    |  |                                          "
"     ________/|\\/k__/\\|)_______                | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"    /         ¯¯     ¯        /|               |                    |  |                                          "
"   /                         /_|_______        | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"|                     _____|/       /  |_/\\____|__________          |  |                                          "
"|  |¯¯¯|    |¯¯¯|    /             /  /  ||              /|¤ ¤ ¤ ¤  |¤¤|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |¤ ¤ ¤ ¤  |¤¤|                                          "
"|__________________|__¯¯__¯¯__¯¯__|/__________________/___|_________|__|_______                                   "
"««««««««\\«««««««««««\\\\«««««««««««\\«««««««««««\\«««««««««««\\«««««««««««\\««««««««\\\\                                  "
"«««««««««\\«««««««««««\\\\«««««««««««\\«««««««««««\\«««««««««««\\«««««««««««\\««««««««\\\\                                 "
"¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||_____________________________   "
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
		
		//Point d'intérêt du dessin:
		u.menubgpointinteret(18,21,0.2,0.7);
		
		//Titre à afficher à l'écran:
		u.menutitredessin("          /\\                  |                  "
"          \\                   |   _   /\\         "
"           \\   | |   |/       |  /_\\  \\          "
"          \\/   \\_|\\  |        |  \\_  \\/          "		//9 lignes de haut
"                                                 "
"               |            |                    "
"              ¯¯¯       *  ¯¯¯   /\\              "
"               |   /\\   |   |    \\               "
"               |   \\/   |   |   \\/               ",9);
		
		//Hauteur par rapport à la fenêtre totale (0 = dans le haut complètement):
		u.menutitrehauteur(0.0285714286);		// = 1/35; mais ça ne marche pas quand on l'écrit en tant que fraction...
		
		//Premier bouton de mon menu principal, ainsi que son effet
		u.menunvbouton("Retour au jeu","§u§");
			//Ce bouton, contrairement à l'autre, ne fera que "un-pause" le jeu: "§u§" ('u' pour "unpause", repart tous les canaux/msn/etc. qui ne sont pas gelés)
	
		//Deuxième bouton, ainsi que son effet
		u.menunvbouton("Options","§zoptions§");	
		
		//Troisième bouton, ainsi que son effet
		u.menunvbouton("Quitter","§a§");	

//-----------------------------------------------------------------|     Menus d'options     |--------------------------------------------------------------------------------\\

	//Créer le menu d'options
	u.nvmenu("options");		

		//Mettre l'arrière-plan
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
"                                               |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|¯¯|                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"                                               |                    |  |                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"                                               |                    |  |                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"              ¢       {)                       |                    |  |                                          "
"     ________/|\\/k__/\\|)_______                | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"    /         ¯¯     ¯        /|               |                    |  |                                          "
"   /                         /_|_______        | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"|                     _____|/       /  |_/\\____|__________          |  |                                          "
"|  |¯¯¯|    |¯¯¯|    /             /  /  ||              /|¤ ¤ ¤ ¤  |¤¤|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |¤ ¤ ¤ ¤  |¤¤|                                          "
"|__________________|__¯¯__¯¯__¯¯__|/__________________/___|_________|__|_______                                   "
"««««««««\\«««««««««««\\\\«««««««««««\\«««««««««««\\«««««««««««\\«««««««««««\\««««««««\\\\                                  "
"«««««««««\\«««««««««««\\\\«««««««««««\\«««««««««««\\«««««««««««\\«««««««««««\\««««««««\\\\                                 "
"¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||_____________________________   "
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
		
		//Définir le titre à afficher à l'écran
		u.menutitredessin(
" /¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\\ "
"/          OPTIONS           \\"
"|                            |"
"|         ATTENTION!         |"
"|  Si tu modifies la taille  |"
"|  de la fenêtre, il faudra  |"
"|    que tu commences une    |"
"\\      nouvelle partie!      /"
" \\__________________________/ ",9);

			//Comme le premier bouton a un texte plutôt long, je vais agrandir les boutons (par défaut: largeur de 19 caractères, dont 15 pouvant héberger du texte; hauteur de 3 caractères, dont une ligne dispo pour du texte)
			u.menulargeurbouton(31);
			u.menuhauteurbouton(4);

		//Premier bouton, ainsi que son effet
		u.menunvbouton("Modifier la taille \nde la fenêtre de jeu","§zmodiffen§");
		
		//Deuxième bouton, ainsi que son effet
		u.menunvbouton("Retour","§y§");
			//Ce bouton aura comme effet de faire ré-apparaître le menu précédent: "§y§", 'y' pour "précédent"
			
		//Définir l'effet de la touche "escape"
		u.menuescape("§y§");
		
	//Créer le menu de modification de la taille de la fenêtre de jeu
	u.nvmenu("modiffen");

		//Mettre l'arrière-plan
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
"                                               |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|¯¯|                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"                                               |                    |  |                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"                                               |                    |  |                                          "
"                                               | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"              ¢       {)                       |                    |  |                                          "
"     ________/|\\/k__/\\|)_______                | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"    /         ¯¯     ¯        /|               |                    |  |                                          "
"   /                         /_|_______        | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤ ¤  |¤¤|                                          "
"|                     _____|/       /  |_/\\____|__________          |  |                                          "
"|  |¯¯¯|    |¯¯¯|    /             /  /  ||              /|¤ ¤ ¤ ¤  |¤¤|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |¤ ¤ ¤ ¤  |¤¤|                                          "
"|__________________|__¯¯__¯¯__¯¯__|/__________________/___|_________|__|_______                                   "
"««««««««\\«««««««««««\\\\«««««««««««\\«««««««««««\\«««««««««««\\«««««««««««\\««««««««\\\\                                  "
"«««««««««\\«««««««««««\\\\«««««««««««\\«««««««««««\\«««««««««««\\«««««««««««\\««««««««\\\\                                 "
"¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||_____________________________   "
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
		u.menunvbouton("Plus de hauteur","§fh+§§x§");
			//Ce bouton aura comme effet d'ajouter une ligne à la hauteur de la fenêtre: "§f§", 'f' pour fenêtre; 'h' = hauteur, '+' = augmenter; puis de rester au même menu: "§x§" pour "remettre le même menu"
			
		//Deuxième bouton, ainsi que son effet
		u.menunvbouton("Moins de hauteur","§fh-§§x§");
		
		//Troisième bouton, ainsi que son effet
		u.menunvbouton("Plus de largeur","§fl+§§x§");
			//'l' = largeur.
		
		//Quatrième bouton, ainsi que son effet
		u.menunvbouton("Moins de largeur","§fl-§§x§");				
			
		//Cinquième bouton, ainsi que son effet
		u.menunvbouton("Retour","§m§§y§");
			//§m§ ('m' pour "mémoire") ré-initialise les sauvegarde du texte du jeu; ce qui est nécessaire, puisque celles-ci sont conservées dans un format qui prend appui sur la taille de la fenêtre.
		
		//Définir l'effet de la touche "escape"
		u.menuescape("§y§");
		
		//Accélérer les effets de sélection
		u.menuenterdelay(200);
		u.menuselectdelay(300);
					
//-----------------------------------------------------------------|      Menu de pause      |--------------------------------------------------------------------------------\\

	//Créer le menu de pause
	u.nvmenu("pause");	

		//Spécifier que c'est ce menu qu'on veut voir affiché quand le bouton [ESC] sera enfoncé
		u.menuingameescape("pause");
		
		//Par défaut, si on ne spécifie pas d'arrière-plan, le contenu des mémoires sera utilisé
			
		//Définir le titre à afficher à l'écran
		u.menutitredessin("/---------\\"
"|  PAUSE  |"
"\\---------/",3);
		
		//Définir sa hauteur par rapport à la fenêtre totale (0 = dans le haut complètement)
		u.menutitrehauteur(0.05);
		
		//Définir le premier bouton du menu, ainsi que son effet
		u.menunvbouton("Retour au jeu","§u§");			
			//Ce bouton aura pour effet de remettre le jeu en action (§u§, 'u' pour "unpause").

		//Définir le deuxième bouton, ainsi que son effet
		u.menunvbouton("Revenir au \nmenu principal","§zprincipal retour§");
			//Ce bouton aura pour effet d'appeler le menu principal (§z§, 'z' pour... rien en fait. 'm' était déjà pris dans les codes spéciaux de canaux, alors j'ai pris z. Que je ré-utilise ici).			

			//Comme le deuxième bouton a deux lignes, je vais agrandir tous les boutons à une hauteur de 4 (à la place de 3):
			u.menuhauteurbouton(4);

		//Définir le troisième bouton, ainsi que son effet
		u.menunvbouton("Quitter le jeu","§a§");	
			//Ce bouton aura pour effet de terminer le programme (§a§, 'a' pour "abort()").		

		//Définir l'action de la touche [ESCAPE]
			//Par défaut, cette touche a pour conséquence la fermeture du programme.
		u.menuescape("§u§");		//Régler [ESCAPE] pour revenir au jeu

//-----------------------------------------------------------------|       Menu de fin       |--------------------------------------------------------------------------------\\

	//Créer le menu de pause
	u.nvmenu("end");				//Par défaut, si on ne spécifie pas d'arrière-plan, le contenu des mémoires sera utilisé

		//Définir le titre à afficher à l'écran
		u.menutitredessin(" /¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\\ "
"/  POUR L'INSTANT,  \\"
"|   C'EST TOUT CE   |"
"| QUE J'AI À OFFRIR |"
"|                   |"
"|   MAIS REVENEZ    |"
"\\    PLUS TARD!     /"
" \\_________________/ ",8);
		
		//Définir sa hauteur par rapport à la fenêtre totale (0 = dans le haut complètement)
		u.menutitrehauteur(0.05);
		
		//Définir le premier bouton, ainsi que son effet
		u.menunvbouton("Revenir au \nmenu principal","§c§§zprincipal commencement§");	
			//Ce bouton aura pour effet d'appeler le menu principal (§z§, 'z' pour... rien en fait. 'm' était déjà pris dans les codes spéciaux de canaux, alors j'ai pris z. Que je ré-utilise ici).			

			//Comme le premier bouton a deux lignes, je vais agrandir tous les boutons à une hauteur de 4 (à la place de 3):
			u.menuhauteurbouton(4);

		//Définir le deuxième bouton, ainsi que son effet
		u.menunvbouton("Quitter","§a§");	
			//Ce bouton aura pour effet de terminer le programme (§a§, 'a' pour "abort()").		


//-----------------------------------------------------------------|        Exécuter         |--------------------------------------------------------------------------------\\		
		
	//Commencer proprement
	u.debuter("principal commencement");

}		
