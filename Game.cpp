////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <bits/stdc++.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct TextFormat
{
    int size_font = 60;
    Color menu_text_color = Color::White;
    float bord = 0.0f;
    Color border_color = Color::Black;
};

void InitText(Text& mtext, float xpos, float ypos, const String & str,TextFormat Ftext);


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int Record[3];
bool isPlaying = false;
int tek_pts = 0;
int Egg[3];
int curEgg = 0;
int lives = 3;
int Level = 1;
int tek_pos = 0;

int can = 0;

struct Kurica {
	Sprite egg[4];
	int cur = -1, t = 100;
	int update() {
		t --;
		cout << t << '\n';
		if(t != 0) return 0;
		t = 100;
		cur ++;
		if(cur != 3) can = 1;
		if(cur == 4) {
			cur = -1;
			return 1;
		}
		return 0;
	}
}bird[4];

void rest() {
	isPlaying = false;
	tek_pos = 0;
	tek_pts = 0;
	for(int i = 0; i < 3; i ++) {
		Egg[i] = rng()%3;
	}
	for(int i = 0; i < 4; i ++) {
		bird[i].cur = -1;
		bird[i].t = 100;
	}
	curEgg = 0;
	lives = 3;
}


SoundBuffer getsound(string s) {
	SoundBuffer buffer;
	cout << s << '\n';
	buffer.loadFromFile(s);
	return buffer;
}

int main()
{
	 setlocale(LC_ALL, "Russian");
    // Create the main window
    auto width = 1400;
    auto height = 700;
 	RenderWindow window;
    window.create(VideoMode(width, height), "NfactorialGame");

//    window.setMouseCursorVisible(false); //ioee??aai aeaeiinou eo?ni?a


  	RectangleShape background(Vector2f(width, height));

    Texture texture_window;
    if (!texture_window.loadFromFile("resources\\ramka1.png")) return 0;
    background.setTexture(&texture_window);
    
    RectangleShape backgroundongame(Vector2f(width, height));

    Texture texture_window_ongame;
    if (!texture_window_ongame.loadFromFile("resources\\gameison.png")) return 0;
    backgroundongame.setTexture(&texture_window_ongame);
    
    Font font;
	if (!font.loadFromFile("resources\\font.otf")) return 0;
    Font font1;
	if (!font1.loadFromFile("resources\\font1.ttf")) return 0;
	Font font2;
	if (!font2.loadFromFile("resources\\font2.ttf")) return 0;
	
    Text Title;
    Title.setFont(font);
    
	TextFormat Ftext;
    Ftext.size_font = 30;
    Ftext.menu_text_color = Color(237, 147, 0);
    Ftext.bord = 3;
    TextFormat LevText;
    
    InitText(Title, 200, 120, "Ну, погоди! - Волк ловит яйца", Ftext);
    
    Text YourRecord;
    YourRecord.setFont(font);
//    InitText(YourRecord, 200, 175, "Ваш рекорд: " + to_string(Record), Ftext);

    Text Pause;
    Pause.setFont(font);
    InitText(Pause, 500, 300, "Пауза", Ftext);

    Text PauseF;
    PauseF.setFont(font);
    InitText(PauseF, 300, 50, "P - Пауза", Ftext);

    Text nebag;
    nebag.setFont(font);
    InitText(nebag, 100, 500, "Не баг а фича :)", Ftext);

    Text CurrentPoints;
    CurrentPoints.setFont(font);

    Text PressFtoPlay;
    PressFtoPlay.setFont(font);
    InitText(PressFtoPlay, 200, 230, "Press F to pay respect and Play", Ftext);

    Text F;
    F.setFont(font1);
    TextFormat bigF;
    bigF.size_font = 300;
    bigF.menu_text_color = Color(255,0,0);
    bigF.bord = 3;
    InitText(F, 400	, 200, "F", bigF);
    
    Texture gameover_tex;
    if(!gameover_tex.loadFromFile("resources\\gameover.png")) return 0;
    Sprite gameover = Sprite(gameover_tex);
    gameover.setScale(0.3,0.3);
    gameover.setPosition(500,200);
    
    Texture wolfes[4];
	Sprite wolf[4];
	
    for(int i = 0; i < 4; i ++) {
    	if(!wolfes[i].loadFromFile("resources\\wolf" + to_string(i) + ".png")) return 0;
		wolf[i] = Sprite(wolfes[i]);
		float sc = 0.25;
		wolf[i].setScale(sc,sc);
		int lef = 120;
		int rig = 650;
		if(i == 0) {
			wolf[i].setPosition(rig,0);
		}
		if(i == 1) {
			wolf[i].setPosition(lef,0);
		}
		if(i == 2) {
			wolf[i].setPosition(rig,0);
		}
		if(i == 3) {
			wolf[i].setPosition(lef,0);
		}
	}
	
    Texture eggs;
    if(!eggs.loadFromFile("resources\\eggs.png")) return 0;
    for(int i = 0; i < 4; i ++) {
    	bird[i].egg[0] = Sprite(eggs, IntRect(0,0,80,80));
    	bird[i].egg[1] = Sprite(eggs, IntRect(85,0,80,80));
    	bird[i].egg[2] = Sprite(eggs, IntRect(180,10,80,80));
    	bird[i].egg[3] = Sprite(eggs, IntRect(290,5,90,90));
    	for(int j = 0; j < 4; j ++) {
    		int refx = 1;
    		if(i%2 == 0) refx = -1;
    		bird[i].egg[j].setScale(0.5*refx,0.5);
		}
		if(i == 0) {
    		bird[i].egg[0].setPosition(1220, 364);
    		bird[i].egg[1].setPosition(1190, 390);
    		bird[i].egg[2].setPosition(1155, 420);
    		bird[i].egg[3].setPosition(1095, 463);
		}
		if(i == 1) {
			int x = 25;
			int y = 210;
    		bird[i].egg[0].setPosition(183-x,170-x+y);
    		bird[i].egg[1].setPosition(216-x,204-x+y);
    		bird[i].egg[2].setPosition(258-x,242-x+y);
    		bird[i].egg[3].setPosition(295-x+30,275-x+y);
		}
		if(i == 2) {
			int y = 210;
    		bird[i].egg[0].setPosition(1220, 364-y);
    		bird[i].egg[1].setPosition(1190, 390-y);
    		bird[i].egg[2].setPosition(1155, 420-y);
    		bird[i].egg[3].setPosition(1095, 463-y);
		}
    	if(i == 3) {
    		int x = 25;
    		bird[i].egg[0].setPosition(183-x,170-x);
    		bird[i].egg[1].setPosition(216-x,204-x);
    		bird[i].egg[2].setPosition(258-x,242-x);
    		bird[i].egg[3].setPosition(295-x,275-x);
		}
	}
    
	Text Lives;
    Lives.setFont(font);
    rest();
    
    
    LevText.size_font = 50;
    LevText.menu_text_color = Color(88, 60, 251);
	LevText.bord = 3;
    Text CurLevel;
    
    CurLevel.setFont(font2);
    map<int,string> name_level;
    name_level[1] = "Малыш (Слишком просто)";
    name_level[2] = "Журттын баласы (Средний)";
    name_level[3] = "Поступил в nFactorial (бешенный)";
    InitText(CurLevel, 600, 300, "Уровень сложности: " + name_level[Level], LevText);
    
    Texture changelevel;
    if(!changelevel.loadFromFile("resources\\changelevel.png")) return 0;
    Sprite Harder = Sprite(changelevel, IntRect(0,0,288,122));
    Harder.setPosition(650, 380);
    Sprite Easier = Sprite(changelevel, IntRect(0,122,288,122));
    Easier.setPosition(950, 380);
    
    
    SoundBuffer clickBuffer;
    if(!clickBuffer.loadFromFile("resources\\click.ogg")) return 0;
    Sound click(clickBuffer);

    SoundBuffer startBuffer;
    if(!startBuffer.loadFromFile("resources\\start.ogg")) return 0;
    Sound start(startBuffer);

	SoundBuffer pointBuffer;
    if(!pointBuffer.loadFromFile("resources\\point.ogg")) return 0;
    Sound point(pointBuffer);

	SoundBuffer minusBuffer;
    if(!minusBuffer.loadFromFile("resources\\minus.ogg")) return 0;
    Sound minus(minusBuffer);
    bool pause = 0;
    bool nb = 0;
	while(window.isOpen()) {
    	Event event;
    	while(window.pollEvent(event)) {
//    	 	 if (event.type == sf::Event::MouseMoved)
//            {
//                cout << event.mouseMove.x << ' ' << event.mouseMove.y << std::endl;
//            } 
			if(!isPlaying) {
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
					Vector2f const mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
					cout << "Mouse world position: " << mousePos.x << " " << mousePos.y << endl;
					if(mousePos.x >= 650 && mousePos.x <= 650+288 && mousePos.y >= 380 && mousePos.y <= 380+122) {
						Level = min(Level+1, 3);
						click.play();
					}
					if(mousePos.x >= 950 && mousePos.x <= 950+288 && mousePos.y >= 380 && mousePos.y <= 380+122) {
						Level = max(Level-1, 1);
						click.play();
					}
				}
			}
			 
			 if ((event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
            	window.close();
            	break;
            }
            
            
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F)) {
                if (!isPlaying) {
                    isPlaying = true;
                    start.play();
                }
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P)) {
                if (isPlaying) {
                	if(!pause)
	                    pause = true;
	                else {
	                	pause = false;
	                	nb = 0;
					}
                }
            }
            
            int ok = tek_pos;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)) {
                tek_pos |= 1;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)) {
                tek_pos &= 2;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)) {
                tek_pos |= 2;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)) {
                tek_pos &= 1;
            }
            if(ok != tek_pos && pause == true) {
            	nb = 1;
			}
		}
        window.clear();
        int bittima = 0;
		if(isPlaying == false) {
		    window.draw(background);
		    window.draw(CurLevel);
		    window.draw(Harder);
		    window.draw(Easier);
		    window.draw(CurLevel);
	        InitText(YourRecord, 200, 175, "Ваш рекорд: " + to_string(Record[Level-1]), Ftext);
		    InitText(CurLevel, 600, 300, "Уровень сложности: " + name_level[Level], LevText);
			window.draw(YourRecord);
	        window.draw(Title);
	        window.draw(PressFtoPlay);
	        window.draw(F);
    	}
    	else {
		    window.draw(backgroundongame);
		    window.draw(PauseF);
    		InitText(CurrentPoints, 400, 100, "Текущий счёт: " + to_string(tek_pts), Ftext);
    		
    		window.draw(CurrentPoints);
    		window.draw(wolf[tek_pos]);
    		for(int i = 0; i < 4; i ++) {
    			if(bird[i].cur != -1) {
    				window.draw(bird[i].egg[bird[i].cur]);
				}
			}
	    	can = 0;
    		if(pause == 0) {
	    		int gone = bird[Egg[curEgg]].update();
	    		if(gone) {
					if(tek_pos == Egg[curEgg]) {
	    				tek_pts ++;
	    				point.play();
	    				Record[Level-1] = max(Record[Level-1], tek_pts);
					}
					else {
						lives --;
						minus.play();
						if(lives == 0) {
							
							bittima = 1;
						}
						else {
							
						}
					}
					Egg[curEgg] = rng()%4;
				}
			}
			else {
				window.draw(Pause);
 			    if(nb) {
 			    	window.draw(nebag);
				 }
			}
		    InitText(Lives, 700, 140, "жизней: " + to_string(lives), Ftext);
    		window.draw(Lives);
    		if(can) {
    			curEgg ++;
    			curEgg %= Level;
			}
		}
		if(bittima) {
			window.draw(gameover);
			rest();
			window.display();
			Sleep(2000);
			continue;
		}
        window.display();
	}
}

// функция настройки текста
void InitText(Text& mtext, float xpos, float ypos, const String & str, TextFormat Ftext)
{
    mtext.setCharacterSize(Ftext.size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(Ftext.menu_text_color);
    mtext.setOutlineThickness(Ftext.bord);
    mtext.setOutlineColor(Ftext.border_color);
}
