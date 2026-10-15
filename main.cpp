#include "LeaderSortUI.h"
// include "Merge and Quick sort or something.h"

int main() {
	RenderWindow window(VideoMode::getDesktopMode(), "LeaderSort", State::Fullscreen);
	LeaderSortUI UI(window.getDefaultView().getCenter(), Texture("../../../assets/panel.png"), Font("../../../assets/pixeloid.ttf"));


	// Class from other file created (could be passed into UI class)


	while (window.isOpen()) {
		bool clicked = false; int scroll_delta = 0;
		while (auto event = window.pollEvent()) {
			if (event->is<Event::Closed>() or isKeyPressed(Keyboard::Key::Escape)) { window.close(); }
			else if (auto* mouse = event->getIf<Event::MouseButtonPressed>()) { clicked = true; }
			else if (auto* scroll = event->getIf<Event::MouseWheelScrolled>()) { scroll_delta = scroll->delta; }
		}

		window.clear(Color(38, 38, 38));

		UI.Update(Mouse::getPosition(), clicked, scroll_delta);
		UI.Render(window);
		window.display();
		
	}
	return 0;
}
