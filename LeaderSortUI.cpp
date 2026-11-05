#include "LeaderSortUI.h"
#include "algorithms.h"
#include <algorithm>
#include <random>
#include <chrono>

void LeaderSortUI::Render(RenderWindow& window) {
	window.draw(panel);

	if (not dynamic_stats) {
		element_sprites[2].setPosition(element_rects[12].position); window.draw(element_sprites[2]);
	}
	if (not merge_sort) {
		element_sprites[2].setPosition(element_rects[13].position); window.draw(element_sprites[2]);
	}
	if (not quick_sort) {
		element_sprites[2].setPosition(element_rects[14].position); window.draw(element_sprites[2]);
	}

	element_sprites[1].setPosition(element_rects[selected_stat].position);
	window.draw(element_sprites[1]);

	switch (highlight_index) {
		case 0: case 1: case 2: // Stat Tabs
			element_sprites[0].setPosition(element_rects[highlight_index].position);
			window.draw(element_sprites[0]); break;
		case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: // Rows
			element_sprites[4].setPosition(element_rects[highlight_index].position);
			window.draw(element_sprites[4]); break;
		case 12: case 13: case 14: // Toggle
			element_sprites[3].setPosition(element_rects[highlight_index].position);
			window.draw(element_sprites[3]); break;
		case 15: // Refresh
			element_sprites[5].setPosition(element_rects[highlight_index].position + Vector2f(3.f, 3.f));
			window.draw(element_sprites[5]); break;
	}

	for (Text& text : panel_texts) {
		window.draw(text);
	}

	for (StatRow& stat_row : stat_rows) {
		stat_row.Render(window);
	}
	user_row.Render(window);
}

void LeaderSortUI::ScrollStats(int scroll_delta) {
	vector<PlayerStats*>* selected_container = nullptr;

	switch (selected_stat) {
		case 0: selected_container = &xp_sorted; break;
		case 1: selected_container = &wins_sorted; break;
		case 2: selected_container = &kd_sorted; break;
		default: return;
	}

	int size = (int)selected_container->size();
	scroll_offset = clamp(scroll_offset - scroll_delta, 0, max(0, size - 9));

	for (int i = 0; i < 9; i++) {
		int ranking = scroll_offset + i;
		if (ranking >= size) { continue; }

		PlayerStats* p = selected_container->at(ranking);
		stat_rows[i].Update(ranking + 1, p->username, p->xp, p->wins, p->kd);
	}
}

void LeaderSortUI::Update(Vector2i mouse_position, bool clicked, int scroll_delta) {
	if (scroll_delta != 0) { ScrollStats(scroll_delta); }

	Vector2f screen_position(mouse_position);
	highlight_index = -1;
	for (int i = 0; i < 16; i++) {
		const FloatRect& rect = element_rects[i];

		if (rect.contains(screen_position)) {
			highlight_index = i;

			if (clicked) {
				switch (highlight_index) {
					case 0: case 1: case 2: selected_stat = highlight_index; ScrollStats(0); break;

					//case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: break; // selected profiles

					case 12: dynamic_stats = not dynamic_stats; break;
					case 13: merge_sort = not merge_sort; quick_sort = not merge_sort; break;
					case 14: quick_sort = not quick_sort; merge_sort = not quick_sort; break;

					case 15: Refresh(); break;
				}
			}
		}
	}

	if (dynamic_stats) {
		// players keep playing: stats only ever increase, rows catch up on Refresh
		static mt19937 rng(random_device{}());
		for (int n = 0; n < 50; n++) {
			PlayerStats& p = database[rng() % database.size()];
			p.xp += 1 + rng() % 20;                   // +1 to +20 xp
			if (rng() % 3 == 0) { p.wins += 1; }      // a win roughly every third update
			p.kd += (rng() % 5) / 100.f;              // +0.00 to +0.04
		}
	}
}

LeaderSortUI::LeaderSortUI(Vector2f panel_center_, Texture elements_texture_, Font pixeloid_font_) :
	panel_center(panel_center_), elements_texture(elements_texture_), panel(elements_texture), pixeloid_font(pixeloid_font_),
	user_row(
		pixeloid_font, Vector2f(panel_center.x - 445.f, (panel_center.y - 314.f) + (51.f * 10) + 20.f),
		77, "", 0, 0, 0.f
	) {

	panel.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(896, 768)));
	panel.setOrigin(Vector2f(448.f, 384.f));
	panel.setPosition(panel_center);

	float left_margin(panel_center.x - 445.f);
	float top_margin(panel_center.y - 314.f);

	element_rects = {
		FloatRect(panel_center + Vector2f(79.f, -381.f), Vector2f(120.f, 64.f)), // XP
		FloatRect(panel_center + Vector2f(79.f + 123.f, -381.f), Vector2f(120.f, 64.f)), // WINS
		FloatRect(panel_center + Vector2f(79.f + 123.f * 2.f, -381.f), Vector2f(120.f, 64.f)), // KD

		FloatRect(Vector2f(left_margin, top_margin + (51.f * 0)), Vector2f(890.f, 48.f)), // Row 1
		FloatRect(Vector2f(left_margin, top_margin + (51.f * 1)), Vector2f(890.f, 48.f)), // Row 2
		FloatRect(Vector2f(left_margin, top_margin + (51.f * 2)), Vector2f(890.f, 48.f)), // Row 3
		FloatRect(Vector2f(left_margin, top_margin + (51.f * 3)), Vector2f(890.f, 48.f)), // Row 4
		FloatRect(Vector2f(left_margin, top_margin + (51.f * 4)), Vector2f(890.f, 48.f)), // Row 5
		FloatRect(Vector2f(left_margin, top_margin + (51.f * 5)), Vector2f(890.f, 48.f)), // Row 6
		FloatRect(Vector2f(left_margin, top_margin + (51.f * 6)), Vector2f(890.f, 48.f)), // Row 7
		FloatRect(Vector2f(left_margin, top_margin + (51.f * 7)), Vector2f(890.f, 48.f)), // Row 8
		FloatRect(Vector2f(left_margin, top_margin + (51.f * 8)), Vector2f(890.f, 48.f)), // Row 9

		FloatRect(panel_center + Vector2f(-312.f, 258.f + 38.f * 0.f), Vector2f(72.f, 36.f)), // 12: Dynamic Stats
		FloatRect(panel_center + Vector2f(-312.f, 258.f + 38.f * 1.f), Vector2f(72.f, 36.f)), // 13: Merge Sort
		FloatRect(panel_center + Vector2f(-312.f, 258.f + 38.f * 2.f), Vector2f(72.f, 36.f)), // 14: Quick Sort

		FloatRect(panel_center + Vector2f(-47.f, 258.f), Vector2f(112.f, 112.f)), // 15: Refresh
	};

	element_sprites = {
		Sprite(elements_texture), // 0 Stat Highlight
		Sprite(elements_texture), // 1 Stat Selected
		Sprite(elements_texture), // 2 Toggle = OFF
		Sprite(elements_texture), // 3 Toggle Highlight
		Sprite(elements_texture), // 4 Row Highlight
		Sprite(elements_texture)  // 5 Refresh Highlight
	};

	element_sprites[0].setTextureRect(IntRect(Vector2i(899, 232), Vector2i(64, 120)));
	element_sprites[0].setOrigin(Vector2f(0.f, 120.f));
	element_sprites[0].rotate(degrees(90));
	element_sprites[1].setTextureRect(IntRect(Vector2i(899, 109), Vector2i(64, 120)));
	element_sprites[1].setOrigin(Vector2f(0.f, 120.f));
	element_sprites[1].rotate(degrees(90));
	element_sprites[2].setTextureRect(IntRect(Vector2i(899, 355), Vector2i(72, 36)));
	element_sprites[3].setTextureRect(IntRect(Vector2i(899, 394), Vector2i(72, 36)));
	element_sprites[4].setTextureRect(IntRect(Vector2i(0, 768), Vector2i(890, 48)));
	element_sprites[5].setTextureRect(IntRect(Vector2i(896, 0), Vector2i(106, 106)));

	dynamic_stats = false;
	merge_sort = true;
	quick_sort = false;

	highlight_index = -1;
	selected_stat = 0;
	scroll_offset = 0;

	// stuff from other files
	// database owns the players; the sorted vectors only hold pointers into it
	database.reserve(10000); // required: a reallocation would invalidate every pointer
	for (int i = 0; i < 10000; i++) {
		database.push_back(PlayerStats(i + 1));
	}
	for (PlayerStats& p : database) {
		xp_sorted.push_back(&p);
		wins_sorted.push_back(&p);
		kd_sorted.push_back(&p);
	}

	// 1 = xp, 2 = wins, 3 = kd
	mergeSort(xp_sorted, 1);
	mergeSort(wins_sorted, 2);
	mergeSort(kd_sorted, 3);

	for (int i = 0; i < 9; i++) {
		PlayerStats* p = xp_sorted.at(i);
		stat_rows.push_back(StatRow(
			pixeloid_font,
			element_rects.at(i + 3).position + Vector2f(0.f, 20.f),
			i + 1,
			p->username,
			p->xp,
			p->wins,
			p->kd
		));
	}
	PlayerStats* u = xp_sorted.at(15);
	user_row.Update(15 + 1, u->username, u->xp, u->wins, u->kd, true);
	// stuff from other files

	panel_texts = {
		Text(pixeloid_font, "RANK", 24),
		Text(pixeloid_font, "NAME", 24),
		Text(pixeloid_font, "XP", 24),
		Text(pixeloid_font, "WINS", 24),
		Text(pixeloid_font, "KD", 24),

		Text(pixeloid_font, "...", 64),

		Text(pixeloid_font, "Dynamic Stats", 16),
		Text(pixeloid_font, "Merge Sort", 16),
		Text(pixeloid_font, "Quick Sort", 16),
		Text(pixeloid_font, "REFRESH", 16),

		Text(pixeloid_font, "Last sort: --", 16) // 10: sort timer
	};
	panel_texts[0].setPosition(element_rects.at(3).position + Vector2f(60.f,  -38.f)); user_row.CenterText(panel_texts[0]);
	panel_texts[1].setPosition(element_rects.at(3).position + Vector2f(325.f, -38.f)); user_row.CenterText(panel_texts[1]);
	panel_texts[2].setPosition(element_rects.at(3).position + Vector2f(587.f, -38.f)); user_row.CenterText(panel_texts[2]);
	panel_texts[3].setPosition(element_rects.at(3).position + Vector2f(710.f, -38.f)); user_row.CenterText(panel_texts[3]);
	panel_texts[4].setPosition(element_rects.at(3).position + Vector2f(833.f, -38.f)); user_row.CenterText(panel_texts[4]);

	panel_texts[5].setPosition(Vector2f(left_margin + 60.f, top_margin + (51.f * 9.f) - 30.f)); user_row.CenterText(panel_texts[5]);

	panel_texts[6].setPosition(panel_center + Vector2f(-230.f, 276.f - 10.f));
	panel_texts[7].setPosition(panel_center + Vector2f(-230.f, 314.f - 10.f));
	panel_texts[8].setPosition(panel_center + Vector2f(-230.f, 352.f - 10.f));
	panel_texts[9].setPosition(panel_center + Vector2f(10.f, 314.f)); user_row.CenterText(panel_texts[9]);

	panel_texts[10].setPosition(panel_center + Vector2f(120.f, 290.f)); // adjust to fit your panel art
}

void LeaderSortUI::Refresh() {
	using clock = chrono::steady_clock;
	auto ms = [](clock::time_point a, clock::time_point b) {
		return chrono::duration<double, milli>(b - a).count();
	};

	string label;
	if (merge_sort) {
		auto t0 = clock::now();
		mergeSort(xp_sorted, 1);
		auto t1 = clock::now();
		mergeSort(wins_sorted, 2);
		auto t2 = clock::now();
		mergeSort(kd_sorted, 3);
		auto t3 = clock::now();

		label = format("Merge sort: {:.2f} ms\nXP {:.2f} | Wins {:.2f} | KD {:.2f}",
			ms(t0, t3), ms(t0, t1), ms(t1, t2), ms(t2, t3));
	}
	else { // quick_sort: not implemented yet
		label = "Quick sort: not implemented";
	}

	panel_texts[10].setString(label);
	cout << label << "\n"; // also logs to the console so you can compare runs
	ScrollStats(0);        // redraw the visible rows with the new order
}



StatRow::StatRow(Font& font, Vector2f position, int ranking_, string username_, int xp_, int wins_, float kd_) :
	ranking(font, "", 24),
	username(font, "", 24),
	xp(font, "", 24),
	wins(font, "", 24),
	kd(font, "", 24) {

	Update(ranking_, username_, xp_, wins_, kd_);

	ranking.setPosition(position + Vector2f(60.f, 0.f));
	username.setPosition(position + Vector2f(325.f, 0.f));
	xp.setPosition(position + Vector2f(587.f, 0.f));
	wins.setPosition(position + Vector2f(710.f, 0.f));
	kd.setPosition(position + Vector2f(833.f, 0.f));
}
void StatRow::Render(RenderWindow& window) {
	window.draw(ranking); window.draw(username); window.draw(xp); window.draw(wins); window.draw(kd);
}
void StatRow::Update(int ranking_, string username_, int xp_, int wins_, float kd_, bool is_user) {
	Color text_color;
	if (is_user) { text_color = Color(255, 255, 255); }
	else if (ranking_ < 6) { text_color  = Color(0, 191, 99); }
	else { text_color = Color(166, 166, 166); }

	ranking.setString(to_string(ranking_) + '.');
	CenterText(ranking); ranking.setFillColor(text_color);

	username.setString(username_);
	CenterText(username); username.setFillColor(text_color);

	xp.setString(to_string(xp_));
	CenterText(xp); xp.setFillColor(text_color);

	wins.setString(to_string(wins_));
	CenterText(wins); wins.setFillColor(text_color);

	kd.setString(format("{:.2f}", kd_));
	CenterText(kd); kd.setFillColor(text_color);
}
void StatRow::CenterText(Text& text) {
	FloatRect rect = text.getLocalBounds();
	text.setOrigin(rect.position + rect.size / 2.f);
}