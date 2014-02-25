#pragma once

#include "ofMain.h"
#include "oscReceiver.h"


class testApp : public ofBaseApp
{

	public:
	
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
	
		// Sound
		// > Charge la liste des morceaux
		void readPlaylist(string folder, bool loop=true);
		// > Joue un son de la liste
		void playSound(int which);
		// > joue un son de la liste au hasard
		void playSoundRandom();

	
		// Input / output
		// > Initialise la connexion avec le GPIO de la Rapsberry
		void initInputOutput();
		// > Mets à jours les E/S GPIO
		void updateInputOutput();
		// > Lecture Entrée (de 0 à 5)
		int readInput(int which);
		// > Écriture sur la sortie (/input0 ou /input1)
		void writeOutput(string which, int value);


	private:

		// http://www.openframeworks.cc/documentation/utils/ofDirectory.html
		ofDirectory dir;

 		// http://www.openframeworks.cc/documentation/sound/ofSoundPlayer.html
 		vector<ofSoundPlayer> listSounds;
		int currentSound;

        // OSC
        oscReceiver     m_oscReceiver;
        ofxOscSender	m_oscSender;
};
