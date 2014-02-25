#pragma once

#include "ofMain.h"
#include "oscReceiver.h"
#include "ofxXmlSettings.h"


class testApp : public ofBaseApp
{

	public:
	
		// Démarrage de l'application
		void setup();
		// L'équivalent de loop sur Arduino
		void update();
		// Appelée lorsqu'on quitte l'application
		void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
	
		// > Joue un son de la liste (en passant son numéro dans la liste)
		void playSound(int which);
		// > joue un son de la liste au hasard
		void playSoundRandom();

		// > Lecture Entrée (de 0 à 5)
		int readInput(int which);
		// > Écriture sur la sortie ("/output0" ou "/output1")
		void writeOutput(string which, int value);

		// > récupérer une valeur en fonction de son nom & type, avec une valeur par défaut (optionnelle)
		int getConfigurationValue(string varName, int defaultVal=0);
		float getConfigurationValue(string varName, float defaultVal=0.0f);
		string getConfigurationValue(string varName, string defaultVal="");

	private:
		// Configuration par fichier
		// http://www.openframeworks.cc/documentation/ofxXmlSettings/ofxXmlSettings.html
		ofxXmlSettings settings;


		// http://www.openframeworks.cc/documentation/utils/ofDirectory.html
		ofDirectory dir;

 		// http://www.openframeworks.cc/documentation/sound/ofSoundPlayer.html
 		vector<ofSoundPlayer> listSounds;
		int currentSound;

        // Communications OSC / GPIO
        oscReceiver     m_oscReceiver;
        ofxOscSender	m_oscSender;

		// Sound
		// > Charge la liste des morceaux
		void readPlaylist(string folderName, bool loop=true);
	
		// Configuration de variables
		// > charger la configuration (à faire dans la fonction setup)
		bool loadConfiguration(string fileName="configuration.xml");
		bool isConfigurationLoaded;

		// Input / output
		// > Initialise la connexion avec le GPIO de la Rapsberry
		void initInputOutput();
		// > Mets à jours les E/S GPIO
		void updateInputOutput();

};
