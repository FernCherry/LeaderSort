#include "LeaderSortUI.h"

int main() {
	RenderWindow window(VideoMode::getDesktopMode(), "LeaderSort", State::Fullscreen);

	bool dev_build = false; // true: visual studio build, false: regular build 
	string panel_path = "assets/panel.png"; string font_path = "assets/pixeloid.ttf";
	if (dev_build) { panel_path = "../../../assets/panel.png"; font_path = "../../../assets/pixeloid.ttf"; }

	LeaderSortUI UI(window.getDefaultView().getCenter(), Texture(panel_path), Font(font_path));
	Clock clock;

	while (window.isOpen()) {
		bool clicked = false; int scroll_delta = 0;
		float delta_time = clock.restart().asSeconds();

		while (auto event = window.pollEvent()) {
			if (event->is<Event::Closed>() or isKeyPressed(Keyboard::Key::Escape)) { window.close(); }
			else if (auto* mouse = event->getIf<Event::MouseButtonPressed>()) { clicked = true; }
			else if (auto* scroll = event->getIf<Event::MouseWheelScrolled>()) { scroll_delta = scroll->delta; }
		}

		// 10,000 rankings/s
		if (isKeyPressed(Keyboard::Key::Up)) { UI.ScrollRankings(static_cast<int>(10000 * delta_time)); }
		else if (isKeyPressed(Keyboard::Key::Down)) { UI.ScrollRankings(static_cast<int>(-10000 * delta_time)); }

		window.clear(Color(38, 38, 38));
		
		UI.Update(Mouse::getPosition(), clicked, scroll_delta, delta_time);
		UI.Render(window);
		window.display();
	}
	return 0;
}