		//Créer des arrays multidimensionnels dynamiques
		
			class table{
			//Membres
			public: 
				int nbcol;
				int nbligne;
				int** cell;
			//Constructeurs
			table() {nbcol = 1; nbligne = 1; cell = new int* [nbcol]; cell[nbcol] = new int [nbligne];}
			table(int x,int y) {
				nbcol = x; nbligne = y;                 //Ce qui suit semble être la seule manière de créer des arrays dynamiques
				cell = new int* [nbcol];   //Créer un premier array de taille variable
				for(int col=0; col<nbcol ; col++) {cell[col] = new int [nbligne];}    //Créer les lignes pour chaque colonne
			}
			//Fonction d'accès : retourner certaines positions
			int acces (int posx, int posy) { //Créer une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(cell[posx][posy]);
			}
			//Fonction de modification : ajouter une ligne à la suite de la position spécifiée (Opérateur +) 
			void operator + (int pos) {
				int emptypos = pos + 1;   //Calculer la position qui sera vide
				int** nwcell = new int* [nbcol]; for(int col=0; col<nbcol ; col++) {cell[col] = new int [nbligne+1];}  //Déclarer le nouvel array (transitoire)
				int oldpos = 0;  //Déclarer un compteur pour les vieilles positions				
				for(int nwpos=0; nwpos < nbligne; nwpos++) {  //Remplir, en laissant une position vide
					if(nwpos==emptypos) {continue;} 
					for(int xpos = 0; xpos<nbcol ; xpos++) {nwcell[xpos][nwpos] = cell[xpos][oldpos];}
					oldpos++;
				}
				nbligne++;   //Noter le nombre de valeur qu'on enlève
				for(int col=0; col<nbcol ; col++) delete[] cell[col] ; delete[] cell;  //Éliminer le vieil array    //Élimination longue!
				cell = nwcell;  //Assigner le pointeur à l'array actuel
			}
		};
		
		
