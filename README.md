ABCDerres
=========

codes for ensad's ABCDerres project

## To Do

Most codes have to be re-written in order to include the configuration file. 

## Startup

Set alsa volume to the maximum

	sudo amixer cset numid=1 100% > /dev/null

Script example :

	#!/bin/bash 

	# Here comes the startup script!
	sudo amixer cset numid=1 100% > /dev/null
	sudo python ~/ABCDerres/python/digitalToOSC.py &
	sudo ~/Dev/C/openFrameworks/examples/myapps/appABCderres_lettre/bin/appABCderre$



