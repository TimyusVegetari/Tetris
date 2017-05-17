#include <Scores.hpp>
#include <stdlib.h>   // srand, rand
#include <time.h>     // time

/* Constructor */
Scores::Scores ( void ) :
  m_uiScore           (0),
  m_uiLevel           (0),
  m_uiLines           (0),
  m_uiRequiredLines   (0),
  m_uiFallSpeed       (0),
  m_sfFont            ()
{
}

/* Destructor */
Scores::~Scores ( void ) {
}

/* Initialise the score, level, etc... */
void Scores::Initialize ( void ) {
  m_uiScore             = 0;
  m_uiLevel             = 0;
  m_uiLines             = 0;
  m_uiRequiredLines     = 10;

  // Generate the random seed.
  srand (time (NULL));

  m_uiNextTetriminos[0] = rand () % 7;
  do {
    m_uiNextTetriminos[1] = rand () % 7;
  } while (m_uiNextTetriminos[1] == m_uiNextTetriminos[0]);
  do {
    m_uiNextTetriminos[2] = rand () % 7;
  } while (m_uiNextTetriminos[2] == m_uiNextTetriminos[0] || m_uiNextTetriminos[2] == m_uiNextTetriminos[1]);

  m_uiNextTetriminos[1] = 0;
  m_uiNextTetriminos[2] = 0;
  m_uiFallSpeed         = 940;

  // initialise the font.
  if (!m_sfFont.loadFromFile ("datas/graphics/arial.ttf")) {
    std::cout << "Error : The font can't be open !" << std::endl;
  }

  // Initialise the score, level, etc... display.
  m_sfInterface[0].loadFromFile ("datas/graphics/scores.png", sf::IntRect (0, 0, 16, 320));
  m_sfInterface[1].loadFromFile ("datas/graphics/scores.png", sf::IntRect (16, 0, 112, 320));
}

/* Compute the score of the player. */
void Scores::ComputeScore ( Scores::Action eAction, unsigned int uiCells ) {
  switch (eAction) {
    case Scores::Action::OneLine :
      m_uiScore += 40*(m_uiLevel+1);
      break;
    case Scores::Action::TwoLines :
      m_uiScore += 100*(m_uiLevel+1);
      break;
    case Scores::Action::ThreeLines :
      m_uiScore += 300*(m_uiLevel+1);
      break;
    case Scores::Action::FourLines :
      m_uiScore += 1200*(m_uiLevel+1);
      break;
    case Scores::Action::SlowFall :
      m_uiScore += 1*uiCells;
      break;
    case Scores::Action::FreeFall :
      m_uiScore += 2*uiCells;
      break;
    default :
      break;
  }
}

/* Check the number of deleted lines. */
void Scores::CheckDeletedLines ( unsigned int uiDeletedLines ) {
  m_uiLines += uiDeletedLines;
  if (m_uiLines >= m_uiRequiredLines) {
    m_uiLevel++;
    m_uiRequiredLines = 10*(m_uiLevel+1);
    m_uiFallSpeed = 940-m_uiLevel*80;
  }
}

/* Generate the new next tetriminos. */
void Scores::GenerateNextTetriminos ( void ) {
  m_uiNextTetriminos[0] = m_uiNextTetriminos[1];
  m_uiNextTetriminos[1] = m_uiNextTetriminos[2];
  do {
    m_uiNextTetriminos[2] = rand () % 7;
  } while (m_uiNextTetriminos[2] == m_uiNextTetriminos[0] || m_uiNextTetriminos[2] == m_uiNextTetriminos[1]);
}

/* Draw the score, level, etc... */
void Scores::Draw ( sf::RenderWindow& sfWindow ) {
  sf::Sprite sfInterface[2];
  sfInterface[0].setTexture (m_sfInterface[0]);
  sfInterface[0].setPosition (0.f, 0.f);
  sfInterface[1].setTexture (m_sfInterface[1]);
  sfInterface[1].setPosition (208.f, 0.f);
  sfWindow.draw (sfInterface[0]);
  sfWindow.draw (sfInterface[1]);

  sf::Text sfText;
  sfText.setFont (m_sfFont);
  sfText.setCharacterSize (16);
  sfText.setColor (sf::Color::Green);
  sfText.setStyle (sf::Text::Style::Bold);

  std::string szToString;
  std::ostringstream oss[3];
  // Draw the level.
  oss[0] << m_uiLevel;
  szToString = oss[0].str ();
  sfText.setString (szToString);
  sfText.setOrigin (sfText.getGlobalBounds ().width, 0.f);
  sfText.setPosition (298.f, 30.f);
  sfWindow.draw (sfText);
  // Draw the score.
  oss[1] << m_uiScore;
  szToString = oss[1].str ();
  sfText.setString (szToString);
  sfText.setOrigin (sfText.getGlobalBounds ().width, 0.f);
  sfText.setPosition (298.f, 78.f);
  sfWindow.draw (sfText);
  // Draw the lines.
  oss[2] << m_uiLines;
  szToString = oss[2].str ();
  sfText.setString (szToString);
  sfText.setOrigin (sfText.getGlobalBounds ().width, 0.f);
  sfText.setPosition (298.f, 190.f);
  sfWindow.draw (sfText);
}

/* Get the next tetriminos. */
unsigned int Scores::GetNextTetriminos ( void ) {
  return m_uiNextTetriminos[0];
}

/* Get the fall speed. */
unsigned int Scores::GetFallSpeed ( void ) {
  return m_uiFallSpeed;
}
