#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <format>

using namespace std;
using namespace sf;

struct PlayerStats { // included from another file
	string username;
	int xp;
	int wins;
	float kd;
	
	PlayerStats(int random_number) {
		username = "default_name" + to_string(random_number);
		wins = kd = 0;
		xp = (random_number * 37 + 11) % 100; // cool hash
	}
};

struct StatRow {
	Text ranking, username, xp, wins, kd;

	StatRow(Font& font, Vector2f position, int ranking_, string username_, int xp_, int wins_, float kd_);
	void Render(RenderWindow& window);
	void Update(int ranking_, string username_, int xp_, int wins_, float kd_, bool is_user = false);
	void CenterText(Text& text);
};

class LeaderSortUI {
	vector<Text> panel_texts;

	Texture elements_texture;
	Font pixeloid_font;

	Sprite panel;
	vector<Sprite> element_sprites;
	Vector2f panel_center;
	vector<FloatRect> element_rects;

	bool dynamic_stats;
	bool merge_sort;
	bool quick_sort;
	int highlight_index;
	int selected_stat;
	int scroll_offset;

	vector<PlayerStats> xp_sorted;
	vector<PlayerStats> wins_sorted;
	vector<PlayerStats> kd_sorted;
	
	vector<StatRow> stat_rows;
	StatRow user_row;
	
public:
	LeaderSortUI(Vector2f window_center_, Texture elements_texture_, Font pixeloid_font_);

	void Render(RenderWindow& window);
	void Update(Vector2i mouse_position, bool clicked, int scroll_delta);
	void Refresh();
	void ScrollStats(int scroll_delta);
};
