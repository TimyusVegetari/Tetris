#include <includes.hpp>
#include <Game.hpp>

int main ( void ) {

  Game oGame;
  sf::Clock sfClock;

  // Initialising the game.
  if (oGame.Initialize ()) {
    while (oGame.IsRunning ()) {
      if (!oGame.IsSleeping (sfClock)) {
        // The Game is running.
        oGame.Events ();
        oGame.Update ();
        oGame.Draw ();
      }
    }

    return EXIT_SUCCESS;
  }

  // If there is a problem with the initialisation of the game.
  std::cout << "Error : The main window cannot be open !" << std::endl;
  std::cout << "Press 'Enter' to quit..." << std::endl;
  std::cin.get ();
  return EXIT_FAILURE;
}
