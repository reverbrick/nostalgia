  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <signal.h>
#include "RtMidi.h"

#define SUNVOX_MAIN
#include "sunvox.h"

int keep_running = 1;
void int_handler( int param ) 
{
    keep_running = 0;
}

int gNote = 0;
int gVelocity = 0;
int poly[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void midicallback( double deltatime, std::vector< unsigned char > *message, void *userData ){
	int gChannel = -1;
	/*
	unsigned int nBytes = message->size();
	for ( unsigned int i=0; i<nBytes; i++ )
		std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
	if ( nBytes > 0 )
		std::cout << "stamp = " << deltatime << std::endl;
	*/
	if((int)message->at(2)!=0){
        	for(int x=0; x<16; x++){
                	if(poly[x]==0){
				poly[x]=(int)message->at(1);
				gChannel=x;
				break;
			}
	        }

		//sv_send_event( 0, (int)message->at(0)-144, (int)message->at(1), (int)message->at(2), 2, 0, 0 );
                sv_send_event( 0, gChannel, (int)message->at(1), (int)message->at(2), 2, 0, 0 );
	}
	else{
        	for(int x=0; x<16; x++){
                	if(poly[x]==(int)message->at(1)){
				poly[x]=0;
				gChannel=x;
				break;
			}			
        	}

		//sv_send_event( 0, (int)message->at(0)-144, NOTECMD_NOTE_OFF, 128, 2, 0, 0 );
                sv_send_event( 0, gChannel, NOTECMD_NOTE_OFF, 128, 2, 0, 0 );
	}
	//std::cout << poly[0] << poly[1] << poly[2] << poly[3] << poly[4] << poly[5] << poly[6] << poly[7] << poly[8] << poly[9] << poly[10] << poly[11] << poly[12] << poly[13] << poly[14] << poly[15] << std::endl;
}

int main(int argc, char** argv)
{
    printf( "Nostalgia ROMpler by PlaybleElectronics\n" );
    if(argc<2)
    {
	printf( "Usage:\n" );
	printf( "./nostalgia <module>[Sampler] <filename>\n" );
    }
    else
    {
	    signal( SIGINT, int_handler );
	    
	    if( sv_load_dll() )
		return 1;
	    
	    int ver = sv_init( 0, 44100, 2, 0 );
	    if( ver >= 0 )
	    {
		int major = ( ver >> 16 ) & 255;
		int minor1 = ( ver >> 8 ) & 255;
		int minor2 = ( ver ) & 255;
		printf( "SunVox lib version: %d.%d.%d\n", major, minor1, minor2 );
		
		sv_open_slot( 0 );

		sv_lock_slot( 0 );
		int mod_num = sv_load_module( 0, argv[2], 0, 0, 0 );
		sv_unlock_slot( 0 );
		if( mod_num >= 0 )
		{
		    //Connect the new module to the Main Output:
		    sv_lock_slot( 0 );
		    sv_connect_module( 0, mod_num, 0 );
		    sv_unlock_slot( 0 );
		}
		else
		{
		    printf( "Can't create the new module\n" );
		}

		RtMidiIn *midiin = new RtMidiIn();
		// Check available ports.
		unsigned int nPorts = midiin->getPortCount();
		if ( nPorts == 0 ) {
			std::cout << "No ports available!\n";
			goto cleanup;
		}
		for(int i=1;i<nPorts;i++)
			midiin->openPort( i );
		midiin->setCallback( &midicallback );
		midiin->ignoreTypes( false, false, false ); // Don't ignore sysex, timing, or active sensing messages.

		while( keep_running )
		{
		    sleep( 1 );
		}
		
		cleanup:
			sv_stop( 0 );	
			sv_close_slot( 0 );
			sv_deinit();
	    }
	    else 
	    {
		printf( "sv_init() error %d\n", ver );
	    }
	    
	    sv_unload_dll();
    }
    return 0;
}
