#include <ncurses.h>
#include "letteroid.h"
#include "blinkingletteroid.h"
#include "letteroidfield.h"
/// include your derived classes here
//----------------------------------------START OF ADDED CODE------------------------------------------------//

#include <cstdlib>//used for rand()
#include <ctime>//used to seed rand with time
#include <string>
#include <vector>

class LetteroidVR : public Letteroid{
	public:
	virtual void run() =0;
};

class ScrollingLetterRoid : public LetteroidVR {
public:
	
	ScrollingLetterRoid(int posx = rand() % 81, int posy = rand() % 21, int speed = 5, char letter = 'S') :
		m_speed(speed), m_ticktrack(0) {
		setCoords(posy, posx);
		setLetter(letter);
	}

	enum perim {
		LEFT, RIGHT= 80
	};

	void run() { erase(); update(); draw(); }

	void update() {
		if (getY() == RIGHT) {
			setLetter(charPik());
			setCoords(rand() % 21, 0);
		}
		else {
			setCoords(getX(), getY() + 1);
		}
	}

private:
char charPik(){
	//total of: <67>  letters and char pool
	char pool[68] {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$*"};
	char finalch;
		int l = rand() % 68;
		finalch = pool[l];
	return finalch;
}
private:
	int m_speed;
	int m_ticktrack;

};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>END OF SCROLLING LETTEROID<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class MovingLetteroid : public LetteroidVR {
public:
	// MovingLetteroid(){}
	MovingLetteroid(int posx = rand() % 81, int posy = rand()%21, int speed = 5, char letter = 'M'):
		m_speed(speed), m_ticktrack(0), vel(rand()%4){
		setCoords(posy, posx);
		setLetter(letter);
	}
	void run() { erase(); update(); draw(); }
	void tick() { ++m_ticktrack; }
private:
	int m_speed;
	int m_ticktrack;
	int vel;
	enum dir
	{
		UPRIGHT, DOWNRIGHT, DOWNLEFT, UPLEFT, BOTTOM = 20, RIGHTSIDE = 80
	};
private:
	void update() {
		//erase();
		if (vel == UPRIGHT) { 
			if (getY() == RIGHTSIDE) {
				setCoords((getX()-1), (getY()-1)); vel = UPLEFT;
			}
			else if (getX() == 0/*top*/) {
				setCoords((getX()+1), (getY()+1)); vel = DOWNRIGHT;
			}
			else {
			setCoords((getX()-1), (getY() + 1));
			}
		}
		else if (vel == DOWNRIGHT) {
			if (getY() == RIGHTSIDE) {
				setCoords((getX() + 1), (getY()-1)); vel = DOWNLEFT;
			}
			else if (getX() == BOTTOM) {
				setCoords((getX()-1), (getY() + 1)); vel = UPRIGHT;
			}
			else {
				setCoords((getX() + 1), (getY() + 1));
			}
		}
		else if (vel == DOWNLEFT) {
			if (getY() == 0/*leftside*/) {
				setCoords((getX() + 1), (getY() + 1)); vel = DOWNRIGHT;
			}
			else if (getX() == BOTTOM) {
				setCoords((getX()-1), (getY() - 1)); vel = UPLEFT;
			}
			else {
				setCoords((getX() + 1), (getY()-1));
			}
		}
		else if (vel == UPLEFT) {
			if (getY() == 0/*leftside*/) {
				setCoords((getX()-1), (getY() + 1)); vel = UPRIGHT;
			}
			else if (getX() == 0) {
			  setCoords((getX() + 1), (getY() - 1)); vel = DOWNLEFT;
			}
			else {
				setCoords((getX()-1), (getY()-1));
			}
		}
	}//END OF VOID UPDATE()
char charPik(){
	//total of: <67>  letters and char pool
	char pool[68] {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$*"};
	char finalch;
		int l = rand() % 68;
		finalch = pool[l];
	return finalch;
}
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>END OF MOVING LETTEROID<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class JumpingLetteroid: public LetteroidVR {
public:
	// JumpingLetteroid(){}
	JumpingLetteroid(int posx = rand() % 80, int posy = rand() % 20, int speed = 5):
		m_speed(speed), m_ticktrack(0){
			setCoords(posy, posx);
			setLetter(charPik());
	}
	void run(){erase(); update(); draw();}
private:
void update(){
	setCoords(rand() % 20, rand() % 80);
}
char charPik(){
	//total of: <67>  letters and char pool
	char pool[68] {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$*"};
	char finalch;
		int l = rand() % 68;
		finalch = pool[l];
	return finalch;
}

private:
	int m_speed;
	int m_ticktrack;
	

};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>END OF JUMPING LETTEROID<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//----------------------------------------END OF ADDED CODE------------------------------------------------//

int main()
{


  LetteroidField screen;
  screen.start();
  screen.setTitle("LETTEROIDS, press any key to move, 'x' to quit");

  
  BlinkingLetteroid one(true);
  BlinkingLetteroid two(false);
  BlinkingLetteroid three(false);
  BlinkingLetteroid four(true);


  one.setLetter('!'); /// character
  one.setCoords(5, 10); /// row, col
  two.setLetter('h');
  two.setCoords(7, 9);
  three.setLetter('@');
  three.setCoords(15, 57);
  four.setLetter('*');
  four.setCoords(10, 47);

  /// create and initialize your letteroids here
  
  srand(time(NULL));

	std::vector<LetteroidVR*> vecLs;
	for (int i = 0; i < 6; ++i){
		switch(i){
			case 0: case 1:{ vecLs.push_back(new ScrollingLetterRoid); break;}
			case 2: case 3:{ vecLs.push_back(new MovingLetteroid); break;}
			case 4: case 5:{ vecLs.push_back(new JumpingLetteroid); break;}
		}
	}
	for (int i = 0, j; i < 6; ++i){
		j = rand()% 6;
		switch(j){
			case 0: case 1:{ vecLs.push_back(new ScrollingLetterRoid); break;}
			case 2: case 3:{ vecLs.push_back(new MovingLetteroid); break;}
			case 4: case 5:{ vecLs.push_back(new JumpingLetteroid); break;}
		}
	}

  while ( screen.waitForKeyPress() ) /// keep going until 'x' is pressed
    {
      one.blink();
      two.blink();
      three.blink();
      four.blink();
      /// call the function that draws your letteroids here
	for (int i = 0; i < 12; ++i){
		vecLs[i]->run();
	}
      // m1.run();
	  // s1.run();
	  // j1.run();
    }

  screen.end();
  return 0;
}
