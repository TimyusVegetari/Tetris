#ifndef GAME_HPP_
#define GAME_HPP_

#include <includes.hpp>
#include <Tetriminos.hpp>
#include <Scores.hpp>

#define TETRIMINOS_COUNT 7

/* Class to define the game. */
class Game {
  private :
    bool              m_bRunning;                       ///< State of the game.
    sf::RenderWindow  m_sfWindow;                       ///< Main window of the game.
    sf::Event         m_sfEvent;                        ///< Event of the game.
    sf::Texture       m_sfBricks;                       ///< Bricks which limit the playfield.
    std::map<char, sf::Texture> m_sfTetriminos;         ///< Blocks which compose the tetriminos.
    char              m_cPlayfield[15][23];             ///< Grid of the playfield.
    unsigned int      m_uiCheckLine[23];                ///< Check the number of blocks in each line.
    unsigned int      m_uiLinesCount;                   ///< Number of deleted lines at a T time.
    unsigned int      m_uiSlowFallCellsCount;           ///< Number of cells during the slow fall.
    unsigned int      m_uiFreeFallCellsCount;           ///< Number of cells during the free fall.
    Tetriminos        m_oTetriminos[TETRIMINOS_COUNT];  ///< Set of Tetriminos.
    unsigned int      m_uiCurrentTetriminos;            ///< Current tetriminos in the playfield.
    Scores            m_oScores;                        ///< Score, level, next tetriminos and lines.
    bool              m_bDisplayTetriminos;             ///< State of the tetriminos display.
    bool              m_bGotoNext;                      ///< State of the tetriminos changement.
    bool              m_bCollapse;                      ///< State of the collapse.
    bool              m_bFalling;                       ///< State of the fall.
    bool              m_bFallingSlow;                   ///< State of the slow fall.
    bool              m_bRotationRight;                 ///< State of the right rotation.
    bool              m_bRotationLeft;                  ///< State of the left rotation.
    bool              m_bMovingRight;                   ///< State of the right move.
    bool              m_bMovingLeft;                    ///< State of the left move.
    bool              m_bLockGame;                      ///< State of the game over.
    bool              m_bPause;                         ///< State of the game pause.
    sf::Time          m_sfElapsedTime;                  ///< Get the elapsed time.
    unsigned int      m_uiFallTime;                     ///< Time to fall.
    unsigned int      m_uiDeleteLineTime;               ///< Time to delete lines.

  public :
    Game ( void );
    ~Game ( void );

    bool Initialize ( void );
    bool IsRunning ( void );
    bool IsSleeping ( sf::Clock &sfClock );
    void Events ( void );
    void Update ( void );
    void Draw ( void );
    void SelectTetriminos ( void );
    bool Collide ( void );
    void PrintTetriminos ( void );
    void GoToNext ( void );
    void DeleteLines ( void );
    void Collapse ( void );
};

#endif // GAME_HPP_
