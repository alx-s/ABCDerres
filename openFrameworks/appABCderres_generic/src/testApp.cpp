#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{
	initInputOutput();
	readPlaylist("sounds/poubelle/");
	playSoundRandom();
}

//--------------------------------------------------------------

void testApp::update()
{
	// Nécessaire pour le moteur de sons d'OF
	ofSoundUpdate();
	updateInputOutput();

	int value = readInput(0);
	float nvalue = (1023.0f-(float)value)/(1023.0f - 230.0f);
	nvalue = max(0.0f, min(1.0f,nvalue));
	writeOutput("/output0", nvalue <= 0.5f ? 0 : 1);

	if (currentSound>=0){
		listSounds[currentSound].setSpeed( ofMap(nvalue,0.0f,1.0f, 0.3f,2.0f) );
		listSounds[currentSound].setVolume( 1.0f);
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


