ABCDerres
=========

codes for ensad's ABCDerres project


## Documentation de Julien

[https://dl.dropboxusercontent.com/s/fikeofub4bpokgp/index.html](https://dl.dropboxusercontent.com/s/fikeofub4bpokgp/index.html)

## Raspberry

| **Login** | **Mot de passe** |
| ------------ | ----------------------- |
| pi		| raspberry	     |

## Basculer le clavier en azerty

	sudo nano /etc/default/keyboard
	
changer la ligne :
	
	XKBLAYOUT="gb"
	
en :

	XKBLAYOUT="fr"
	
Le changement sera pris en compte après le redémarrage de la rapsberry.

## Connection ssh avec  interface graphique 

Ajouter l'option ```-X``` après ssh.

	ssh -X pi@hostIp
	
## installer pd-extended

	sudo nano /etc/apt/source.list
	
à la fin du fichier ajouter :

	deb http://apt.puredata.info/releases wheezy main
	
Sauvegarder en tapant ```ctrl+O```, taper ```enter``` puis fermer en tapant : ```ctrl+X```.

Après :

	sudo apt-get update
	sudo apt-get install pd-extended
	
## Obtenir ce git

	cd ~
	git clone https://github.com/alx-s/ABCDerres.git
	
## Lancer Pure Data extended

Avec interface graphique :

	pd-extended
	
Sans interface graphique :

	pd-extended -nogui nomDuPatch.pd
	
## Startup

### Login automatique

	sudo nano /etc/inittab

remplacer la ligne :
	
	1:2345:respawn:/sbin/getty 115200 tty1

par :

	1:2345:respawn:/bin/login -f pi tty1 </dev/tty1 >/dev/tty1 2>&1


## Startup Script

Création du script :
	
	cd ~
	nano startup.sh
	
Exemple de contenu :

	#!/bin/bash
	sudo amixer cset numid=1 100% > /dev/null			#Volume au maximum
	sudo python ~/ABCDerres/python/digitalToOSC.py &		# Lecture des gpio via python
	pd-extended -nogui ~/ABCDerres/pureData/xenophobie.pd		# lance pd sans interface graphique
	
## Faire exécuter le script au démarage

	nano ~/.bashrc
	
Tout à la fin ajouter :

	#Startup script
	
	bash ./startup.sh

	
	

## Plus d'infos sur les scripts de démarrage

[http://www.akeric.com/blog/?p=1976](http://www.akeric.com/blog/?p=1976)



