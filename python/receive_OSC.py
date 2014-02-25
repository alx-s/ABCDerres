
#! /usr/bin/python
 
import socket
import OSC
import time, threading
 
 
 
# tupple with ip the OSC server will listen to. 
receive_address = 'localhost', 1235
 
 
# OSC Server. there are three different types of server.
s = OSC.OSCServer(receive_address) # basic

  
     

# this registers a 'default' handler (for unmatched messages),
# an /'error' handler, an '/info' handler.
# And, if the client supports it, a '/subscribe' & '/unsubscribe' handler
s.addDefaultHandlers()
     
     
     
# define a message-handler function for the server to call.
def printing_handler(addr, tags, stuff, source):
    print "---"
    print "received from :  %s" % OSC.getUrlStr(source)
    print "with addr : %s" % addr
    print "typetags : %s" % tags
    print "data : %s" % stuff
    print "---"
     
s.addMsgHandler("/input6", printing_handler) # adding our function, first parameter corresponds to the OSC address you want to listen to
     
     
# just checking which handlers we have added
print "Registered Callback-functions are :"
for addr in s.getOSCAddressSpace():
    print addr
     
     
# Start OSCServer
print "\nStarting OSCServer. Use ctrl-C to quit."
st = threading.Thread( target = s.serve_forever )
st.start()
     
     
try :
    while 1 :
        time.sleep(5)
 
except KeyboardInterrupt :
    print "\nClosing OSCServer."
    s.close()
    print "Waiting for Server-thread to finish"
    st.join() ##!!!
    print "Done"
