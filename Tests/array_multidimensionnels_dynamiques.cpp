		//Cr�er des arrays multidimensionnels dynamiques
		
			class table{
			//Membres
			public: 
				int nbcol;
				int nbligne;
				int** cell;
			//Constructeurs
			table() {nbcol = 1; nbligne = 1; cell = new int* [nbcol]; cell[nbcol] = new int [nbligne];}
			table(int x,int y) {
				nbcol = x; nbligne = y;                 //Ce qui suit semble �tre la seule mani�re de cr�er des arrays dynamiques
				cell = new int* [nbcol];   //Cr�er un premier array de taille variable
				for(int col=0; col<nbcol ; col++) {cell[col] = new int [nbligne];}    //Cr�er les lignes pour chaque colonne
			}
			//Fonction d'acc�s : retourner certaines positions
			int acces (int posx, int posy) { //Cr�er une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(cell[posx][posy]);
			}
			//Fonction de modification : ajouter une ligne � la suite de la position sp�cifi�e (Op�rateur +) 
			void operator + (int pos) {
				int emptypos = pos + 1;   //Calculer la position qui sera vide
				int** nwcell = new int* [nbcol]; for(int col=0; col<nbcol ; col++) {cell[col] = new int [nbligne+1];}  //D�clarer le nouvel array (transitoire)
				int oldpos = 0;  //D�clarer un compteur pour les vieilles positions				
				for(int nwpos=0; nwpos < nbligne; nwpos++) {  //Remplir, en laissant une position vide
					if(nwpos==emptypos) {continue;} 
					for(int xpos = 0; xpos<nbcol ; xpos++) {nwcell[xpos][nwpos] = cell[xpos][oldpos];}
					oldpos++;
				}
				nbligne++;   //Noter le nombre de valeur qu'on enl�ve
				for(int col=0; col<nbcol ; col++) delete[] cell[col] ; delete[] cell;  //�liminer le vieil array    //�limination longue!
				cell = nwcell;  //Assigner le pointeur � l'array actuel
			}
		};
		
		
