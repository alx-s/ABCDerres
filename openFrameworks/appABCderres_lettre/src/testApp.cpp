#include "testApp.h"


// Variables
// > Exemple de variable qui peut-être lue depuis le fichier de configuration
int exempleVar = 0;

float soundVolume = 0.0f;
float soundVolumeTarget = 0.0f;

//--------------------------------------------------------------
void testApp::setup()
{
	
	initInputOutput();

	readPlaylist("sounds/lettre/", false);
	// Jouer un son au hasard	
	//ofSleepMillis(5000);
	playSound(0);
	listSounds[0].setVolume(soundVolume);
}

//--------------------------------------------------------------
void testApp::update()
{
	// Nécessaire pour le moteur de sons d'Openframeworks
	ofSoundUpdate();

	// Nécessaire pour la mise à jour du GPIO
	updateInputOutput();

	//
	if (!listSounds[0].getIsPlaying()){
		playSound(0);
	}

	// Exemple de lecture depuis une entrée
	// Puis écriture sur la sortir "/output0"
	int value = readInput(5);
	if (value>0)
	{
		soundVolumeTarget = 0.0f;
		soundVolume += (soundVolumeTarget-soundVolume)*0.2;
	}
	else
	{
		ofLogNotice() << "touch detected";
		soundVolumeTarget = 1.0f;
		soundVolume += (soundVolumeTarget-soundVolume)*0.7;
	}

	listSounds[0].setVolume(soundVolume);
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
	// Variable qui contient l'index du morceau qui est en train d'tre joué
	// -1 = aucun
	currentSound = -1;

	// Listing de tous les fichiers dans le dossier data/sounds
	dir.listDir(folder);
	
	// Pour chaque fichier
	for(int i = 0; i < (int)dir.size(); i++)
	{
		// Récupre le chemin
		string pathSound = dir.getPath(i);
		
		// Création d'une instance de type SoundPlayer
		ofSoundPlayer soundPlayer;
		
		// Si le chargement s'est correctement effectué
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
	
	// Petite boucle pour ne pas jouer le même son deux fois d'affilée
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
	if (which >= ABC_NB_INPUT)
	{
		ofLogWarning() << "[readInput("<< which <<")] attention les valeurs possibles sont entre 0 et " << (ABC_NB_INPUT-1);
		return 0;
	}

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

//--------------------------------------------------------------
bool testApp::loadConfiguration(string fileName)
{
	// isConfigurationLoaded = settings.loadFile(fileName); // la valeur retournée par cette fonction n'est pas fiable (BUG je pense)
	isConfigurationLoaded = true;
	settings.loadFile(fileName);
	if (!isConfigurationLoaded)
	{
		ofLogWarning() << "[loadConfiguration] erreur lors du chargement du fichier " << fileName;
	}
	return isConfigurationLoaded;
}


//--------------------------------------------------------------
int testApp::getConfigurationValue(string varName, int defaultVal)
{
	if (isConfigurationLoaded)
		return settings.getValue("configuration:"+varName, defaultVal);
	else{
		ofLogWarning() << "[getConfigurationValue("<< varName <<")] retour de la valeur par défaut ";
		return defaultVal;
	}
}


//--------------------------------------------------------------
float testApp::getConfigurationValue(string varName, float defaultVal)
{
	if (isConfigurationLoaded)
		return settings.getValue("configuration:"+varName, defaultVal);
	else{
		ofLogWarning() << "[getConfigurationValue("<< varName <<")] retour de la valeur par défaut ";
		return defaultVal;
	}
}

//--------------------------------------------------------------
string testApp::getConfigurationValue(string varName, string defaultVal)
{
	if (isConfigurationLoaded)
		return settings.getValue("configuration:"+varName, defaultVal);
	else{
		ofLogWarning() << "[getConfigurationValue("<< varName <<")] retour de la valeur par défaut ";
		return defaultVal;
	}
}


