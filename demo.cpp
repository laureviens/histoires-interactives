/*
			///||================================---2020/01/18---================================||\\\
\\\||================================---Tutoriel / Démo du potentiel interactif / narratif---================================||///
*/

//-----------------------------------------------------------------|  Explication de la base |--------------------------------------------------------------------------------\\

		//J'explique ici le coeur de ma façon d'écrire des "fictions interactives" (ou "aventures narratives" ou "text adventure", etc.)
			//Chaque histoire (interactive) sera composée de petites unités, qui comprennent à la fois le texte à lire et les conditions dans lequel ce texte sera lu.
			//J'appelle ici ces unités des "motifs".
			//Le principe à la base de cette idée de création "interactive" est que ces motifs pourront s'enchaîner, se croiser, se superposer à leur guise, dans un ordre pas forcément linéaire, dans l'ordre décidé par les actions de la joueuse.

		//Afin d'organiser efficacement cette collection de motifs, je les regroupe en "chapitres".
		
		//J'utilise deux types de "motifs" : les motifs "automatiques" et les motifs "manuels".
			//Les motifs automatiques n'attendent que les conditions propices pour déverser leur texte dans la fenêtre de jeu.
			//Les motifs manuels, quant à eux, sont exécuté quand les conditions propices sont réunies ET seulement si la bonne commande les appelle.
				//C'est par les motifs manuels que la joueuse pourra influencer le cours de l'histoire, en appelant certaines actions plutôt que d'autres, ou plutôt qu'une inaction.

		//Pour conserver l'information relative à la progression du jeu, et à quelle condition est remplie au moment présent, j'utilise la bibliothèque (introduite plus haut).

		//Pour interagir avec le système de jeu (supprimer un dialogue déjà intégré mais devenu caduque, noter la progression, changer la vitesse, etc.), j'utilise seulement le texte à lire.
			//À l'intérieur de ce "texte à lire", je vais donc cacher des "codes spéciaux".
				//Un "code spécial", c'est simplement quelque chose qui n'apparaîtra pas à l'écran, mais dont la "lecture" enclenchera une action quelconque (une interaction avec le système de jeu).
			//Pour marquer un "code spécial", j'utilise le symbole '§' (qui est un caractère que j'ai jugé que je n'utiliserai jamais dans le texte que je veux voir affiché à l'écran).
				//Un code spécial sera donc un bout de texte entouré de '§' (à la manière de parenthèses ou d'accolades)
				//La deuxième lettre du code (la première étant '§') indiquera l'action à effectuer et la façon dont on doit lire le reste du code spécial. 
					//Par exemple, "§p1000§" signifie "prendre une pause de 1000 millisecondes dans la lecture". En gros: attendre une seconde.
					//Un exemple bête : "Je suis due pour une pause.§p2000§ Merci!" sera lu comme : "Je suis due pour une pause." - pause de 2 secondes - " Merci!"
					
			
//-----------------------------------------------------------------|  Préparation technique  |--------------------------------------------------------------------------------\\
 
# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/cadre_fonctionnel_global.cpp"
		//On a besoin de loader les codes et définitions qui sont dans ce fichier. C'est en quelque chose la ligne la plus importante!
int main(void) {
		//On doit spécifier que la suite sera "[et maintenant,] votre programme principal" (c'est une joke de VHS/dvd). En gros, tout ce qui est à l'intérieur de la fonction "main" sera automatiquement exécuté en tant que programme. 
		//Tout ce qui vient avant ce "main" pourra servir à setter des valeurs ou initialiser des objets, mais jamais à interagir avec la console. Et tout ce qui vient après... ne sert à rien?
		
	//Créer l'objet où tout est initié
			//J'ai créé un classe d'objet (nommée "univers") qui contient tout ce que j'ai besoin pour fonctionner. Ici, je crée un objet ("u") de cette classe ("univers"), qui sera initialisé avec les paramètres du "constructeur par défaut" (défini à l'intérieur de la classe "univers"). Bref. 
	univers u;
	
//-----------------------------------------------------------------|      Bibliothèque       |--------------------------------------------------------------------------------\\
		//La bibliothèque est le lieux où la plupart des valeurs (toujours numériques (des nombres entiers, en fait), BTW) utiles à la progression (genre à savoir où on est rendue) sont stockées.
		//Elle est organisé ainsi: chaque nombre est stocké en tant que "livre", et les multiples livres sont regroupés à l'intérieur de "rayons".
		//Cette hiérarchie à deux niveau (niveau le + petit: livre, niveau le + grand: rayon) a été choisie à la fois pour imposer un peu d'ordre dans la création des compteurs, 
		//   et à la fois pour optimiser le temps de recherche (c'est moins long de rechercher un rayon à travers 8 choix, puis un livre à travers 20 choix, qu'un seul livre à travers une pile de 400 choix).

	u.nvrayon("intro");					//Ici, je crée le premier rayon, que j'intitule "intro" (il sert à coordonner tout ce qui se passe avant que le contrôle soit donné à la joueuse - la mise en contexte, en quelque sorte).
		u.nvlivre("desuet");			//Ici, je crée le premier livre du rayon actuel 
		u.nvlivre("je");				//...deuxième livre...
		u.nvlivre("sara");
		u.nvlivre("tuto");
	u.nvrayon("cloture");				//...deuxième rayon...
		u.nvlivre("desuet");			//...premier livre du rayon actuel, donc premier livre du deuxième rayon...
		u.nvlivre("je");
		u.nvlivre("sara");
		u.nvlivre("estucorrecte");	
		u.nvlivre("abandon");
		u.nvlivre("choix");
		u.nvlivre("continuer");
		u.nvlivre("franchir");
		u.nvlivre("grimper");
		u.nvlivre("courage");	
		
			//Tous ces noms vont avoir plus de sens par la suite...
			//BTW, la valeur numérique attachée à chaque "livre" est de 0. Fait que tous les "livres" commencent avec une valeur de 0.
			
//-----------------------------------------------------------------|       Introduction      |--------------------------------------------------------------------------------\\		

	//Créer un canal
			//Le texte s'affiche principalement via des "canaux". Il s'agit simplement d'objets qui stockent le texte envoyé par les motifs, et l'écrivent dans la console progressivement.
			//Je crée ici deux canaux: un pour la narration ("je"), et un pour les paroles de ta compagne d'aventures, Sara. Sara pourra ainsi parler en même temps que la narration explique quelque chose!
			//Pour chaque canaux, je précise un délai (en millisecondes). Il s'agit du temps à attendre entre chaque lettre (plus c'est petit, plus le texte défile vite!).
	u.nvcanal("je"); u.canaldelai(80); 
			//Je donne un alinéa au canal de Sara (par défaut, il n'y en a pas). Ainsi, tout ce qu'elle dit va être en retrait de 6 espaces du bord gauche de la fenêtre. Ça va permettre de mieux différencier les voix.
			//Je lui fournis aussi une terminaison (y'en a pas par défaut). Il s'agit simplement de c'qu'elle va dire si on lui coupe la parole subitement (si on doit effacer tout ce qu'il lui restait à dire, parce que ça n'a plus rapport).
			//Ici, la terminaison spécifiée (BTW, on pourra la changer par la suite - plus tard) permet de simplement fermer ses guillemets de dialogue, après une pt'ite pause, pour faire plus propre.
	u.nvcanal("sara"); u.canaldelai(130); u.canalalinea(6); u.canalterminaison("§p400§\"");		
		
		
	//Débuter un chapitre pour l'introduction (où t'as pas de choix à faire, tu fais juste lire la mise en contexte)
			//Comme les rayons de la bibliothèque, les chapitres sont un moyen de mieux organiser les fictions, puis d'optimiser la recherche.
	u.nvchapt();
		u.ccond("intro¶desuet==0");        //Hou, on rentre dans le croquant! Une ligne qui n'est pas du tout évidente! 
				//Cette ligne sert à définir les conditions sous lesquelles ce chapitre sera valide (les moments dans lesquels on pourra en puiser du texte).
				//Pour faire ça, on utilise les livres de la bibliothèque!
				//On peut reconnaître qu'on recherche le rayon "intro", et qu'à l'intérieur de ce rayon, on veut le livre "desuet". 
				//COMME POUR TOUTE RÉFÉRENCE À LA BIBLIO, le rayon est séparé du livre par le symbole '¶' (BTW, garde en tête de ne pas mettre d'espaces de chaque côté. C'est pas "intro ¶ desuet", c'est "intro¶desuet").
				//Ici, la condition veut simplement que ce livre ("desuet", situé dans le rayon "intro") soit égal à 0 (qui est la valeur par défaut de tous les livres).
				//Si l'on remplit cette condition, on pourra pêcher du texte des motifs présents dans ce premier chapitre.
				
				
			//Introduire notre premier motif
					//Houuu!! Là ça devient sérieux!
					//Il s'agit d'un motif automatique (pour bien le différencier, on voit que toutes les fonctions qui le modifie commencent par un 'a'), qui lancera le texte qu'il contient dans la console dès que sa condition d'activation sera remplie.
			u.nvauto(); u.acanal("je");	    
					//On crée le nouveau "motif" (c'est là où on conserve le texte qu'on va ajouter progressivement aux canaux). Et puis on l'assigne à un canal: ici, ce sera "je", qui correspond à la narration.    	
			u.acond("intro¶je==1");	
					//Comme pour le chapitre, chaque motif doit avoir une condition d'activation. Ici, le "je", situé à l'intérieur de "intro", doit être égal à 1 (et il le sera au début du programme). 
			u.atexte("\n\nT'as froid aux joues.§p1400§"
			"\n§d0§                     §d80§Pis aux cuisses.");	
					//Beaucoup de nouvelles choses ici!!!
					//First, "\n". Il s'agit du "code spécial" standard (standard à la plupart des langages de programmation) pour dire qu'on change de ligne.
						//Fait qu'à chaque fois qu'on inclut "\n" dans notre texte, on va sauter une ligne à l'écran rendue là.
						//Ici, "\n\n" fait qu'on va sauter deux lignes avant de commencer à déclamer le texte.
					//Deuxièmement: Un code spécial! 
						//Un code spécial est : n'importe quoi qui est entouré de '§', et qui effectue une action précise sur le système de jeu.
						//La deuxième lettre du code (après le premier '§') va servir à dire de quel type le code spécial est (en gros: qu'est-ce qu'il fait).
						//Ici, on en a deux types: "§p§"  et  "§d§".
							//"§p§" ('p' pour pause) sert à prendre une pause dans la lecture, une pause dont la longueur est transmise en millisecondes.
								//En lisant "§p1400§", le canal "je" va arrêter d'afficher son texte pendant 1,4 secondes, pui recommencer.
							//"§d§" ('d' pour délai) sert à modifier le délai (le temps à attendre) entre chaque lettre.
								//En définissant le canal "je", on lui avait donné un délai de 80 millisecondes : le canal va sortir une nouvelle lettre à toutes les 0.08 secondes.
								//Ici, j'utilise simplement un p'tit truc pour tasser le texte à gauche:
									//a) changer de ligne; b) mettre un délai de 0 seconde (lire le texte à la vitesse de l'éclair); c) remettre le délai normal quand on a assez inscrit d'espace (quand le texte est assez tassé).
			u.adeb("§bintro¶je~>0§§p1200§");
					//Pour faciliter la lecture des codes importants, je sépare le début et la fin du texte du reste.
					//Mais ça va faire partie du texte du motif, au final. Le voir comme     { deb + texte + fin } = le texte du motif au complet
								
					//Nouveau code spécial qui s'introduit!
						//"§b§" ('b' pour bibliothèque) sert à modifier les valeurs stockées dans la bibliothèque (donc, agir sur quel motif présente les conditions nécessaires pour s'activer)
						//Après le 'b', on va avoir "le nom du rayon de la bibliothèque où on veut modifier un livre" ("intro"), '¶', "le nom du livre qu'on veut modifier" ("sara"), "le symbole de modification" ("~>"), puis "la valeur qu'on veut donner au livre" ("1").
						//Ici, ce code spécial va permettre de désactiver le motif actuel (sa condition était "intro¶je==0") (et oui, un même motif peut être activé plus d'une fois!).
			u.afin("§bintro¶sara~>1§");
					//Ici, à la fin du texte, on met en place la valeur qui va permettre au prochain motif de s'activer (le prochain motif, ça va être Sara qui parle)!
					

			//Deuxième motif: Message de directives du début (temporaire?)
			u.nvauto(); u.acanal("msn");
					//Nouveau concept: un msn
						//En gros, j'voulais avoir la possibilité d'inscrire un message temporaire, qui s'inscrit puis qui s'efface (avec un visuel cool).
						//Fait que j'ai créé une nouvelle classe de "canaux", que j'ai nommé "msn".
						//Puisque les "msn" sont temporaires, il ne faut pas les créer au début : on en crée un nouveau à chaque fois qu'un motif ayant comme canal "msn" s'active.
			u.acond("intro¶je==1");
			u.afin("§p2600§§f0§");
					//Nouveau code spécial!
						//"§f§" ('f' pour FREEZE) sert à mettre en pause tous les autres canaux (et messageries), pour n'avoir que celui qui l'a inscrit qui est actif.
							//"§f1§" (qui est présent au milieu du mot "quitter", dans le texte du motif) sert à "freezer", tandis que "§f0§" sert à "dé-freezer".
			u.atexte("§p2200§Pou§f1§r quitter le programme,§p400§ appuie sur §p210§[ESC§p110§].§p1200§"
			"\nPour modifier la vitesse de défilement,§p600§ appuie sur les touches §p90§[HAUT§p100§] et §p140§[BAS§p90§] (possiblement plusieurs fois).");
				
			//La harangue de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro¶sara==1");	
			u.adeb("§bintro¶sara~>0§§s§");
					//Nouveau code spécial!
						//§s§ ('s' pour skip) sert à placer le canal dans le bas du texte qui s'affiche (skipper la file!) : ça permet de le mettre à l'avant-scène, drette sous les projecteurs. 
			u.afin("§bintro¶je~>2§\"");
					//Nouveau "code spécial standard"
						//    \"     , ça là (j'peux pas l'entourer de guillemets en gardant ça clair), ça fait qu'un guillemet (") s'affiche à l'écran.
						//C'est parce que sinon, un guillement tout seul signifie "début/fin de la zone de texte". Fait que pour rester dans la zone de texte pis afficher un guillement à l'écran, on utilise \" .			
			u.atexte("§p1800§\n\"Come on,§p1100§"
			"\n§d0§          §d130§on est presquµ"			//Segment #1
			"e rendues!µ"									//Segment #2
			"'arrivées!");									//Segment #3
					//Nouveau mécanisme!
						//Pour introduire de la variété dans les phrases qui s'affichent, j'ai décidé que différentes combinaisons de phrases semblables pourraient être sélectionnées.
						//Ici, je sépare mon texte en plusieurs segments. Le séparateur utilisé est 'µ' (comme '§', c'est un caractère que j'suis sûre de ne pas utiliser sinon).			
			u.aordre("1-2;1-3");			//Par défaut, chaque combinaison a une probabilité égale de se produire; mais ça peut être changé si on veut autrement.
					//Ici, je décide quelles seront les "combinaisons gagnantes" : celles qui pourront être sélectionnées pour être ajouté au canal "je".
					//Par exemple, ici, les segments #1 et #2 sont à peu près synonymes, de même que les #3 et #4. Donc j'mets juste toutes les combinaisons différentes.

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==2");	
			u.adeb("§bintro¶je~>0§§s§");
			u.afin("§bintro¶sara~>2§");
			u.atexte("§p400§\n\n         T'accélères le pas,§p600§ moins pour la rejoindre§p100§ que pour réchauffer tes jambes.§p1200§§d110§ Le vent,§p500§ gode.§p700§ Le vent transperce.§p1600§"
			"\n§d90§Tu lèves les yeux§p100§ juste à la limite de ton capuchon§p300§ pis Sara est quand même loin en avant.§p1400§§d80§ Tu te presses un peu plus.§p2800§"
			"\n\nTraverses une rue,§p400§ t'es au coin de la cathédrale§p300§ pis le vent charge de plus belle depuis ta droite.§p2400§ Caliss.§p3000§§d90§"	//Segment #1
			"\nSara est déjà rendue plus bas,§p500§ 'a longe la grosse chapelle.§p2300§µ"	//Segment #2
			"\nTon amie est maintenant pas mal plus bas,§p500§ aux pieds de l'imposante église.§p2000§µ"	//Segment #3			
			"\n§d0§                       §d80§Tu descends au jogging§p120§, §p400§"
			"\n§d0§                                                §d80§rejoindre au plus vite l'énorme pare-vent de pierre.§p1800§µ"			//Segment #4
			"\n\nTu t'actives pluss, question d'la rejoindre rapidement à l'abri du vent.§p1100§µ"												//Segment #5
			"\nTa jupe virevolte sur tes genoux,§p200§ expose tes cuisses aux rafales;§p2300§ Pas l'meilleur choix de vêtements.§p4300§"
			"\n\n     La cathédrale coupe le vent§p150§ pour vrai.§3100§ "
			"\n\n\nSara t'as un peu attendue et te sourit avec son trop d'excitation.§p2200§");													//Segment #6
			u.aordre("1-2-4-6;1-2-5-6;1-3-4-6;1-3-5-6");

			//La réponse de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro¶sara==2");	
			u.adeb("§bintro¶sara~>0§§s§§p130§§d110§\n\"");
			u.afin("\"§bintro¶je~>3§");
			u.atexte("J'te l'dis,§p260§ t'as vraiment trop hâte d'être rendue su'l'toît du Granada!µ"		//Segment #1
			"L'accès aux toîts estµ "			//Segment #2
			"§d50§"								//Segment #3
			"justeµ"							//Segment #4
			"-justeµ"							//Segment #5
			"-justeµ"							//Segment #6
			" à côté.§d100§µ"					//Segment #7
			"T'auras jamais vu une vue d'même, juré!µ"			//Segment #8
			"Tu tough encore genre trois mètres pis on devient les roines du centro!");		//Segment #9
			u.aordre("1;2-3-4-5-7;2-3-4-5-6-7;2-3-4-5-7-8;2-3-4-5-7-9;2-4-7-9");

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==3");	
			u.adeb("§bintro¶je~>0§§s§");
			u.afin("§bintro¶sara~>3§");
			u.atexte("§p3100§Tu peux pas empêcher tes commissures engourdies de remonter un peu.§p2600§"
			"\n\n§d90§Encore quelques pas ensemble et vous êtes à l'arrière d'la maison de Dieu§p140§ pis l'vent reprend.§p560§§100§ Vraiment une belle soirée pour être sur l'top d'une colline.§2600§"
			"\n\n§d90§Sara te traîne encore plus derrière l'église,§p220§ dans une allée séparée de la rue par un p'tit muret.§p1800§ À ta gauche,§p160§ tu peux voir le frimas sur les toits plats des buildings adjacents,§p240§ pis les lumières de la ville,§p130§ de l'autre côté d'la rivière.§p2000§ Vous êtes pas mal haut,§p180§ finalement.§p3000§"
			"\nTu continues et un long bâtiment de briques s'érige entre le bord de la falaise et vous,§p110§ coupe le paysage.§p900§ Ça donne moins le vertige.§p2500§"
			"\n§d0§               §d90§Tu te demandes si c'est illégal de grimper sur les toits des bâtiments la nuit.§p1200§"  
			"§d100§\n\nAprès la bâtisse,§p300§ votre allée remonte à gauche vers un léger promontoir asphalté.§p1100§"
			"\nUltime place de parking avant le précipice.§p2300§"
			"\nLe stationnement garde le bâtiment de briques à sa gauche;§p330§ et une ligne jaune comme limite à droite,§p540§ même si le bord du précipice donne aussi une délimitation pas mal claire.§p2000§ Y'a des \"§p120§butoirs\"§p70§ en béton à droite et au devant de l'emplacement,§p140§ tout le long de la peinture jaune.§p2600§ À l'avant, c'est bouclé par une clôture haute de 3 ou 4 mètres,§p230§ qui empêche fermement l'accès aux toits adjacents,§p400§ barbelés et tout.§p2400§"
			"§d85§\nClôture sur laquelle les épaules de Sara sont accotées,§p140§ ses deux pieds repoussés contre le bump en béton.§p1500§ Les bras croisés,§p400§ un sourire qui sussure"
			"\n§d0§                          §d100§\"C'est par là qu'on passe\".§p3000§");

			//L'explication de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro¶sara==3");	
			u.adeb("§bintro¶sara~>0§§s§");
			u.afin("");
			u.atexte("§p1600§§d100§\n\"Fait qu'on a juste à monter la clôture,§bintro¶je~>4§§p300§ là,§p2900§"
			"\npis après on va vraiment jusqu'au coin,§p400§ jusqu'à l'autre clôture bizarre,§p200§ la genre de grille qui pend.§p1200§ Pis elle,§p90§ on la monte§p270§ - tu vas voir c'est pas tough - §p5200§ pis 'y reste juste à r'descendre pis on est sur les toîts.\"");
					//BTW: ici, on dit à un motif de l'autre canal (le prochain) de commencer à s'activer PENDANT que le texte de celui-ci défile. Ça fait que tout le monde parle en même temps. Effet intéressant.
			
			//Encore l'explication de Sara, mais en gestes (narration)	/ puis la tienne
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==4");	
			u.adeb("§bintro¶je~>0§§s§");
			u.afin("§bintro¶je~>5§");
			u.atexte("§d80§\n\nElle se redresse et pose la main à plat sur le grillage en losanges§p540§ avant de pointer l'extrémité en haut à droite,§p420§ avance d'un pas en bougeant de haut en bas avec ses deux bras,§p2800§ te regarde dans les yeux,§p1200§ fait un tour sur elle-même en crispant les dents avec ses doigts solidement accrochés à son imagination,§p100§§d90§ et fait semblant d'atterir sur ses deux pieds,§d110§ finalement.§p4500§µ"		//#1
			"§d100§\n\n\nElle te sourit,§300§ l'air fière de son explication.§p2000§"
			"§d110§\nTu clignes des paupières§p800§ une fois.§p2900§"		
			"§d100§\n\n\nLa tête te soupire§p110§ et t'avances pour constater le chemin toi-même.§p2100§µ"		//#2
			"§d100§\n\n\nA' s'retourne,§400§ prunelles pétillantes d'encouragement.§p2000§µ"		
			"\nTu lui donne un sourire indulgent,§p900§ et vas toi-même voir de quoi elle parlait.§p2100§µ"		//#3			
			"\n\nAu devant, la grande barrière de grillage en losanges§p90§ a son top en barbelés,§p390§ dressés en angle contre votre direction.§p900§ §d120§Fait que définitivement pas par là.§p2300§"	//#4
			"\n\nOui,§p370§ le devant du parking est flanqué d'un haute clôture terminée en barbelée.§p1100§ Gentil.§p1200§µ"	//#5
			"§d150§\n\nÀ droite,§p500§§d130§ par contre,§p430§§d110§ le grillage finit juste avant la falaise,§p290§ et une espèce de grille à gros barreaux verticaux prolonge la clôture au-dessus du précipiceµ"	//#6
			",§p600§§d100§ probablement pour nous empêcher de juste tourner le coin.§p1800§µ"		//#7
			"§p200§ :§p600§§d140§ veulent vraiment pas qu'on y aille,§p600§ sur les toîts.§p2000§µ"		//#8
			"§d100§\n\n\nSara émerge dans ton champs de vision,§p500§ comme une araignée qui commence à monter le grillage vers la droite§p150§-§p500§;§p800§"
			"§d80§\nE' veut passer par la grosse grille suspendue,§p300§ la seule place qu'y'a pas d'barbelés.§p600§ Pis q'est fucking lisse pis ac' une chute de 8 mètres en-d'sous d'elle.§p2500§µ"	//#9
			"§d120§\n\nMais la grille,§p180§ qui fait juste chiller au-ds'us du vide,§p440§ elle,§p580§ elle a pas de barbelés.§p400§.§p320§.§p3200§"
			"§d160§ Fait que par là.§p1500§.§p1100§.§p3000§");		//#10
			u.aordre("1-2-4-6-7-9;1-2-4-6-7-10;1-2-4-6-8-9;1-2-4-6-8-10;1-2-5-6-7-9;1-2-5-6-7-10;1-2-5-6-8-9;1-2-5-6-8-10;"
			"1-3-4-6-7-9;1-3-4-6-7-10;1-3-4-6-8-9;1-3-4-6-8-10;1-3-5-6-7-9;1-3-5-6-7-10;1-3-5-6-8-9;1-3-5-6-8-10");
	
			//Tu doutes de tes capacités, pour avoir une excuse pour commencer à intégrer les commandes manuelles
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==5");	
			u.adeb("§bintro¶je~>0§");
			u.afin("§bintro¶tuto~>1§");			
			u.atexte("§d90§\n\n\n\nTes yeux se ferment brièvement,§p430§ une seconde fois.§p1500§"
			"§d300§\n\n\n§d0§                  §d200§DANGEREUX.§p1600§"
			"§d100§\n\n\nT'ouvres l'oeil sur tes pieds,§p300§ au sol,§p430§§d120§ l'autre oeil,§p520§"
			"\n§d0§                §d100§t'es debout sur l'asphalte,§p460§ les orteils à peine sur la ligne jaune du devant du parking,§320§ juste avant le bump de béton.§p1300§"
			"§d90§\n\nSara estµ"																													//#1
			" rendue l'autre bord de la clôture§p130§,§p220§ déjà passée par-dessus la grille,§p180§ agrippée§p110§ légère encore dans le haut de la barrière,§p330§ accrochée.§p2600§µ"	//#2
			" les deux pieds 'dans 'clôture,§p360§§d120§ déjà grimpée pas mal haut,§390§§d140§ déjà pas mal proche du coin.§p200§.§p160§.§p3000§µ"					//#3
			"\n\n\n§d180§Tu ...§p820§,§p1240§§d120§        ...tu penses pas§p210§§d130§ être capable§d140§ de faire§p140§§d160§ ça§p300§?§p2600§µ"					//#4
			"§d90§\n\n\n\n\n\nTon pouls s'accélère alors que t'imagine §d100§ton corps §d110§frêle §d130§glisser,§p350§ perdre§d150§ pri§d170§se,§p460§§d200§ tomber§p600§ .§p600§"		
			"\n§d0§      .§p700§"
			"\n§d0§           .§p600§"
			"\n§d0§              .§p500§"
			"\n§d0§                   .§p400§"
			"\n§d0§                    .§p300§"
			"\n§d0§                     .§p200§"
			"\n§d0§                      .§p100§"
			"\n§d0§                      .§d90§ Tu -§p220§"
			"\n\n\nTu ressaisis ton corps§p420§, pis avances d'un coup pour bredouiller à Sara que t'es pas down finalement§p620§;"
			"\n§d110§     'estµ"																										//#5
			"\n\n\n§d0§                          §d90§ Fuck, a'§p260§ -§p470§;§d0§     §d80§Fuck!§p2100§"
			"\n\n§p100§Tu restes plantée où tu es,§p750§ au devant du parking,§p680§ même pas encore passé la ligne jaune à terre.§p1800§");	//6
			u.aordre("1-2-4;1-3-4;5-2-6;5-3-6");

			//La voix du tutoriel qui te parle
			u.nvauto(); u.acanal("msn");		
			u.acond("intro¶tuto==1");	
			u.adeb("§bintro¶tuto~>0§");
			u.afin("§f0§§bintro¶tuto~>2§");			
			u.atexte("                           C'est main§f1§tenant à toi de µ"		//#1
			"guiderµ"		//#2
			"dirigerµ"		//3
			"commanderµ"	//#4
			" [t]es actesµ"			//#5
			" [t]es actionsµ"			//#6
			".§p1000§ Écris la µ"		//#7
			"commandeµ"			//#8
			"directiveµ"			//#9
			" que tu souhaites [t]e donner,§p610§ puis appuie sur §p120§[ENTER§p90§].§p2200§");		//#10
			u.aordre("1-2-5-7-8-10;1-3-5-7-8-10;1-2-6-7-8-10;1-3-6-7-8-10;1-2-5-7-9-10;1-3-5-7-9-10;1-4-5-7-9-10;1-2-6-7-9-10;1-3-6-7-9-10;1-4-6-7-9-10");

			//Les mille et une suggestions d'actions à faire
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin("§bintro¶desuet~>1§§bcloture¶choix~>1§"); u.atexte("§p7130§Avancer§p1100§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p8840§Franchir la ligne§p2000§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p9270§Continuer§p800§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p11600§Monter dans le grillage§p1400§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p12310§Être capable de grimper§p1800§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p13530§Poursuivre§p2300§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p16020§Aller de l'avant§p1600§");			
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p16250§Rassembler son courage§p1800§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p18510§Monter sur les toits§p3800§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p19750§Surmonter sa peur§p2200§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p22670§Franchir la ligne jaune§p3000§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p25830§Rejoindre Sara§p1800§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin("§bcloture¶sara~>1§"); u.atexte("§p26930§Avancer jusqu'à la clôture§p2100§");


				//Pis... je crois que le code bug quand y'a plus de msn qui veulent s'inscrire que la limite imposée???
							//Faudrait vérifier ça!!!
							
//-----------------------------------------------------------------|   Traverser la clôture  |--------------------------------------------------------------------------------\\
							
	//Débuter un chapitre dont le but sera de passer par-dessus la clôture
	u.nvchapt();
		u.ccond("intro¶desuet&!cloture¶desuet");        //Rendre le premier chapitre accessible seulement quand t'as pas encore traversé + quand ce n'est plus l'intro													
						//Première condition composée!
							//Le symbole '&' signifie que les deux conditions doivent être À LA FOIS remplie pour que le motif soit activé. Ça veut dire "ET".
							//Si on voit '|', au contraire, ça signifie qu'une ou l'autre des conditions doivent être remplies, ou encore les deux à la fois. '|' signifie "OU".
						//J'utilise aussi de bêtes raccourcis d'expression logique: 
							//"intro¶desuet" tout seul signifie que "intro¶desuet" est égal à n'importe quoi sauf 0.  
								//J'aurais aussi pu l'écrire "intro¶desuet!=0", car l'opérateur "!=" signifie "pas égal à".
							//et "!cloture¶desuet" signifie que "cloture¶desuet" n'est pas égal à "n'importe quoi sauf 0". Donc est égal à 0. Donc "cloture¶desuet==0", dans le fond.
					
			//Sara te rassures
			u.nvauto(); u.acanal("sara");					//Le texte est parsemé de "§r§". Ce code spécial permet d'intégrer le motif manuel qui était en réserve au bon moment.						
			u.acond("cloture¶sara==1");						//Cette mécanique est utilisée afin de ne pas interrompre une phrase n'importe quand par la réception d'une commande.
			u.adeb("§bcloture¶sara~>0§§s§§p4000§\"");
			u.afin("§mabandonner§\""); 		//Le code spécial §m§ est pour forcer l'exécution d'un motif manuel dont le nom correspond
			u.atexte("§d100§\n\n\n\n\nTu vois§r§§p3400§§r§ c'est vraiment simple§r§§p1400§§r§,§p1800§§r§§p2120§§r§ c'est juste la partie où tu changes de bord §r§§2300§qui§p2000§ est un peu tricky§r§,§p6130§§r§ mais sinon y'a vraiment pas à s'inquiéter§r§,§p4700§§r§ tu vas voir ça va full bien s'passer§r§§p3100§§r§,§p4810§§r§ pis j'suis là si y'a d'quoi.\"§r§§p5600§§r§"	
			"§p4000§§r§\n\n\"§d110§Ok§r§,§p2430§§r§ fais juste avancer lentement§r§,§p4020§§r§ une fois que t'es dedans§p1400§ ça se fait tu seul.§r§§p5850§§r§ Sérieux.§r§§p4570§§r§§p3000§§r§§p3300§§r§µ"		//#1
			"§p3100§§r§§d200§\nCommmmmmme ooon§r§nnnnnnnnnnn§r§§p600§.§r§§2200§§r§§d100§ Come on!§p1400§§r§ T'avais dit qu'ça t'tentait!§r§§p2700§§r§§p3000§§r§µ"		//#2
			"§p2200§§r§§d160§§bcloture¶estucorrecte~>1§§\nOohh nooon,§p900§§r§ t'as l'air un peu cassée -§r§§p400§§d90§§r§"
			"§d0§                 §d90§Ben non pas cassée j'voulais pas dire ça §p110§mais genre§r§§p600§§d140§§r§ absent§p200§e?§r§§p1800§§d110§§r§ Genre t'as pas l'air§r§§p670§§r§ là?§r§§2200§§r§"
			"§d90§Ok j'ai une idée§p300§§r§ :§p500§§r§§d110§ viens mettre tes deux mains§r§ contre la clôture§r§ pis fais juste te soulever§r§ tu vas voir à quel point y'a rien là§r§ pis ça va full te grounder§r§.§p2000§ Right§p300§?§r§§p1800§§r§ Right.§r§§p3200§§bcloture¶estucorrecte~>0§µ"		//#3			
			"\n§d0§          §d90§ok fais juste bouger,§p1830§ au moins§r§,§p4650§§r§ avance jusqu'à' clotûre§r§§p7560§§r§,§p2630§§r§§p2000§§r§ envoyes§r§,§1470§§r§§p2000§§r§ y fait frette!§r§§p2100§§r§§p2000§§r§");		//#4
									
			//Sara constate que t'es correcte parce que tu bouges
			u.nvauto(); u.acanal("sara");
			u.acond("cloture¶estucorrecte==1&cloture¶continuer==1|cloture¶estucorrecte==1&cloture¶grimper==1|cloture¶estucorrecte==1&cloture¶grimper==1|cloture¶estucorrecte==1&cloture¶courage==1");	
			u.adeb("§dcloture¶estucorrecte~>0§§p700§§d90§");		//Dans la condition, '|' signifie "ou".
			u.afin("\"");
			u.atexte(" - µ"		//#1
			"\n§d0§           §d90§µ"	//#2
			"Ah nice,§p400§ tµ"		//#3
			"Cool,§p300§ tµ"		//#4
			"Yé,§p450§ tµ"			//#5
			"Yipip §p300§bravo!§p810§ Tµ"		//#6
			"u commençais à m'inquiéter!§p800§µ"	//#7
			"'es encore là!§p900§µ"			//#8
			"'as r'commencé à bouger!§p1000§µ"		//#9
			"'as surmonté l'inertie!§p700§");		//#10
			u.aordre("1-3-7;1-3-8;1-3-9;1-3-10;1-4-7;1-4-8;1-4-9;1-4-10;1-5-7;1-5-8;1-5-9;1-5-10;1-6-7;1-6-8;1-6-9;1-6-10;"
			"2-3-7;2-3-8;2-3-9;2-3-10;2-4-7;2-4-8;2-4-9;2-4-10;2-5-7;2-5-8;2-5-9;2-5-10;2-6-7;2-6-8;2-6-9;2-6-10");

			//Sara chiale parce que t'abandonne
			u.nvauto(); u.acanal("sara");
			u.acond("cloture¶abandon==1&cloture¶sara==2");
			u.adeb("§dcloture¶sara~>0§§c§§p2200§§d110§\"");
			u.afin("\""); u.aover();
			u.atexte("\n\nAh bin.§p700§  Ah bin nice.§p1200§     Bon.§2000§ Fait que§p700§ bonne soirée,§p500§ là.§p1000§µ"
			"Come on,§p700§ pars pas!§p1500§ Come§p400§-§p500§on§p200§!§p1800§ Heille!§p2000§");
			u.aordre("1;2");
			
			//Choix: "abandonner"    (Premier motif manuel! Wouhou!)
			u.nvmanu("abandonner"); u.mcanal("je");
			u.mcond("cloture¶choix==1");
			u.mcomm("(reculer|retourner|aller|marcher|se diriger&vers|en direction d|pour atteindre|jusqu'&ailleurs|chapelle|église|cathédrale|rue|maison|chez soi|chez toi)"
			"(abandonner|quitter|s'en aller|partir)");		// ()() = deux façons différentes d'appeler cette commande
					//Un motif manuel a besoin de commandes pour être appelé!
						//Cette fonction définit quel mots-clés auront besoin d'être présents (ou absent!) dans la commande entrée par la joueuse pour que le motif manuel s'active.
						//Elle permet d'utiliser plusieurs façon de dire la commande (séparées par des parenthèses) : ici, genre "avancer vers la clôture" ou genre "rejoindre Sara".
						//À l'intérieur de chaque façon de dire la commande (donc à l'intérieur de la parenthèse), on retrouve:
							//Des groupes de mots (séparés par '&'), qui doivent chacun être présent pour que la commande soit validée : ici, "avancer|continuer", "vers|en direction d|pour atteindre|jusqu'" et "clôture|grillage|barrière|toît" sont des groupes de mots différents
							//À l'intérieur des groupes de mots, il y a:
								//Des synonymes (séparés par '|')! En gros, on a besoin d'avoir soit "Sara", soit "amie", soit "complice", soit "partenaire" ou soit "compagne" pour que le groupe de mot soit reconnu comme présent.
							//Ils n'apparaissent pas ici, mais chaque façon de dire la commande peut aussi contenir des mots à éviter (mis entre crochets, et séparés par '|')!
					//Ici, autant "avancer en direction des toîts", "continuer jusqu'au grillage" et "aller rejoindre ton amie" seront reconnues commes des commandes valides pour ce motif.
			u.mdeb("§bcloture¶choix~>0§§bcloture¶abandon~>1§§bcloture¶sara~>2§§s§§d120§"); 	
					//Nouveau code spécial:
						//"§o§" ('o' pour overwrite) sert à effacer le texte du canal spécifié (ici, "sara") pour arrêter son affichage. En gros, on "coupe à parole" à Sara.
						//Pour être sûre de bien fermer ça propret, on place la terminaison du canal juste après avoir tout effacé. Ici, ça permet de fermer son dialogue avec de derniers guillements (voir "u.canalterminaison()")
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite; il faudra attendre qu'un code spécial "§r§" soit atteint.
			u.mfin("\n\n\nC'EST LA FINNNNNNNNNN");
			u.mtexte("\nNon,§p300§ non;§p1000§ non.§p2600§ Tu vas pas faire ça.§p1300§ C'est trop glissant pis ça vaut pas la peine.§p2300§");
																				
			//Choix: "continuer", "avancer"	et autres formulations vagues
			u.nvmanu("aller de l'avant"); u.mcanal("je");
			u.mcond("cloture¶choix==1");
			u.mcomm("(marcher|se diriger|avancer|continuer|aller&vers|en direction d|pour atteindre|jusqu'&clôture|grillage|barrière|toît)(rejoindre|aller à la rencontre de|atteindre|rattraper&Sara|amie|complice|partenaire|compagne)");		// ()() = deux façons différentes d'appeler cette commande
			u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
					//On peut également définir des commandes qui doivent être écrites mots pour mots pour être reconnues
						//Ça permet, par exemple, d'éviter de valider des commandes "contraires" avec des mots-clés trop flous:
						//Par exemple, "avancer" va te faire avancer vers la clôture, mais pas "avancer vers la cathédrale" (si on avait mis ces synonymes comme autre façon de dire la commande, tout ce qui aurait contenu "avancer" aurait passé comme bon).
			u.mdeb("§osara§§bcloture¶choix~>0§§bcloture¶continuer~>1§§s§§d120§"); 		//Dès que le motif est lu, on efface ce que Sarah avait à dire
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite: il sera mis en réserve. Il faudra attendre qu'un code spécial "§r§" soit lu par n'importe quel canal (ici, ça va arriver dans le dialogue de Sara).
			u.mfin("§bcloture¶continuer~>2§");
			u.mtexte("§d120§\n\nOuin,§p800§ tant qu'à déjà être rendue§p140§...§p1600§µ"				//Segment #1
			"§d140§\n\n\nNon,§p300§ tu vas pas chocker ici.§p1130§§d110§ T'es meilleure que ça.§p1800§§µ"		//Segment #2
			"\n\n\nTu tires ton capuchon vers l'arrière en levant le menton,§p350§"		//Segment #3
			"\ny'est plus dans tes yeux maintenant.§p1420§µ"							//Segment #3 (encore)
			"\n\nUn grand respire,§p570§ tu soulèves tes yeux§p430§ à hauteur de Sara.§1170§ 'A te sourit,§p440§ puis marmonne qu'ses mains sont gelées.§p620§µ"		//Segment #4
			"§d90§ Tu lances ta jambes en avant dans un grand pas,§230§ par-dessus l'obstacle de béton pis tu mets tes mains sur la grille.§p1000§");			//Segment #5
			u.mordre("1-3-5;1-4-5;2-3-5;2-4-5");		//Par défaut, chaque combinaison a une chance égale de se produire
	
				//Suite de "continuer" : faut demander explicitement de grimper (bout automatique qui l'explicite)
				u.nvauto(); u.acanal("je");
				u.acond("cloture¶continuer==2");
				u.adeb("§bcloture¶choix~>2§"); 
				u.afin("§mgrimper continuer§"); 		//Le code spécial §m§ est pour forcer l'exécution d'un motif manuel dont le nom correspond
				u.atexte("§d80§\nOuin§r§,§p400§ tu sais pas trop comment prendre ça§r§,§p510§ finalement.§r§§p820§    §r§Tu§p500§.§p420§..§r§§p370§ tu guess qu'il faut que t'escalades?§r§§p1500§§r§§d130§ T'insères tes doigts à l'intérieur des fils losangés.§r§§p3520§§r§ Ben,§p410§ d'ins trous d'la clôture,§p300§ dans l'fond.§r§§p4200§§r§"
				"\nÇa devrait être simple.§r§§p3600§§r§ T'as juster à te hisser.§r§§p4200§§r§ Te monter§p400§§r§,§p520§ avec un peu de force dans les bras§p300§.§r§§p3500§§r§§p3600§§r§§p4020§§r§ Bon.§p760§");
			
				//Suite de "continuer" : faut demander explicitement de grimper (mais il se passe automatiquement si on attend assez longtemps)
				u.nvmanu("grimper continuer"); u.mcanal("je");
				u.mcond("cloture¶continuer==2");
				u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&clôture|grillage|barrière|grille|toît)(grimper|monter|escalader|se hisser)");
				u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
				u.mdeb("§bcloture¶choix~>0§"); 
				u.mreserve(); u.mover();
				u.mfin("§bcloture¶grimper~>2§");
				u.mtexte("§d80§ Tu places tes mains plus haut,§p220§ sécures tes doigts§p100§ pis tires§p200§§d100§ comme "
				"\n§d0§                     §d70§tes bottes glissent contre la clôture§p210§;§p330§ tu réussis à avoir une pogne pour tes pieds.§p1100§"
				"§bcloture¶grimper~>1§"
				"§d90§\n\nNice,§p140§ t'es d'ins airs.§p2300§");

			//Choix: "Franchir la ligne" ou autres formulation dramatiques/littérales (parce qu'il faut d'abord que t'enjambe la ligne de peinture jaune)
			u.nvmanu("franchir la ligne jaune"); u.mcanal("je");
			u.mcond("cloture¶choix==1");
			u.mcomm("(franchir|traverser|outrepasser|piétiner|fouler|marcher sur|passer|continuer outre&ligne|limite|trait|délimitation|frontière)");
			u.mdeb("§osara§§bcloture¶choix~>0§§bcloture¶franchir~>1§§s§§d110§"); 
			u.mfin("§bcloture¶franchir~>2§");
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite; il faudra attendre qu'un code spécial "§r§" soit atteint.
			u.mtexte("\n\n\nFuck it.§p800§µ"		//Segment #1
			"\nTu regardes la ligne jaune à terre.§p500§ La peinture écaillée te fixe en retour.§p800§µ"		//Segment #2
			"\n\nLes bornes administratives d'un parking de presbytère ne peuvent plus te contenir.§1500§µ"		//Segment #3
			"\nTu choisis ton camp pour ce soir.§p800§"		//Segment #4
			" Tu lèves solonellement ta botte,§p400§ et passe outre la limite du parking.§p1300§"
			"\nT'as la jambe droite accotée sur le butoir de béton et tu es prête à affronter n'importe quoi.§p1100§µ"			//Segment #5
			"\nT'enjambes ce qui te séparait encore de la clôture : un trait peinturé à terre pis un rectangle de ciment bas.§p1400§µ"			//Segment #6
			"\n\nTu foules la délimitation stationnaire d'un bref bond;§p1000§ conquis le petit bump de béton en deux temps.§p1600§"
			"\nLa clôture n'a qu'à bien se tenir.§p2600§");			//Segment #7
			u.mordre("1-5;1-6;1-7;2-5;2-6;2-7;3-5;3-6;3-7;4-5;4-6;4-7");

				//Suite de "franchir" : faut demander explicitement de grimper (bout automatique qui l'explicite)
				u.nvauto(); u.acanal("je");
				u.acond("cloture¶franchir==2");
				u.adeb("§bcloture¶choix~>2§"); 
				u.afin("§mgrimper franchir§"); 		//Le code spécial §m§ est pour forcer l'exécution d'un motif manuel dont le nom correspond
				u.atexte("§d80§");
			
				//Suite de "franchir" : faut demander explicitement de grimper (mais il se passe automatiquement si on attend assez longtemps)
				u.nvmanu("grimper franchir"); u.mcanal("je");
				u.mcond("cloture¶franchir==2");
				u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir|vaincre|conquérir|braver|soumettre&clôture|grillage|barrière|grille|toît)(grimper|monter|escalader|se hisser)");
				u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
				u.mdeb("§bcloture¶choix~>0§"); 
				u.mreserve(); u.mover();
				u.mfin("§bcloture¶grimper~>2§");
				u.mtexte("");
			
			//Choix: "Surmonter sa peur" / "Rassembler son courage" / "Prendre son courage à deux mains", etc.
			u.nvmanu("surmonter sa peur"); u.mcanal("je");
			u.mcond("cloture¶choix==1");
			u.mcomm("(être capable d|pouvoir|être en posture de|se forcer à|se motiver à&grimper|monter|escalader|agripper|se hisser|franchir&clôture|grillage|barrière|grille|toît)"
			"(être capable d|pouvoir|être en posture de|se forcer à|se motiver à&grimper|escalader|se hisser)");
			u.mcommexact("surmonter sa peur|prendre son courage à deux mains|se prendre en mains|rassembler son courage|être courageuse");
			u.mdeb("§osara§§bcloture¶choix~>0§§bcloture¶courage~>1§§s§§d120§"); 
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite; il faudra attendre qu'un code spécial "§r§" soit atteint.
			u.mfin("\n\n\nC'EST LA FINNNNNN");
			u.mtexte("\n\n\nTU RASSEMBLES TON COURAGE C'EST BEAU CHAMPIONNE");					
						
			//Choix: "Grimper" ou autres
			u.nvmanu("grimper la clôture"); u.mcanal("je");
			u.mcond("cloture¶choix==1");
			u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&clôture|grillage|barrière|grille|toît[être capable d|pouvoir|être en posture de|se forcer à|se motiver à])"		// [] = on ne les veut pas!
			"(poser|passer|mettre|accoter|reposer|déposer&main|gant|doigt&contre|sur|le long|au travers d&clôture|grillage|barrière|grille)");
			u.mcommexact("grimper|escalader|se hisser");
			u.mdeb("§osara§§bcloture¶choix~>0§§bcloture¶grimper~>0§§s§§d120§"); 
			u.mfin("§bcloture¶grimper~>2§");
			u.mreserve();		
			u.mtexte("\n\n\n\nTu lèves un bon pas franc et tu te ramasses à trois pouces du grillage.§p1400§ T'étends ton bras droit,§p540§ fermes tes doigts contre les fils froids.§p700§§d130§ Positionnes ton autre main,§p670§§d150§ baisse ton bassin pour un §p320§§d180§élan§d230§..."
			"§d0§\n\n               §d80§t'pousses tes rotules en d'scendant dans les vides en losanges§p130§ parc'qu'tes bottes ont glissé§p200§ pis t'doigts tirent§p100§ pis tu patines encore p'tu lances ton gant plus haut encore pis ça clenche §p140§- ton pied pogne' le trou ton pied s'appuie!§p2200§"
			"§bcloture¶grimper~1§"
			"§d120§\nGode.§r§§p1000§§d100§§r§ Fait que t'es s'a clôture.§r§§p1900§§r§ Le vent souffle une§d150§ bourrasque.§r§§d90§§p2600§§r§");
					
				//Suite de "grimper" (point commun de toutes les avenues) : t'es dans les airs, pis faut bouger sur la clôture, sinon tes bras fatiguent pis tu retombes
				u.nvauto(); u.acanal("je");
				u.acond("cloture¶grimper==2");
				u.adeb("§d90§");
				u.afin("§bcloture¶grimper~>3§");
				u.atexte(" Fait que t'imagines que tu dois te traîner à droite,§p800§§r§ dans le haut de la grosse grille verticale.§p2400§§r§§p1100§ ");
							//Reste à avancer ce texte plus!
						
						
				//Choix: "Grimper encore" (si t'es tombée)
				u.nvmanu("grimper encore"); u.mcanal("je");
				u.mcond("cloture¶grimper==3");
				u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&clôture|grillage|barrière|grille|toît[être capable d|pouvoir|être en posture de|se forcer à|se motiver à])"		// [] = on ne les veut pas!
				"(poser|passer|mettre|accoter|reposer|déposer&main|gant|doigt&contre|sur|le long|au travers d&clôture|grillage|barrière|grille)");
				u.mcommexact("grimper|escalader|se hisser");
				u.mdeb("§bcloture¶grimper~>0§§s§§d120§");
				u.mreserve();		
				u.mtexte(""); 									
										
				//Choix: "Se déplacer sur la clôture"						
										
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

	//Créer le menu principal
	u.nvmenu("principal");
	
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
		u.menunvbouton("Lancer le jeu","§bintro¶je~>1§§j§");
			//Ce bouton aura pour effet de modifier un rayon de la bibliothèque, puis de lancer la boucle "jouer" (§j§, 'j' pour "jouer"), qui lance le programme. 
	
		//Définir le deuxième bouton, ainsi que son effet
		u.menunvbouton("Quitter","§a§");	
			//Ce bouton aura pour effet de terminer le programme (§a§, 'a' pour "abort()").

//-----------------------------------------------------------------|      Menu de pause      |--------------------------------------------------------------------------------\\

	//Créer le menu de pause
	u.nvmenu("pause");				//Par défaut, si on ne spécifie pas d'arrière-plan, le contenu des mémoires sera utilisé

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
		u.menunvbouton("Revenir au \nmenu principal","§zprincipal§");	
			//Ce bouton aura pour effet d'appeler le menu principal (§z§, 'z' pour... rien en fait. 'm' était déjà pris dans les codes spéciaux de canaux, alors j'ai pris z. Que je ré-utilise ici).			

			//Comme le deuxième bouton a deux lignes, je vais agrandir tous les boutons à une hauteur de 4 (à la place de 3):
			u.menuhauteurbouton(4);

		//Définir le troisième bouton, ainsi que son effet
		u.menunvbouton("Quitter le jeu","§a§");	
			//Ce bouton aura pour effet de terminer le programme (§a§, 'a' pour "abort()").		

		//Définir l'action de la touche [ESCAPE]
			//Par défaut, cette touche a pour conséquence la fermeture du programme.
		u.menuescape("§u§");		//Régler [ESCAPE] pour revenir au jeu

//-----------------------------------------------------------------|        Exécuter         |--------------------------------------------------------------------------------\\		
		
	//Commencer proprement
	u.debuter();

}		
