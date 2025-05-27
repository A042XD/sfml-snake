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
	
	int lose=0;
	vector<pii>ps;
	ps.push_back({10, 10});
	bd[10][10]=1;
	int dir=1;
	int dx[5] = {0, 0, 1, 0, -1};
	int dy[5] = {0, 1, 0, -1, 0};
	vector<pii>fd;
	for(int i=3;i;i--){
		fd.push_back(genfd());
	}
	
	win.setFramerateLimit(60);
	while(win.isOpen()){
		while(const optional event = win.pollEvent()){
			if(event->is<Event::Closed>()){
				win.close();
			}
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
		y+=dy[dir];
		x+=dx[dir];
		if(bd[y][x])lose=1;
		bd[y][x]++;
		ps.insert(ps.begin(),{y,x});
		ps.pop_back();	

		// Draw
		win.clear();
		for(auto x:fd){
			RectangleShape r(Vector2f{50, 50});
			r.setPosition({x.se * 50, 950 - x.fi * 50});
			r.setFillColor(Color::Red);
			win.draw(r);
		}
		for(auto x:ps){
			RectangleShape r(Vector2f{50, 50});
			r.setPosition({x.se * 50, 950 - x.fi * 50});
			r.setFillColor(Color::Blue);
			win.draw(r);
		}
		win.display();
	}
	return 0;
}
