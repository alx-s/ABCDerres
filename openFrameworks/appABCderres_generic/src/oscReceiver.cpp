//
//  oscReceiver.cpp
//  murmur
//
//  Created by Julien on 14/04/13.
//
//

#include "oscReceiver.h"

oscReceiver::oscReceiver()
{
    for (int i=0;i<ABC_NB_INPUT;i++)
        valeur[i]=0;    
}

//--------------------------------------------------------------
void oscReceiver::update()
{
    
    if (hasWaitingMessages())
    {
		while(getNextMessage(&m_oscMessage))
		{
            if (m_oscMessage.getAddress() == "input0")
            {
                valeur[0]  = m_oscMessage.getArgAsInt32(0);
            }
            else
            if (m_oscMessage.getAddress() == "input1")
            {
                valeur[1]  = m_oscMessage.getArgAsInt32(0);
            }
            else
            if (m_oscMessage.getAddress() == "input2")
            {
                valeur[2]  = m_oscMessage.getArgAsInt32(0);
            }
            else
            if (m_oscMessage.getAddress() == "input3")
            {
                valeur[3]  = m_oscMessage.getArgAsInt32(0);
            }
            else
            if (m_oscMessage.getAddress() == "input4")
            {
                valeur[4]  = m_oscMessage.getArgAsInt32(0);
            }
            else
            if (m_oscMessage.getAddress() == "input5")
            {
                valeur[5]  = m_oscMessage.getArgAsInt32(0);
            }
        }
    }
}
