#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{
	initInputOutput();
	readPlaylist("sounds/voix/", false);
}

//--------------------------------------------------------------

void testApp::update()
{
	// Nécessaire pour le moteur de sons d'OF
	ofSoundUpdate();
	updateInputOutput();

	int value0 = readInput(0);
	int value1 = readInput(1);
	int value2 = readInput(2);
	int value3 = readInput(3);

	// 4 paliers 0, 340, 680, 1024

	if (abs(value0)>20 && abs(value1)<20 && abs(value2)<20 && abs(value3)<20)
	{
		if (abs(value0 - 340)<20 && !listSounds[0].getIsPlaying())
		{
			// play touche 1
			ofLogNotice() << "touche 1";
			playSound(0);
		}
		else if (abs(value0 - 680)<20 && !listSounds[1].getIsPlaying())
		{
			// play touche 2
			ofLogNotice() << "touche 2";
			playSound(1);
		}
		else if (abs(value0 - 1023)<20 && !listSounds[2].getIsPlaying())
		{
			// play touche 3
			ofLogNotice() << "touche 3";
			playSound(2);
		}
	}
	if (abs(value1)>20 && abs(value0)<20 && abs(value2)<20 && abs(value3)<20)
	{
		if (abs(value1 - 340)<20 && !listSounds[3].getIsPlaying())
		{
			// play touche 4
			ofLogNotice() << "touche 4";
			playSound(3);
		}
		else if (abs(value1 - 680)<20 && !listSounds[4].getIsPlaying())
		{
			// play touche 5
			ofLogNotice() << "touche 5";
			playSound(4);
		}
		else if (abs(value1 - 1023)<20 && !listSounds[5].getIsPlaying())
		{
			// play touche 6
			ofLogNotice() << "touche 6";
			playSound(5);
		}
	}
	if (abs(value2)>20 && abs(value0)<20 && abs(value1)<20 && abs(value3)<20)
	{
		if (abs(value2 - 340)<20 && !listSounds[6].getIsPlaying())
		{
			// play touche 7
			ofLogNotice() << "touche 7";
			playSound(6);
		}
		else if (abs(value2 - 680)<20 && !listSounds[7].getIsPlaying())
		{
			// play touche 8
			ofLogNotice() << "touche 8";
			playSound(7);
		}
		else if (abs(value2 - 1023)<20 && !listSounds[8].getIsPlaying())
		{
			// play touche 9
			ofLogNotice() << "touche 9";
			playSound(8);
		}
	}
	if (abs(value3)>20 && abs(value0)<20 && abs(value1)<20 && abs(value2)<20)
	{
		if (abs(value3 - 340)<20 && !listSounds[9].getIsPlaying())
		{
			// play touche *
			ofLogNotice() << "touche *";
			playSound(9);
		}
		else if (abs(value3 - 680)<20 && !listSounds[10].getIsPlaying())
		{
			// play touche 0
			ofLogNotice() << "touche 0";
			playSound(10);
		}
		else if (abs(value3 - 1023)<20 && !listSounds[11].getIsPlaying())
		{
			// play touche #
			ofLogNotice() << "touche #";
			playSound(11);
		}
	}
	

	

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	playSoundRandom();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
}


//--------------------------------------------------------------
void testApp::readPlaylist(string folder, bool loop)
{
	// Variable qui contient l'index du morceau qui est en train d'tre jouŽ
	// -1 = aucun
	currentSound = -1;

	// Listing de tous les fichiers dans le dossier data/sounds
	dir.listDir(folder);
	dir.sort();
	
	// Pour chaque fichier
	for(int i = 0; i < (int)dir.size(); i++)
	{
		// RŽcupre le chemin
		string pathSound = dir.getPath(i);
		
		// CrŽation d'une instance de type SoundPlayer
		ofSoundPlayer soundPlayer;
		
		// Si le chargement s'est correctement effectuŽ
		if (soundPlayer.loadSound(pathSound))
		{
			// En mode boucle pour le son si on le joue
			soundPlayer.setLoop(loop);
			
			// On l'ajoute dans notre liste
			listSounds.push_back(soundPlayer);

			// log sur la console
			ofLogNotice() << "loaded " << pathSound;
		}
	}

}

//--------------------------------------------------------------
void testApp::playSound(int which)
{
if (listSounds.size()==0){
ofLogWarning() << "[playSound("<< which <<")] la playlist est vide...";
return;
}
if (which >= listSounds.size()){
ofLogWarning() << "[playSound("<< which <<")] l'index n'est pas valide...";
return;
}

// Si on est en train de jouer un son
if (currentSound>=0)
{
// On le stoppe
listSounds[currentSound].stop();
}

currentSound = which;
listSounds[currentSound].play();
}

//--------------------------------------------------------------
void testApp::playSoundRandom()
{
	if (listSounds.size()==0){
		ofLogWarning() << "[playSoundRandom] la playlist est vide...";
		return;
	}

	// Si on est en train de jouer un son
	if (currentSound>=0)
	{
		// On le stoppe
		listSounds[currentSound].stop();
	}
	
	// Petite boucle pour ne pas jouer le mme son deux fois d'affilŽe
	int newCurrentSound = -1;
	do
	{
		newCurrentSound = (int)ofRandom(listSounds.size());
		if (newCurrentSound>=listSounds.size())
			newCurrentSound = listSounds.size()-1;
	} while (newCurrentSound == currentSound);

	currentSound = newCurrentSound;
	ofLogNotice() << "playing listSounds[" << currentSound << "]";
	
	// On joue ce son
	listSounds[currentSound].play();
}

//--------------------------------------------------------------
void testApp::initInputOutput()
{
    m_oscReceiver.setup(1234);
	m_oscSender.setup("127.0.0.1", 1235);
}

//--------------------------------------------------------------
void testApp::updateInputOutput()
{
	m_oscReceiver.update();
}

//--------------------------------------------------------------
int testApp::readInput(int which)
{
	return m_oscReceiver.valeur[which];
}

//--------------------------------------------------------------
void testApp::writeOutput(string which, int value)
{
	ofxOscMessage m;
	m.setAddress(which.c_str());
	m.addIntArg(value);
	m_oscSender.sendMessage(m);
}


