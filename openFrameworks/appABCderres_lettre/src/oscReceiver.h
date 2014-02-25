//
//  oscReceiver.h
//  murmur
//
//  Created by Julien on 14/04/13.
//
//

#pragma once

#include "ofxOsc.h"

#define ABC_NB_INPUT	6

class oscReceiver  : public ofxOscReceiver
{
    public:
    	oscReceiver();
        void                update      ();


		int valeur[ABC_NB_INPUT];

    private:
        ofxOscMessage		m_oscMessage;
};

