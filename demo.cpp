/*
			///||================================---2020/01/18---================================||\\\
\\\||================================---Tutoriel / Démo du potentiel interactif / narratif---================================||///
*/


# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/cadre_fonctionnel_global.cpp"


//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\

int main(void) {

	//Créer l'objet où tout est initié
	univers u;
	//Ouvrir une fenêtre de bonnes dimensions et initialiser les objets de sauvegarde
	u.MettreDansLeMain();
	
//-----------------------------------------------------------------|      Bibliothèque       |--------------------------------------------------------------------------------\\
	
	u.nvrayon("intro");
		u.nvlivre("desuet");	
		u.nvlivre("je");
		u.nvlivre("sara");
		u.nvlivre("tuto");
		
			
			
//-----------------------------------------------------------------|          Début          |--------------------------------------------------------------------------------\\

	//Créer un canal
	u.nvcanal("je"); u.canaldelai(80); 
	u.nvcanal("sara"); u.canaldelai(130); u.canalalinea(6);
		
	//Débuter un chapitre
	u.nvchapt();
		u.ccond("!intro¶desuet");        //Rendre le premier chapitre accessible seulement quand c'est l'intro 

			//Juste le début
			u.nvauto(); u.acanal("je");	                                    	
			u.acond("intro¶je==1");	
			u.adeb("§bintro¶je=0§");
			u.afin("§bintro¶sara=1§");
			u.atexte("T'as froid aux joues.§p1400§"
			"\n§d0§                     §d80§Pis aux cuisses.");				

			//Messagerie de directives du début (temporaire?)
			u.nvauto(); u.acanal("msn");
			u.acond("intro¶je==1");
			u.afin("§p2600§§f0§");
			u.atexte("§p4000§Pour qui§f1§tter le programme,§p400§ appuie sur §p210§[ESC§p110§].§p1200§"
			"\nPour modifier la vitesse de défilement,§p600§ appuie sur les touches §p90§[HAUT§p100§] et §p140§[BAS§p90§].");
				
			//La réponse de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro¶sara==1");	
			u.adeb("§bintro¶sara=0§");
			u.afin("§bintro¶je=2§");
			u.atexte("§p1800§\n\"Come on,§p1100§"
			"\n§d0§          §d130§on est presqu'arrivées!\"");

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==2");	
			u.adeb("§bintro¶je=0§§s§");
			u.afin("§bintro¶sara=2§");
			u.atexte("§p400§\n\n         T'accélères le pas,§p600§ moins pour la rejoindre§p100§ que pour réchauffer tes jambes.§p1200§§d110§ Le vent,§p500§ criss.§p700§ Le vent.§p1600§"
			"\n§d90§Tu lèves les yeux§p100§ juste à la limite de ton capuchon§p300§ pis Sara est quand même loin en avant.§p1400§§d80§ Tu te presses un peu plus.§p2800§"
			"\n\nTraverses une rue,§p400§ t'es au coin de la cathédrale§p300§ pis le vent charge de plus belle depuis ta droite.§p2400§ Caliss.§p3000§§d90§ Sara est déjà rendue plus bas,§p500§ a'longe la grosse chapelle.§p2300§"
			"\n§d0§                       §d80§Tu descends au jogging§p120§, §p400§"
			"\n§d0§                                                §d80§rejoindre au plus vite l'énorme pare-vent de pierre.§p1800§"
			"\nTa jupe virevolte sur tes genoux,§p200§ expose tes cuisses aux rafales;§p2300§ Pas l'meilleur choix de vêtements.§p4300§"
			"\n\n     La cathédrale coupe le vent§p150§ pour vrai.§3100§ "
			"\n\n\nSara t'as un peu attendue et te sourit avec son trop d'excitation.§p2200§");

			//La réponse de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro¶sara==2");	
			u.adeb("§bintro¶sara=0§§s§");
			u.afin("§bintro¶je=3§");
			u.atexte("§p130§§d110§\n\"J'te jure,§p260§ c'est l'meilleur spot au monde,§p240§ sur les toits du centro!\"");			//FAUDRAIT CHANGER CETTE PHRASE POUR QUELQUE CHOSE DE PLUS CRÉDIBLE

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==3");	
			u.adeb("§bintro¶je=0§§s§");
			u.afin("§bintro¶sara=3§");
			u.atexte("§p3100§Tu peux pas empêcher tes commissures engourdies de remonter un peu.§p2600§"
			"\n\n§d90§Encore quelques pas ensemble et vous êtes à l'arrière d'la maison de Dieu§p140§ pis l'vent reprend.§p560§§100§ Vraiment une belle soirée pour être sur l'top d'une colline.§2600§"
			"\n\n§d90§Sara te traîne encore plus derrière l'église,§p220§ dans une allée séparée de la rue par un p'tit muret.§p1800§ À ta gauche,§p160§ tu peux voir le frimas sur les toits plats des buildings adjacents,§p240§ pis les lumières de la ville,§p130§ de l'autre côté d'la rivière.§p2000§ Vous êtes pas mal haut,§p180§ finalement.§p3000§"
			"\nTu continues et un long bâtiment de briques s'érige entre le bord de la falaise et vous,§p110§ coupe le paysage.§p900§ Ça donne moins le vertige.§p2500§"

			"\n§d0§               §d90§Tu te demandes si c'est illégal de grimper sur les toits des bâtiments la nuit.§p1200§"   //Phrase nouvelle; essai; est-ce que c'est bon?
			
			"§d100§\n\nAprès la bâtisse,§p300§ votre allée remonte à gauche vers un léger promontoir asphalté.§p1100§"
			"\nUltime place de parking avant le précipice.§p2300§"
			"\nLe stationnement garde le bâtiment de briques à sa gauche;§p330§ et une ligne jaune comme limite à droite,§p540§ même si le bord du précipice donne aussi une délimitation pas mal claire.§p2000§ Y'a des \"§p120§butoirs\"§p70§ en béton à droite et au devant de l'emplacement,§p140§ tout le long de la peinture jaune.§p2600§ À l'avant, c'est bouclé par une clôture haute de 3 ou 4 mètres,§p230§ qui empêche fermement l'accès aux toits adjacents,§p400§ barbelés et tout.§p2400§"
			"§d85§\nClôture sur laquelle les épaules de Sara sont accotées,§p140§ ses deux pieds repoussés contre le bump en béton.§p1500§ Les bras croisés,§p400§ un sourire qui sussure"
			"\n§d0§                          §d100§\"C'est par là qu'on passe\".§p3000§");

			//L'explication de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro¶sara==3");	
			u.adeb("§bintro¶sara=0§§s§");
			u.afin("");
			u.atexte("§p1600§§d100§\n\"Fait qu'on a juste à monter la clôture,§bintro¶je=4§§p300§ là,§p2900§"
			"\npis après on va vraiment jusqu'au coin,§p400§ jusqu'à l'autre clôture bizarre,§p200§ la genre de grille qui pend.§p1200§ Pis elle,§p90§ on la monte§p270§ - tu vas voir c'est pas tough - §p5200§ pis 'y reste juste à r'descendre pis on est sur les toîts.\"");
			
			//Encore l'explication de Sara, mais en gestes (narration)	/ puis la tienne
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==4");	
			u.adeb("§bintro¶je=0§§s§");
			u.afin("§bintro¶je=5§");
			u.atexte("§d80§\n\nElle se redresse et pose la main à plat sur le grillage en losanges§p540§ avant de pointer l'extrémité en haut à droite,§p420§ avance d'un pas en bougeant de haut en bas avec ses deux bras,§p2800§ te regarde dans les yeux,§p1200§ fait un tour sur elle-même en crispant les dents avec ses doigts solidement accrochés à son imagination,§p100§§d90§ et fait semblant d'atterir sur ses deux pieds,§d110§ finalement.§p4500§"
			"§d100§\n\n\nElle te sourit,§300§ l'air fière de son explication.§p2000§"
			"§d110§\nTu clignes des paupières§p800§ une fois.§p2900§"
			"§d100§\n\n\nLa tête te soupire§p110§ et t'avances pour constater le chemin toi-même.§p2100§"
			"\n\nAu devant, la grande barrière de grillage en losanges§p90§ a son top en barbelés,§p390§ dressés en angle contre votre direction.§p900§ §d120§Fait que définitivement pas par là.§p2300§"
			"§d150§\n\nÀ droite,§p500§§d130§ par contre,§p430§§d110§ le grillage finit juste avant la falaise,§p290§ et une espèce de grille à gros barreaux verticaux prolonge la clôture au-dessus du précipice,§p600§§d100§ probablement pour nous empêcher de juste tourner le coin.§p1800§"
			"§d120§\n\nMais la grille,§p180§ qui fait juste chiller au-ds'us du vide,§p440§ elle,§p580§ elle a pas de barbelés.§p400§.§p320§.§p3200§"
			"§d160§ Fait que par là.§p3800§");
	
			//Tu doutes de tes capacités, et j'mets plein de vocabulaire à saisir
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==5");	
			u.adeb("§bintro¶je=0§");
			u.afin("§bintro¶tuto=1§");			
			u.atexte("§d90§\n\n\n\nTes yeux se ferment brièvement,§p430§ une seconde fois.§p1900§"
			"§d300§\n\n\n§d0§                  §d400§DANGEREUX.§p2200§"
			"§d100§\n\n\nT'ouvres l'oeil sur tes pieds,§p300§ au sol,§p430§§d120§ l'autre oeil,§p520§"
			"\n§d0§                §d100§t'es debout sur l'asphalte,§p460§ les orteils à peine sur la ligne jaune du devant du parking,§320§ juste avant le bump de béton.§p1300§"
			"§d90§\n\nSara est rendue l'autre bord de la clôture§p130§,§p220§ déjà passée par-dessus la grille,§p180§ agrippée§p110§ légère encore dans le haut de la barrière,§p330§ accrochée.§p2600§"
			"\n\n\n§d180§Tu ...§p820§,§p1240§§d120§        ...tu penses pas§p210§§d130§ être capable§d140§ de faire§p140§§d160§ ça§p300§?§p2600§");

			//La voix du tutoriel qui te parle
			u.nvauto(); u.acanal("msn");		
			u.acond("intro¶tuto==1");	
			u.adeb("§bintro¶tuto=0§");
			u.afin("§f0§§bintro¶tuto=2§");			
			u.atexte("§p600§       C'est main§f1§tenant à toi de guider [t]es actes.§p1000§ Écris la commande que tu souhaites effectuer,§p610§ puis appuie sur §p120§[ENTER§p90§].§p2200§");

			//Les mille et une suggestions d'actions à faire
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p7130§Avancer§p1100§");
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
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin("§bintro¶saraquatre=1§"); u.atexte("§p26930§Avancer jusqu'à la clôture§p2100§");

			//Sara te rassures
			u.nvauto(); u.acanal("sara");					//Le texte est parsemé de "§r§". Ce code spécial permet d'intégrer le motif manuel qui était en réserve au bon moment.
			u.acond("intro¶sara==4");						//Cette mécanique est intégrée afin de ne pas interrompre une phrase n'importe quand par la réception d'une commande.
			u.adeb("§bintro¶sara=0§§s§§p4000§");
			u.afin("§bintro¶sara=5§");
			u.atexte("§d120§\n\n\n\n\n\"Tu vois§r§§p6400§§r§ c'est vraiment simple§r§§p3400§§r§,§p7120§§r§ c'est juste la partie où tu changes de bord §r§§2300§qui§p4000§ est un peu tricky§r§,§p9130§§r§ mais sinon y'a vraiment pas à s'inquiéter§r§,§p6700§§r§ tu vas voir ça va full bien s'passer§r§§p3100§§r§,§p4810§§r§ pis j'suis là si y'a d'quoi.\"§r§§p5600§§r§"	
								//Y'a un peu un changement de ton ici... On peut vouloir ça; ou non.
			"§p4000§§r§\n\n\"§d130§Ok§r§,§p3430§§r§ fais juste avancer lentement§r§,§p6020§§r§ une fois que t'es dedans§p1400§ ça se fait tu seul.§r§§p7850§§r§ Sérieux.§r§§p7670§§r§§p6300§§r§"
			"\n§d0§          §d110§ok fais juste bouger,§p1830§ au moins§r§,§p4650§§r§ avance jusqu'à' clotûre§r§§p7560§§r§,§p4630§§r§ envoyes§r§,§4470§§r§ y fait frette!§r§§p4100§§r§");


				//Pis... je crois que le code bug quand y'a plus de msn qui veulent s'inscrire que la limite imposée???
							//Faudrait vérifier ça!!!
							
					
			//Choix: "continuer", "avancer"	et autres formulations vagues
			u.nvmanu("aller de l'avant"); u.mcanal("je");
			u.mcond("intro¶tuto==3");
			u.mcomm("(avancer|continuer&vers|en direction d|pour atteindre|jusqu'&clôture|grillage|barrière|toît)(rejoindre|aller à la rencontre de|atteindre|rattraper&Sara|amie|complice|partenaire|compagne)");		// ()() = deux façons différentes d'appeler cette commande
			u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
			u.mdeb("§osara§§bintro¶tuto=0§§s§§d120§"); 		//Dès que le motif est lu, on efface ce que Sarah avait à dire
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite; il faudra attendre qu'un code spécial "§r§" soit atteint.
			//u.mfin();
			u.mtexte("§d120§\n\nOuin,§p800§ tant qu'à déjà être rendue§p140§...§p1600§µ"				//Maille #1
			"§d140§\n\n\nNon,§p300§ tu vas pas chocker ici.§p1130§§d110§ T'es meilleure que ça.§p1800§§µ"		//Maille #2
			"\n\n\nTu tires ton capuchon vers l'arrière en levant le menton,§p350§"		//Maille #3
			"\ny'est plus dans tes yeux maintenant§p1420§.µ"							//Maille #3 (encore)
			"\n\nUn grand respire,§p570§ tu soulèves tes yeux§p430§ à hauteur de Sara.§1170§ 'A te sourit,§p440§ puis marmonne qu'ses mains sont gelées.§p620§µ"		//Maille #4
			"§d90§ Tu lances ta jambes en avant dans un grand pas,§230§ par-dessus l'obstacle de béton pis tu mets tes mains sur la grille.§p1000§");			//Maille #5
			u.mordre("1-3-5;1-4-5;2-3-5;2-4-5");		//Par défaut, chaque enchaînement a une chance égale de se produire

				//Suite de "continuer" : faut demander explicitement de grimper (bout automatique qui l'explicite)
				u.nvauto(); u.acanal("je");
				//u.acond("intro¶tuto==3");			//Ça va pas être ça, mais j'attends avant de voir ça va prendre quelle forme, toutes ces variantes
				//u.adeb(""); 
				//u.afin();
				u.atexte("§d80§\nOuin,§p400§ tu sais pas trop comment prendre ça,§p510§ finalement.§p820§    Tu§p500§.§p420§..§p370§ tu guess qu'il faut que t'escalades?§p1500§§d130§ T'insères tes doigts à l'intérieur des fils losangés.§p1520§ Ben,§p410§ d'ins trous d'la clôture,§p300§ dans l'fond."
				"\nÇa devrait être simple.§p3600§ T'as juster à te hisser.§p4200§ Te monter§p400§,§p520§ avec un peu de force dans les bras§p300§.§p7000§");


							//Eurph, avant de continuer va falloir que j'mette au clair comment j'compte procéder avec les getbusy pis les multiples pt'its bouts de phrases en attendant que tu fasses queq'chose.
							
									//C'que j'pourrais facilement faire, c'est de mettre un code spécial qui change le status de getbusy dans la biblio (genre "menu¶getbusy", changé par §g0§ et §g1§)
										//Pis j'mettrais ça à chaque fin de phrase, là où le reste peut être overwrité sans perdre de sens. Pour éviter d'avoir genre 15 motifs séparés?
										
												//En fait, encore mieux:
														//J'me garde la possibilité, quand j'intègre un motif, de finalement pas le faire tout de suite.
														//J'le mets en réserve (j'note sa position).
														//Pis quand le code spécial §r§ (r pour réserve, mettons) arrive, j'fais simplement appliquer ce que j'avais mis en réserve.
															//Et pendant qu'il y a un motif en réserve, toutes les tentatives pour rentrer des commandes sont automatiquement refusées.
															//Pck "getbusy".
																//Fait qu'il faudrait peut-être changer le nom de ce "getbusy", pour l'appeler réserve, à la place.


								//Bon, c'est fait.
								//Maintenant, faudrait s'assurer d'avoir des motifs à appeler automatiquement pour quand on coupe un des canaux, pour par exemple refermer les guillemets.
										//Mieux:
													//Mettre un string à insérer par défaut après chaque override, et qui peut être modifié par un code spécal "§t[ce que ça va être]§". Genre "§t\"§".
													//En fait: "§t[nom du canal]¶[ce que ça va être]§"

			
				//Suite de "continuer" : faut demander explicitement de grimper
				u.nvmanu("grimper maintenant"); u.mcanal("je");
				//u.mcond("intro¶tuto==3");			//Ça va pas être ça, mais j'attends avant de voir ça va prendre quelle forme, toutes ces variantes
				u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&clôture|grillage|barrière|grille|toît)(grimper|monter|escalader|se hisser)");
				u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
				u.mdeb(""); 
				u.mreserve(); u.mover();
				//u.mfin();
				u.mtexte("§d80§ Tu places tes mains plus haut,§p220§ sécures tes doigts§p100§ pis tires§p200§§d100§ comme "
				"\n§d0§                     §d70§tes bottes glisses contre la clôture§p210§;§p330§ tu réussis à avoir une pogne pour tes pieds.§p1100§"
				"§d90§\n\nNice,§p140§ t'es d'ins airs.§p2300§");




			
			//Choix: "Franchir la ligne" ou autres formulation dramatiques/littérales (parce qu'il faut d'abord que t'enjambe la ligne de peinture jaune)
			u.nvmanu("franchir la ligne jaune"); u.mcanal("je");
			u.mcond("intro¶tuto==3");
			u.mcomm("(franchir|traverser|outrepasser|piétiner|fouler|marcher sur|passer|continuer outre&ligne|limite|trait|délimitation|frontière)");
			u.mdeb("§osara§§bintro¶tuto=0§§s§§d120§");
			//u.mfin();
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite; il faudra attendre qu'un code spécial "§r§" soit atteint.
			//u.mtexte();
						
			//Choix: "Grimper" ou autres
			u.nvmanu("grimper la clôture"); u.mcanal("je");
			u.mcond("intro¶tuto==3");
			u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&clôture|grillage|barrière|grille|toît[être capable d|pouvoir|être en posture de|se forcer à|se motiver à])");		// [] = on ne les veut pas!
			u.mdeb("§osara§§bintro¶tuto=0§§s§§d120§");
			//u.mfin();
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite; il faudra attendre qu'un code spécial "§r§" soit atteint.
			//u.mtexte();
						
			//Choix: "Surmonter sa peur" / "Rassembler son courage" / "Prendre son courage à deux mains", etc.
			u.nvmanu("surmonter sa peur"); u.mcanal("je");
			u.mcond("intro¶tuto==3");
			u.mcomm("(être capable d|pouvoir|être en posture de|se forcer à|se motiver à&grimper|monter|escalader|agripper|se hisser|franchir&clôture|grillage|barrière|grille|toît)");
			u.mcommexact("surmonter sa peur|prendre son courage à deux mains|se prendre en mains|rassembler son courage|être courageuse");
			u.mdeb("§osara§§bintro¶tuto=0§§s§§d120§");
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite; il faudra attendre qu'un code spécial "§r§" soit atteint.
			//u.mfin();
			//u.mtexte();
						
													
			
//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\
	
	//WORK IN PROGRESS
		//Modifier la bibliothèque pour suit my needs
		u.biblio.modif("intro","je",5);
	
	
	//Enclencher le premier motif (oui, j'fais ça manuellement pour garder l'uniformité dans mes enclenchements)
	//u.biblio.modif("intro","je",1);
	//Vérifier une toute première fois la disponibilité des motifs automatiques
	u.AutoInterpret();
	//Faire une boucle pour que les canaux s'expriment!
	u.jouer();				
	curspos(u.cons,0,13);			//Mettre le curseur dans un bel endroit à la fin


}		
