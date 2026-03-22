#define SFML_STATIC
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

using namespace std;


ifstream finn("date.in");

vector<vector<int>>v;
vector<vector<int>>af;

int n = 16, m = 16;
int cnt_bombe = 0;
bool Stil_In_this = 1;

int dx[] = { -1,-1,-1, 0, 1, 1, 1, 0 };
int dy[] = { -1, 0, 1, 1, 1, 0,-1,-1 };

char smn = '?';

///0 nimic
///-1 bomba
///? nu stii cei acolo

void draw_table(vector<vector<int>>& a, sf::RenderWindow& window)
{
	//sf::RenderWindow window(sf::VideoMode(424, 424), "Minesweeper", sf::Style::Close);
	sf::RectangleShape shape(sf::Vector2f(2 * 424, 2 * 424));
	shape.setFillColor(sf::Color(150, 150, 150));
	sf::Font font;
	font.loadFromFile("impact.ttf");
	sf::Text text1, text2, text3, text4, text5, text6, text7, text8;
	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	text4.setFont(font);
	text5.setFont(font);
	text6.setFont(font);
	text7.setFont(font);
	text8.setFont(font);
	text1.setString("1");
	text2.setString("2");
	text3.setString("3");
	text4.setString("4");
	text5.setString("5");
	text6.setString("6");
	text7.setString("7");
	text8.setString("8");
	text1.setCharacterSize(32);
	text2.setCharacterSize(32);
	text3.setCharacterSize(32);
	text4.setCharacterSize(32);
	text5.setCharacterSize(32);
	text6.setCharacterSize(32);
	text7.setCharacterSize(32);
	text8.setCharacterSize(32);
	text1.setFillColor(sf::Color(0, 0, 255));
	text2.setFillColor(sf::Color(0, 255, 0));
	text3.setFillColor(sf::Color(255, 0, 0));
	text4.setFillColor(sf::Color(128, 0, 128));
	text5.setFillColor(sf::Color(255, 165, 0));
	text6.setFillColor(sf::Color(0, 200, 200));
	text7.setFillColor(sf::Color(64, 64, 64));
	text8.setFillColor(sf::Color(0, 0, 0));
	sf::Texture texture1, texture2;
	texture1.loadFromFile("unopened.png");
	texture2.loadFromFile("STEAG.png");
	sf::Sprite sprite1, sprite2;
	sprite1.setTexture(texture1);
	sprite2.setTexture(texture2);
	window.clear();
	window.draw(shape);
	for (int i = 0; i <= 2 * 424; i += 53) {
		sf::Vertex line1[] =
		{
			sf::Vertex(sf::Vector2f(i, 0), sf::Color(0, 0, 0)),
			sf::Vertex(sf::Vector2f(i, 2 * 424), sf::Color(0, 0, 0))
		};
		window.draw(line1, 2, sf::Lines);
		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(0, i), sf::Color(0, 0, 0)),
			sf::Vertex(sf::Vector2f(2 * 424, i), sf::Color(0, 0, 0))
		};
		window.draw(line2, 2, sf::Lines);
	}
	text3.setPosition(53 / 3 + 1, 53 / 3 - 8);
	for (int i = 1; i <= 16; i++) {
		for (int j = 1; j <= 16; j++) {
			if (a[i][j] == 0) {
				continue;
			}
			else if (a[i][j] == 1) {
				text1.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text1);
			}
			else if (a[i][j] == 2) {
				text2.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text2);
			}
			else if (a[i][j] == 3) {
				text3.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text3);
			}
			else if (a[i][j] == 4) {
				text4.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text4);
			}
			else if (a[i][j] == 5) {
				text5.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text5);
			}
			else if (a[i][j] == 6) {
				text6.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text6);
			}
			else if (a[i][j] == 7) {
				text7.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text7);
			}
			else if (a[i][j] == 8) {
				text8.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text8);
			}
			else if (a[i][j] == -1) {
				sprite2.setPosition(53 * (j - 1), 53 * (i - 1));
				sprite2.setScale(0.1, 0.1);
				window.draw(sprite2);
			}
			else if (a[i][j] == (int)'?') {
				sprite1.setPosition(53 * (j - 1), 53 * (i - 1));
				sprite1.setScale(0.1, 0.1);
				window.draw(sprite1);
			}
		}
	}
	window.display();

}
void draw_table_loser(vector<vector<int>>& a, vector<vector<int>>& v, sf::RenderWindow& window, int x, int y, vector<pair<int, int>>& t)
{
	sf::Texture tx5;
	tx5.loadFromFile("STEAG_ROSU.png");
	sf::Sprite sp5;
	sp5.setTexture(tx5);

	//sf::RenderWindow window(sf::VideoMode(424, 424), "Minesweeper", sf::Style::Close);
	sf::RectangleShape shape(sf::Vector2f(2 * 424, 2 * 424));
	shape.setFillColor(sf::Color(150, 150, 150));
	sf::Font font;
	font.loadFromFile("impact.ttf");
	sf::Text text1, text2, text3, text4, text5, text6, text7, text8;
	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	text4.setFont(font);
	text5.setFont(font);
	text6.setFont(font);
	text7.setFont(font);
	text8.setFont(font);
	text1.setString("1");
	text2.setString("2");
	text3.setString("3");
	text4.setString("4");
	text5.setString("5");
	text6.setString("6");
	text7.setString("7");
	text8.setString("8");
	text1.setCharacterSize(32);
	text2.setCharacterSize(32);
	text3.setCharacterSize(32);
	text4.setCharacterSize(32);
	text5.setCharacterSize(32);
	text6.setCharacterSize(32);
	text7.setCharacterSize(32);
	text8.setCharacterSize(32);
	text1.setFillColor(sf::Color(0, 0, 255));
	text2.setFillColor(sf::Color(0, 255, 0));
	text3.setFillColor(sf::Color(255, 0, 0));
	text4.setFillColor(sf::Color(128, 0, 128));
	text5.setFillColor(sf::Color(255, 165, 0));
	text6.setFillColor(sf::Color(0, 200, 200));
	text7.setFillColor(sf::Color(64, 64, 64));
	text8.setFillColor(sf::Color(0, 0, 0));

	sf::Texture texture1, texture2, texture3, texture4;

	texture1.loadFromFile("unopened.png");
	texture2.loadFromFile("STEAG.png");
	texture3.loadFromFile("bomb_nobg.png");
	texture4.loadFromFile("BOMBA_ROSU.png");

	sf::Sprite sprite1, sprite2, sprite3, sprite4;

	sprite1.setTexture(texture1);
	sprite2.setTexture(texture2);
	sprite3.setTexture(texture3);
	sprite4.setTexture(texture4);

	window.clear();
	window.draw(shape);
	for (int i = 0; i <= 2 * 424; i += 53) {
		sf::Vertex line1[] =
		{
			sf::Vertex(sf::Vector2f(i, 0), sf::Color(0, 0, 0)),
			sf::Vertex(sf::Vector2f(i, 424), sf::Color(0, 0, 0))
		};
		window.draw(line1, 2, sf::Lines);
		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(0, i), sf::Color(0, 0, 0)),
			sf::Vertex(sf::Vector2f(424, i), sf::Color(0, 0, 0))
		};
		window.draw(line2, 2, sf::Lines);
	}
	text3.setPosition(53 / 3 + 1, 53 / 3 - 8);
	for (int i = 1; i <= 16; i++) {
		for (int j = 1; j <= 16; j++) {
			if (a[i][j] == 0) {
				continue;
			}
			else if (a[i][j] == 1) {
				text1.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text1);
			}
			else if (a[i][j] == 2) {
				text2.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text2);
			}
			else if (a[i][j] == 3) {
				text3.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text3);
			}
			else if (a[i][j] == 4) {
				text4.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text4);
			}
			else if (a[i][j] == 5) {
				text5.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text5);
			}
			else if (a[i][j] == 6) {
				text6.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text6);
			}
			else if (a[i][j] == 7) {
				text7.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text7);
			}
			else if (a[i][j] == 8) {
				text8.setPosition(53 * (j - 1) + 53 / 3 + 1, 53 * (i - 1) + 53 / 3 - 8);
				window.draw(text8);
			}
			else if (v[i][j] == -1) {
				sprite3.setPosition(53 * (j - 1), 53 * (i - 1));
				sprite3.setScale(0.1, 0.1);
				window.draw(sprite3);
			}
			else if (a[i][j] == (int)'?') {
				sprite1.setPosition(53 * (j - 1), 53 * (i - 1));
				sprite1.setScale(0.1, 0.1);
				window.draw(sprite1);
			}
		}
	}

	sprite4.setPosition(53 * (y - 1), 53 * (x - 1));
	sprite4.setScale(0.074, 0.074);
	window.draw(sprite4);

	for (const auto& i : t)
	{
		sp5.setPosition(53 * (i.second - 1), 53 * (i.first - 1));
		sp5.setScale(0.1, 0.1);
		window.draw(sp5);
	}

	window.display();

}
bool fits(int x, int y)
{
	if (x >= 1 && x <= n && y >= 1 && y <= m)
		return 1;
	return 0;
}
void generate()
{
	vector<vector<int>>mine;
	mine.resize(n + 1);

	vector<int>l;

	for (int i = 0; i <= m; i++)
		l.push_back(i);

	for (int i = 1; i <= n; i++)
		mine[i] = l;

	srand((unsigned)time(0));
	int r = cnt_bombe;
	while (cnt_bombe)
	{
		int t1 = 1 + (rand() % n);
		while (mine[t1].size() == 1)
			t1 = 1 + (rand() % n);


		int t2 = 1 + (rand() % (mine[t1].size() - 1));

		int x = t1;
		int y = mine[t1][t2];
		mine[t1].erase(mine[t1].begin() + t2);

		v[x][y] = -1;

		cnt_bombe--;
	}
	cnt_bombe = r;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (v[i][j] == 0)
				for (int a = 0; a < 8; a++)
				{
					int x = i + dx[a];
					int y = j + dy[a];
					if (fits(x, y))
						if (v[x][y] == -1)
							v[i][j]++;
				}
		}
	}
}
void afis(vector<vector<int>>& af)
{
	cout << '\n' << '\n';
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			if (af[i][j] == smn)
				cout << " " << smn << " ";
			else if (af[i][j] == -1)
				cout << af[i][j] << " ";
			else cout << " " << af[i][j] << " ";

		cout << '\n';
	}
}
void citire_generare()
{
	///finn >> n >> m >> cnt_bombe;
	cnt_bombe = 40;
	v.resize(n + 1, vector<int>(m + 1));
	af.resize(n + 1, vector<int>(m + 1, smn));

	generate();

}

bool verif_cnt_bombe_vecini(int x, int y)
{
	int cnt = 0;
	for (int i = 0; i < 8; i++)
	{
		int a = x + dx[i];
		int b = y + dy[i];
		if (fits(a, b))
			if (af[a][b] == -1)
				cnt++;
	}
	//cout << cnt << " " << af[x][y] << " " << x << " " << y << '\n';
	if (cnt == af[x][y])
	{
		//cout << "sdgjdsfklgjsdkf";
		return 1;
	}

	return 0;
}
bool verif_bombe_cu_cele_de_pe_afis(int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		int a = x + dx[i];
		int b = y + dy[i];
		if (fits(a, b))
			if (af[a][b] == -1 && v[a][b] != -1)
				return 0;
	}
	return 1;
}
void lee(int s, int t)
{
	queue<pair<int, int>>q;
	q.push({ s,t });
	if (af[s][t] != smn)
	{
		//cout << 1 << " ";
		if (verif_cnt_bombe_vecini(s, t))
		{
			if (verif_bombe_cu_cele_de_pe_afis(s, t))
			{
				///introducere vecini in cazul in care este dezvelit deja un numar care are toti vecinii descoperitii

				for (int i = 0; i < 8; i++)
				{
					int a = s + dx[i];
					int b = t + dy[i];
					if (fits(a, b))
						if (af[a][b] == smn && v[a][b] >= 0)
						{
							q.push({ a,b });
							//cout << a << " " << b;
						}
				}
			}
			else
			{
				///cout << "FAIL: lee - verif_bombe_cu_cele_de_pe_afis a returnat 0 pentru (" << s << "," << t << ")\n";
				Stil_In_this = 0;
			}
		}

	}
	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		af[x][y] = v[x][y];

		if (v[x][y] == 0)
		{
			///descoperire pentru v[x][y] gol
			for (int i = 0; i < 8; i++)
			{
				int a = x + dx[i];
				int b = y + dy[i];
				if (fits(a, b))
					if (af[a][b] == smn && v[a][b] >= 0)
						q.push({ a,b });
			}
		}
		else if (v[x][y] > 0)
		{
			///descoperire pentru v[x][y] numar
			for (int i = 0; i < 8; i++)
			{
				int a = x + dx[i];
				int b = y + dy[i];
				if (fits(a, b))
					if (v[a][b] == 0)
						if (af[a][b] == smn && v[a][b] >= 0)
							q.push({ a,b });
			}
		}
	}
}
bool verificare_finala()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (v[i][j] > 0 && v[i][j] != af[i][j])
				return 0;

	return 1;
}
bool nrcst()
{

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (v[i][j] > 0 && af[i][j] != v[i][j])
				return 0;

	return 1;

}
void c_2(int x, int y)
{
	af[x][y] = smn;
}
void c_1(int x, int y)
{
	if (af[x][y] != smn)
		return;
	af[x][y] = -1;
	cnt_bombe--;
}
void cdescop(int x, int y)
{
	if (af[x][y] == -1) {
		return;
	}
	if (v[x][y] == -1)
	{
		///cout << "FAIL: cdescop - ai apasat direct pe bomba (" << x << "," << y << ")\n";
		Stil_In_this = 0;
		return;
	}
	lee(x, y);
}
pair<int, int> conversie(int xx, int yy)
{
	int x, y;
	x = yy / 53 + 1;
	y = xx / 53 + 1;

	return { x,y };
}
void solve()
{
	citire_generare();
	afis(v);
	int c, x, y;
	///-1 seteaza steagul
	///-2 sterge un steag in caz ca lai pus din  greasala
	///1 dezveleste un nr

	sf::RenderWindow window(sf::VideoMode(2 * 424, 2 * 424), "Minesweeper", sf::Style::Close);

	while (window.isOpen())
	{

		sf::Event ev;
		while (window.pollEvent(ev))
		{

			//cout << "yes";
			//close the window by pressing the X
			if (ev.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			//close the window by pressing Escape
			if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				window.close();
				break;
			}
			if (nrcst())
			{
				cout << "BINE BAAAAA";
			}
			if (ev.type == sf::Event::MouseButtonPressed && nrcst() == 0)
			{
				if (ev.mouseButton.button == sf::Mouse::Left)
				{
					//afis(af);
					//cout << "yes";

					int xx = ev.mouseButton.x;
					int yy = ev.mouseButton.y;

					//cout << yy << " " << xx << '\n';

					pair<int, int>p = conversie(xx, yy);

					int x = p.first;
					int y = p.second;
					//cout << yy << " " << xx << " " << x << " " << y << '\n';
					cdescop(x, y);
					bool rapadunga = 0;
					if (Stil_In_this == 0)
					{
						rapadunga = 1;
						if (af[x][y] > 0)
						{
							int a, b;
							vector<pair<int, int>>t;
							for (int i = 0; i < 8; i++)
							{
								a = x + dx[i];
								b = y + dy[i];
								if (fits(a, b))
									if (af[a][b] == -1 && v[a][b] != -1)
									{
										cout << a << " " << b << '\n';
										t.push_back({ a,b });
									}
							}

							for (int i = 0; i < 8; i++)
							{
								a = x + dx[i];
								b = y + dy[i];
								if (fits(a, b))
									if (v[a][b] == -1 && af[a][b] != -1)
									{
										///cout << "Esti prost ba";
										cnt_bombe = 0;
										draw_table_loser(af, v, window, a, b, t);
										///cout << "mama mea e florareasa";
										//sp5.setPosition(53 * (y - 1), 53 * (x - 1));
										//sp5.setScale(0.1, 0.1);
										//window.draw(sp5);
										break;
									}
							}

						}
						else
						{
							cout << "Esti prost baaaa";
							cnt_bombe = 0;
							vector<pair<int, int>>t;
							draw_table_loser(af, v, window, x, y, t);
						}
					}
					if (cnt_bombe == 0 && rapadunga == 0)
					{
						///cout << "mama";
						if (verificare_finala())
							cout << "BINE BAAAAA";
						else
						{
							///cout << "FAIL: solve - verificare_finala dupa cnt_bombe==0\n";
							Stil_In_this = 0;
							cout << "Esti prost ba";
							cnt_bombe = 0;
							vector<pair<int, int>>t;
							draw_table_loser(af, v, window, x, y, t);
						}
					}


				}
				else if (ev.mouseButton.button == sf::Mouse::Right)
				{
					int xx = ev.mouseButton.x;
					int yy = ev.mouseButton.y;

					pair<int, int>p = conversie(xx, yy);

					int x = p.first;
					int y = p.second;

					if (af[x][y] == -1)
						c_2(x, y);
					else if (af[x][y] == smn)
						c_1(x, y);

					if (cnt_bombe == 0 && nrcst())
						if (Stil_In_this)
						{
							if (verificare_finala())
								cout << "BINE BAAAAA";
							else
							{
								///cout << "FAIL: solve - verificare_finala dupa click dreapta\n";
								Stil_In_this = 0;
								cout << "Esti prost ba";
								cnt_bombe = 0;
								vector<pair<int, int>>t;
								draw_table_loser(af, v, window, x, y, t);
							}
						}
				}
			}
			if (Stil_In_this)
				draw_table(af, window);
		}
	}
}

int main()
{
	solve();
	return 0;
}