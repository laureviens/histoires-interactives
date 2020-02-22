/*
			///||================================---2020/01/18---================================||\\\
\\\||================================---Tutoriel / Démo du potentiel interactif / narratif---================================||///
*/


# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/cadre_fonctionnel_global.cpp"


//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\

int main(void) {

	//Changement de taille et de place de la console                     //Doit être défini à l'intérieur du main() pour fonctionner!
	//x, y, width, height,
	fen base(600,30,500,500);                                           //Crée également l'objet dans lequel ces paramètres sont définis       
	memoire mem(base.limtxtx);

	//Créer l'objet où tout est initié
	univers monde;

//-----------------------------------------------------------------|      Bibliothèque       |--------------------------------------------------------------------------------\\
	
	nvrayon(monde,"intro");
		nvlivre(monde,"desuet");	
		nvlivre(monde,"jeprem");
		nvlivre(monde,"jedeux");
		nvlivre(monde,"saraprem");
		nvlivre(monde,"saradeux");
		nvlivre(monde,"jetrois");
		nvlivre(monde,"saratrois");
		nvlivre(monde,"jequatre");
		nvlivre(monde,"saraquatre");
		nvlivre(monde,"jecinq");
		
			
			
//-----------------------------------------------------------------|          Début          |--------------------------------------------------------------------------------\\

	//Créer un canal
	nvcanal(monde,"je"); canaldelai(monde,80); 
	nvcanal(monde,"sara"); canaldelai(monde,130); canalalinea(monde,6);
		
	//Débuter un chapitre
	nvchapt(monde);
		ccond(monde,"!intro¶desuet");        //Rendre le premier chapitre accessible seulement quand c'est l'intro 

			//Juste le début
			nvauto(monde); acanal(monde,"je");	                                    	
			acond(monde,"intro¶jeprem");	
			adeb(monde,"§bintro¶jeprem=0§");
			afin(monde,"§bintro¶saraprem=1§");
			aover(monde,0);						//N'override pas le canal à son début
			atexte(monde,"T'as froid aux joues.§p1400§"
			"\n§d0§                     §d80§Pis aux cuisses.");				

			//La réponse de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro¶saraprem");	
			adeb(monde,"§bintro¶saraprem=0§");
			afin(monde,"§bintro¶jedeux=1§");
			atexte(monde,"§p1800§\"Come on,§p1100§"
			"\n§d0§          §d130§on est presqu'arrivées!\"");

			//La suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro¶jedeux");	
			adeb(monde,"§bintro¶jedeux=0§§s§");
			afin(monde,"§bintro¶saradeux=1§");
			atexte(monde,"§p400§\n\n         T'accélères le pas,§p600§ moins pour la rejoindre§p100§ que pour réchauffer tes jambes.§p1200§§d110§ Le vent,§p500§ criss.§p700§ Le vent.§p1600§"
			"\n§d90§Tu lèves les yeux§p100§ juste à la limite de ton capuchon§p300§ pis Sara est quand même loin en avant.§p1400§§d80§ Tu te presses un peu plus.§p2800§"
			"\n\nTraverses une rue,§p400§ t'es au coin de la cathédrale§p300§ pis le vent charge de plus belle depuis ta droite.§p2400§ Caliss.§p3000§§d90§ Sara est déjà rendue plus bas,§p500§ a'longe la grosse chapelle.§p2300§"
			"\n§d0§                       §d80§Tu descends au jogging§p120§, §p400§"
			"\n§d0§                                                §d80§rejoindre au plus vite l'énorme pare-vent de pierre.§p1800§"
			"\nTa jupe virevolte sur tes genoux,§p200§ expose tes cuisses aux rafales;§p2300§ Pas l'meilleur choix de vêtements.§p4300§"
			"\n\n     La cathédrale coupe le vent§p150§ pour vrai.§3100§ "
			"\n\n\nSara t'as un peu attendue et te sourit avec son trop d'excitation.§p2200§");

			//La réponse de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro¶saradeux");	
			adeb(monde,"§bintro¶saradeux=0§§s§");
			afin(monde,"§bintro¶jetrois=1§");
			atexte(monde,"§p130§§d110§\n\"J'te jure,§p260§ c'est l'meilleur spot au monde,§p240§ sur les toits du centro!\"");			

			//La suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro¶jetrois");	
			adeb(monde,"§bintro¶jetrois=0§§s§");
			afin(monde,"§bintro¶saratrois=1§");
			atexte(monde,"§p3100§Tu peux pas empêcher tes commissures engourdies de remonter un peu.§p2600§"
			"\n\n§d90§Encore quelques pas ensemble et vous êtes à l'arrière d'la maison de Dieu§p140§ pis l'vent reprend.§p560§§100§ Vraiment une belle soirée pour être sur l'top d'une colline.§2600§"
			"\n\n§d90§Sara te traîne encore plus derrière l'église,§p220§ dans une allée séparée de la rue par un p'tit muret.§p1800§ À ta gauche,§p160§ tu peux voir le frimas sur les toits plats des buildings adjacents,§p240§ pis les lumières de la ville,§p130§ de l'autre côté d'la rivière.§p2000§ Vous êtes pas mal haut,§p180§ finalement.§p3000§"
			"\nTu continues et un long bâtiment de briques s'érige entre le bord de la falaise et vous,§p110§ coupe le paysage.§p900§ Ça donne moins le vertige.§p2500§"

			"\n§d0§               §d90§Tu te demandes si c'est illégal de grimper sur les toits des bâtiments la nuit.§p1200§"   //Phrase nouvelle; essai; est-ce que c'est bon?
			
			"§d100§\n\nAu bout d'la bâtisse,§p300§ votre allée remonte vers un léger promontoir asphalté.§p1100§"
			"\nUltime place de parking avant le précipice.§p2300§"
			"\nBordé de la fin du bâtiment de briques à sa gauche,§p200§ le stationnement a mérité une ligne jaune comme limite à droite,§p500§ même si la chute abrupte du relief de beaucoup d'mètres offre aussi une délimitation pas mal claire.§p2000§ Des butoirs de béton ont été installés le long de la peinture jaune,§p130§ à droite et au devant de l'emplacement,§p300§ pour plus de sécurité.§p2600§ À l'avant, c'est bouclé par une clôture haute de 3 ou 4 mètres,§p230§ qui empêche fermement l'accès aux toits adjacents,§p400§ barbelés et tout.§p2400§"
			"§d85§\nClôture sur laquelle les épaules de Sara sont accotées,§p140§ ses deux pieds repoussés contre le bump en béton.§p1500§ Les bras croisés,§210§ le dos trop droit;§p400§"
			"\n   Un sourire qui sussure"
			"\n§d0§                          §d100§\"C'est par là qu'on passe\".§p3000§");

			//L'explication de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro¶saratrois");	
			adeb(monde,"§bintro¶saratrois=0§§s§");
			afin(monde,"");
			atexte(monde,"§p1600§§d100§\n\"Fait qu'on a juste à monter la clôture,§bintro¶jequatre=1§§p300§ là,§p2900§"
			"\npis après on va vraiment jusqu'au coin,§p400§ jusqu'à l'autre clôture bizarre,§p200§ la genre de grille qui pend.§p1200§ Pis elle,§p90§ on la monte§p270§ - tu vas voir c'est pas tough - §p5200§ pis 'y reste juste à r'descendre pis on est sur les toîts.\"");
			
			//Encore l'explication de Sara, mais en gestes (narration)	/ puis la suite
			nvauto(monde); acanal(monde,"je");		
			acond(monde,"intro¶jequatre");	
			adeb(monde,"§bintro¶jequatre=0§§s§");
			afin(monde,"");
			atexte(monde,"§d80§\n\nElle se redresse et pose la main à plat sur le grillage en losanges§p540§ avant de pointer l'extrémité en haut à droite,§p420§ avance d'un pas en bougeant de haut en bas avec ses deux bras,§p2800§ te regarde dans les yeux,§p1200§ fait un tour sur elle-même en crispant les dents avec ses doigts solidement accrochés à son imagination,§p100§§d90§ et fait semblant d'atterir sur ses deux pieds,§d110§ finalement.§p4500§"
			"§d100§\n\n\nElle te sourit,§300§ l'air fière de son explication.§p2000§"
			"§d110§\nTu clignes des paupières§p800§ une fois.§p2900§"
			"§d100§\n\n\nLa tête te soupire§p110§ et t'avances pour constater le chemin toi-même.§p2100§"
			"\n\nAu devant, la grande barrière de grillage en losanges§p90§ a son top en barbelés,§p390§ dressés en angle contre votre direction.§p900§ §d120§Fait que définitivement pas par là.§p2300§"
			"§d150§\n\nÀ droite,§p500§§d130§ par contre,§p430§§d110§ le grillage finit juste avant la falaise,§p290§ et une espèce de grille à gros barreaux verticaux prolonge la clôture au-dessus du précipice,§p600§§d100§ probablement pour nous empêcher de juste tourner le coin.§p1800§"
			"§d120§\n\nMais la grille,§p180§ qui fait juste chiller au-ds'us du vide,§p440§ elle,§p580§ elle a pas de barbelés.§p400§.§p320§.§p3200§"
			"§d160§ Fait que par là.§p3800§"
			"§d90§\n\n\n\nTes yeux se ferment brièvement,§p430§ une seconde fois.§p1900§"
			"§d300§\n\n\n§d0§                  §d400§DANGEREUX.§p2200§"
			"§d100§\n\n\nT'ouvres l'oeil sur tes pieds,§p300§ au sol,§p430§§d120§ l'autre oeil,§p520§"
			"\n§d0§                §d100§t'es debout sur l'asphalte,§p460§ les orteils à peine sur la ligne jaune du devant du parking,§320§ juste avant le bump de béton.§p1300§"
			"§d90§\nSara est rendue l'autre bord du grillage§p130§,§p220§ déjà passée par-dessus la grille,§p180§ agrippée§p110§ légère encore dans le haut de la barrière,§p330§ accrochée.§p2600§§bintro¶saraquatre=1§§p2600§"
			"§d400§§c§Non.§p1800§"
			"§d500§§s§\n\n\n\n\n\n§d180§Non.§p600§§d120§ Non j'fais pas ça.§p700§ §d600§Non.§p1700§");

			//L'explication de Sara
			nvauto(monde); acanal(monde,"sara");		
			acond(monde,"intro¶saraquatre");	
			adeb(monde,"§bintro¶saraquatre=0§§s§");
			afin(monde,"§bintro¶jecinq=1§");
			atexte(monde,"§d80§\n\"Tu vois c'est vraiment simple,§p90§ c'est juste la partie où tu changes de bord qui est un peu tricky,§p100§ mais sinon y'a vraiment pas à s'inquiéter,§p70§ tu vas voir ça va full bien s'passer,§p110§ pis j'suis là si y'a d'quoi§p100§ -\"§p1600§"
			"§s§\n\n\"Ça va§p230§  ?\"");
			

					//Commentaire de Cybèle:
							//Ça serait le fun d'avoir de l'info ("plus tôt") sur c'qu'on fait là,
							//pour pouvoir anticiper plus la suite.
								//Genre savoir un peu le but de tout ça.
									//Donc genre mettre dans les premières lignes de dialogue de Sara un p'tit "Tu vas voir, c'est super le fun sur les toits d'la main"
											
									//Pis commentaire personnel: Le rythme, quand ça défile par lui-même, est quand même lent.
										//Genre c'est un bon 5 minutes se rendre jusqu'au premier choix (traverser la ligne jaune ou pas).
										//Fait que oui, ça devient super pertinent de mettre un peu de "why" là-dedans.
										
							//C'que j'ai changé en réponse:
									//J'ai mis en commentaire deux sections pas utiles, limite redondantes, pour accélérer le rythme.
									//J'ai changé "J'te jure,§p260§ ça vaut vraiment la peine!"
										//par "J'te jure,§p260§ c'est l'meilleur spot au monde,§p240§ sur les toits du centro!"
											
								//J'devrais peut-être aussi ajouter une ptite phrase narrative quand tu marches encore dans les rues (au début-début)			
											
													//à la limite, j'peux également scrapper mon p'tit bout de confusion où tout le monde écrit en même temps, parce qu'il ne sert pas tant à grand-chose...
					
									//Update: J'ai mis une phrase quand elles sont déjà à l'arrière de la cathédrale, et ça fait un beau rappel, en plus de donner le caractère de la personnage principale		
													
					//Commentaire de moi:
							//Le rythme est pas si pire, et j'pense que le but est assez énoncé (selon mon humble avis).
							//J'aime également le bout où tout le monde parle en même temps, j'trouve que ça aide la visualisation sans être lourd.
							//Par contre, le bout que j'trouve maintenant superflus / dans les jambes, c'est la description de l"ultime place de parking". 
								//Idéalement, faudrait la réécrire pour qu'il y ait les mêmes informations, mais dans une forme moins lourde. Moins une pause.
									//Plus comme l'observation du chemin?
											//Principe expérimental: être en relation avec l'environnement (y marcher, l'observer activement), plutôt que le décrire (dans le but de se l'imaginer bien).
						
											
		//La suite, pour introduire les actions à écrire:
			//Ish, j'ai l'impression qu'il me faudrait vraiment des notes écrites en mode "chatt" (qui s'écrivent, et qui disparaîssent comme si effacées par backspace),
			//qui pausent tous les autres canaux, et qui sont genre en blanc, pour dire "Maintenant, c'est à toi de jouer / écrire les actions que tu désires."
			//Pis dès que ça s'efface, (idéalment, y'a un peu de chevauchement) les autres canaux reprennent vie.
			
			//Ça serait vraiment important de définir si oui ou non j'ai accès à cet outil, parce que le niveau d'encouragement/aide que je vais donner via les canaux normaux
			//en dépend vraiment.
									//Fait que mettons que j'prends une décision: oui, j'vais utiliser + développer cet outil.
												//(doit s'afficher après la mémoire, pour effacer certaines lignes, et être positionné).	
												
																	
//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\
	
	//WORK IN PROGRESS
		//Modifier la bibliothèque pour suit my needs
		monde.biblio.modif("intro","saratrois",1);
	
	
	
	//Enclencher le premier motif (oui, j'fais ça manuellement pour garder l'uniformité dans mes enclenchements)
	//monde.biblio.modif("intro","jeprem",1);
	//Vérifier une toute première fois la disponibilité des motifs automatiques
	AutoInterpret(monde.canaux, monde.biblio, monde.histoire, base, monde.inp, mem);
	//Faire une boucle pour que les canaux s'expriment!
	jouer(monde,base,mem);				
	curspos(0,13);			//Mettre le curseur dans un bel endroit à la fin


}		
