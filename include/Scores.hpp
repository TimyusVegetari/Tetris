#ifndef SCORES_HPP_
#define SCORES_HPP_

#include <includes.hpp>
#include <sstream>

/* Class to define the scores, levels and next tetriminos. */
class Scores {
  public:
    enum Action {
      OneLine,
      TwoLines,
      ThreeLines,
      FourLines,
      SlowFall,
      FreeFall
    };

  private:
    unsigned int  m_uiScore;              ///< Score of the player.
    unsigned int  m_uiLevel;              ///< Levels of the player.
    unsigned int  m_uiLines;              ///< Lines deleted by the player.
    unsigned int  m_uiRequiredLines;      ///< Lines must be deleted by the player.
    unsigned int  m_uiNextTetriminos[3];  ///< Identifier of the next tetriminos.
    unsigned int  m_uiFallSpeed;          ///< Speed of the fall.
    sf::Texture   m_sfInterface[2];       ///< Display of score, level, lines and next tetriminos.
    sf::Font      m_sfFont;               ///< Font of the game.

  public:
    Scores ( void );
    ~Scores ( void );

    void Initialize ( void );
    void ComputeScore ( Action eAction, unsigned int uiCells = 0 );
    void CheckDeletedLines ( unsigned int uiDeletedLines );
    void GenerateNextTetriminos ( void );
    void Draw ( sf::RenderWindow& sfWindow );
    unsigned int GetNextTetriminos ( void );
    unsigned int GetFallSpeed ( void );
};

#endif // SCORES_HPP_
