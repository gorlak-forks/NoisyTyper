#include "testApp.h"

CFMachPortRef           eventTap;  
CFRunLoopSourceRef      runLoopSource; 
	
ofSoundPlayer soundSpace;
vector <ofSoundPlayer> soundKey;
ofSoundPlayer soundReturn;
ofSoundPlayer scrollUp;
ofSoundPlayer scrollDn;
ofSoundPlayer backspace;
vector <int> lastSix;

//--------------------------------------------------------------
CGEventRef recordKeysCallback(CGEventTapProxy   proxy, 
                                                          CGEventType           type,  
                                                          CGEventRef            event, 
                                                          void*                         nothing){
        
		if (type == kCGEventKeyDown){
				 
			int key = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
			
			//cout << " key is " <<  << endl; 
			//printf("%i, ", key);
			
			if( key == 125 ){
				scrollDn.play();
				scrollDn.setPan(-0.7);
				scrollDn.setSpeed( ofRandom(0.85, 1.0 ));
			}
			else if( key == 126 ){
				scrollUp.play();
				scrollUp.setPan(-0.7);
				scrollUp.setSpeed( ofRandom(0.85, 1.0 ));
			}
			else if( key == 51 ){
				backspace.setPan(0.75);
				backspace.play();
				backspace.setSpeed(ofRandom(0.97, 1.03));
			}
			else if( key == 49 ){
				soundSpace.setSpeed(ofRandom(0.95, 1.05));
				soundSpace.play();
				soundSpace.setVolume( ofRandom(0.8, 1.1) );			
			}
			else if( key == 36 ){
				soundReturn.setSpeed(ofRandom(0.99, 1.01));
				soundReturn.play();
				soundReturn.setVolume( ofRandom(0.7, 1.1) );
				soundReturn.setPan(0.3);
			}
			else{
				int which = ofRandom(0, ((float)soundKey.size()) * 0.99);
				soundKey[which].setSpeed( ofRandom(0.98, 1.02) );
				soundKey[which].play();
				soundKey[which].setVolume( ofRandom(0.7, 1.1) );
				
				if( key == 12 || key == 13 || key == 0 || key == 1 || key == 6 || key == 7 ){
					soundKey[which].setPan( -0.65 );					
				}else if( key == 35 || key == 37 || key == 43 || key == 31 || key == 40 || key == 46 ){
					soundKey[which].setPan( 0.65 );					
				}
				else{
					soundKey[which].setPan( ofRandom(-0.3, 0.3) );			
				}
				
				lastSix.push_back( key );
				if( lastSix.size() > 6 ){
					lastSix.erase(lastSix.begin(), lastSix.begin()+1);
				}
				if( lastSix.size() == 6 ){
					if( lastSix[0] == 12 && lastSix[1] == 0 && lastSix[2] == 6 && lastSix[3] == 18 && lastSix[4] == 19 && lastSix[5] == 20 ){
						ofExit(0);
					} 
				}	
			}
		
		}
	
		return event;	

}


//--------------------------------------------------------------
void testApp::setup(){


		ofSetDataPathRoot("../Resources/");

		

	
	        // create event listener
        eventTap = CGEventTapCreate(kCGHIDEventTap, 
					kCGHeadInsertEventTap, 
					0, 
					kCGEventMaskForAllEvents, 
					recordKeysCallback,   // <-- this is the function called
					NULL);
					
																        // wrap event listener to loopable form
        runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, 
                                                                                                  eventTap, 
                                                                                                  0);
      // add wrapped listener to loop
        CFRunLoopAddSource(CFRunLoopGetCurrent(), 
                                           runLoopSource, 
                                           kCFRunLoopCommonModes);
        

		ProcessSerialNumber psn = { 0, kCurrentProcess }; 
		OSErr err = SetFrontProcess( & psn ); 
		ofSystemAlertDialog("Noisy Typer runs in the background.\nTo kill it type: qaz123\n\nFor it to work: 'Enable Access for Assistive Devices'\nmust be enabled in Universal Access, System Prefs\n\nMade by Theo Watson, with openFrameworks 0071");
		
		//cout << "1: adding listener " << endl; 

		soundSpace.loadSound("space.mp3");
		soundReturn.loadSound("return-new.mp3");		
		soundKey.push_back( ofSoundPlayer() );
		soundKey.push_back( ofSoundPlayer() );
		soundKey.push_back( ofSoundPlayer() );
		soundKey.push_back( ofSoundPlayer() );
		soundKey.push_back( ofSoundPlayer() );

		soundKey[0].loadSound("key-new-01.mp3");
		soundKey[1].loadSound("key-new-02.mp3");
		soundKey[2].loadSound("key-new-03.mp3");
		soundKey[3].loadSound("key-new-04.mp3");
		soundKey[4].loadSound("key-new-05.mp3");
		
		scrollUp.loadSound("scrollUp.mp3");
		scrollDn.loadSound("scrollDown.mp3");
		backspace.loadSound("backspace.mp3");

		scrollUp.setMultiPlay(true);
		scrollDn.setMultiPlay(true);
		backspace.setMultiPlay(true);
	
		soundSpace.setMultiPlay(true);
		soundReturn.setMultiPlay(true);
		
		for(int i = 0; i < soundKey.size(); i++){
			soundKey[i].setMultiPlay(true);
		}		

        // enable event tab
        CGEventTapEnable(eventTap, 
                                         true);
        
        // run event tab
        CFRunLoopRun();

}


//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}