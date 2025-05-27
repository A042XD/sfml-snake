#include<sfml/graphics.hpp>
#include<bits/stdc++.h>

#define pii pair<int,int>
#define fi first
#define se second

using namespace sf;
using namespace std;

int bd[25][25],fdmp[25][25];
pii genfd(){
	int y=1,x=1;
	do{
		y=rand()%20;
		x=rand()%20;	
	}while(fdmp[y][x]);
	fdmp[y][x]=1;
	return {y,x};
}

signed main(){
	srand((unsigned)time(NULL));
	RenderWindow win(VideoMode({1000, 1000}), "Snake", Style::Titlebar | Style::Close);
	Clock clock;
	Font font("Arial.ttf");
	Text text(font);
	text.setString("Game End");
	text.setFillColor(Color::White);

	int lose=0;
	vector<pii>ps;
	ps.push_back({10, 10});
	bd[10][10]=1;
	int dir=1;
	int dx[5] = {0, 0, 1, 0, -1};
	int dy[5] = {0, 1, 0, -1, 0};
	for(int i=3;i;i--)genfd();
	
	win.setFramerateLimit(60);
	while(win.isOpen()){
		while(const optional event = win.pollEvent()){
			if(event->is<Event::Closed>()){
				win.close();
			}
		}
		if(lose){
			win.clear();
			win.draw(text);
			win.display();
			continue;
		}

		// Keys
		if(Keyboard::isKeyPressed(Keyboard::Key::Left))dir=4;
		if(Keyboard::isKeyPressed(Keyboard::Key::Right))dir=2;
		if(Keyboard::isKeyPressed(Keyboard::Key::Up))dir=1;
		if(Keyboard::isKeyPressed(Keyboard::Key::Down))dir=3;
		
		// Process
		if(clock.getElapsedTime().asMilliseconds() < 200)continue;
		clock.restart();
		
		auto [y,x]=*ps.begin();
		auto [yy,xx]=ps.back();
		bd[yy][xx]--;
		y=(y+dy[dir]+20)%20;
		x=(x+dx[dir]+20)%20;
		if(bd[y][x])lose=1;
		bd[y][x]++;
		ps.insert(ps.begin(),{y,x});
		ps.pop_back();	
		
		for(int i=0;i<20;i++){
			for(int j=0;j<20;j++){
				if(bd[i][j]&&fdmp[i][j]){
					genfd();
					fdmp[i][j]=0;
					ps.push_back(ps.back());
					auto [y,x]=ps.back();
					bd[y][x]++;
				}
			}
		}

		// Draw
		win.clear();
		for(int y=0;y<20;y++){
			for(int x=0;x<20;x++){
				if(!fdmp[y][x])continue;
				RectangleShape r(Vector2f{50, 50});
				r.setPosition({x * 50, 950 - y * 50});
				r.setFillColor(Color::Red);
				win.draw(r);
			}
		}
		int i=0;
		for(auto x:ps){
			RectangleShape r(Vector2f{50, 50});
			r.setPosition({x.se * 50, 950 - x.fi * 50});
			r.setFillColor(Color(max(0,230-i*10),120,120));
			win.draw(r);
			i++;
		}
		win.display();
	}
	return 0;
}
