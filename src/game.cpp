#include <game.hpp>

/* Constructor */
Game::Game ( void ) :
  m_bRunning            (false),
  m_sfWindow            (),
  m_sfEvent             (),
  m_sfBricks            (),
  m_sfTetriminos        (),
  m_uiLinesCount        (0),
  m_uiSlowFallCellsCount(0),
  m_uiFreeFallCellsCount(0),
  m_uiCurrentTetriminos (0),
  m_oScores             (),
  m_bDisplayTetriminos  (false),
  m_bGotoNext           (false),
  m_bCollapse           (false),
  m_bFalling            (false),
  m_bFallingSlow        (false),
  m_bRotationRight      (false),
  m_bRotationLeft       (false),
  m_bMovingRight        (false),
  m_bMovingLeft         (false),
  m_bLockGame           (false),
  m_bPause              (false),
  m_uiDeleteLineTime    (0)
{
}

/* Destructor */
Game::~Game ( void ) {
}

/* Initialise the game and its components. */
bool Game::Initialize ( void ) {
  m_sfWindow.create (sf::VideoMode (320, 320), "Tetris");
  if (m_sfWindow.isOpen ()) {
    m_bRunning = true;

    // Initialise the playfield.
    for (int iY = 0 ; iY < 22 ; iY++) {
      m_cPlayfield[0][iY] = char(0);
      m_cPlayfield[1][iY] = char(1);
      m_cPlayfield[2][iY] = char(0);
      m_cPlayfield[3][iY] = char(0);
      m_cPlayfield[4][iY] = char(0);
      m_cPlayfield[5][iY] = char(0);
      m_cPlayfield[6][iY] = char(0);
      m_cPlayfield[7][iY] = char(0);
      m_cPlayfield[8][iY] = char(0);
      m_cPlayfield[9][iY] = char(0);
      m_cPlayfield[10][iY] = char(0);
      m_cPlayfield[11][iY] = char(0);
      m_cPlayfield[12][iY] = char(1);
      m_cPlayfield[13][iY] = char(0);
      m_cPlayfield[14][iY] = char(0);
      m_uiCheckLine[iY] = 0;
    }
    for (int iX = 0 ; iX < 15 ; iX++) {
      m_cPlayfield[iX][22] = char(1);
    }
    m_uiCheckLine[22] = 12;

    m_sfBricks.loadFromFile ("datas/graphics/sprites.png", sf::IntRect (0, 0, 16, 16));

    // Initialise the tetriminos.
    char cTetros_I[32] = {   ///< 2*4*4 = 32
      char(0), char(0), char(0), char(0),
      char(0), char(0), char(0), char(0),
      'I', 'I', 'I', 'I',
      char(0), char(0), char(0), char(0),

      char(0), 'I', char(0), char(0),
      char(0), 'I', char(0), char(0),
      char(0), 'I', char(0), char(0),
      char(0), 'I', char(0), char(0)
    };
    m_oTetriminos[0].Initialize (4, 4, 2, cTetros_I);
    m_oTetriminos[0].ResetRotation ();
    m_sfTetriminos['I'] = sf::Texture ();
    m_sfTetriminos['I'].loadFromFile ("datas/graphics/sprites.png", sf::IntRect (16, 0, 16, 16));

    char cTetros_O[16] = {   ///< 1*4*4 = 16
      char(0), char(0), char(0), char(0),
      char(0), 'O', 'O', char(0),
      char(0), 'O', 'O', char(0),
      char(0), char(0), char(0), char(0)
    };
    m_oTetriminos[1].Initialize (4, 4, 1, cTetros_O);
    m_oTetriminos[1].ResetRotation ();
    m_sfTetriminos['O'] = sf::Texture ();
    m_sfTetriminos['O'].loadFromFile ("datas/graphics/sprites.png", sf::IntRect (32, 0, 16, 16));

    char cTetros_J[36] = {   ///< 4*3*3 = 36
      char(0), char(0), char(0),
      'J', 'J', 'J',
      char(0), char(0), 'J',

      char(0), 'J', char(0),
      char(0), 'J', char(0),
      'J', 'J', char(0),

      'J', char(0), char(0),
      'J', 'J', 'J',
      char(0), char(0), char(0),

      char(0), 'J', 'J',
      char(0), 'J', char(0),
      char(0), 'J', char(0)
    };
    m_oTetriminos[2].Initialize (3, 3, 4, cTetros_J);
    m_oTetriminos[2].ResetRotation ();
    m_sfTetriminos['J'] = sf::Texture ();
    m_sfTetriminos['J'].loadFromFile ("datas/graphics/sprites.png", sf::IntRect (48, 0, 16, 16));

    char cTetros_L[36] = {   ///< 4*3*3 = 36
      char(0), char(0), char(0),
      'L', 'L', 'L',
      'L', char(0), char(0),

      'L', 'L', char(0),
      char(0), 'L', char(0),
      char(0), 'L', char(0),

      char(0), char(0), 'L',
      'L', 'L', 'L',
      char(0), char(0), char(0),

      char(0), 'L', char(0),
      char(0), 'L', char(0),
      char(0), 'L', 'L'
    };
    m_oTetriminos[3].Initialize (3, 3, 4, cTetros_L);
    m_oTetriminos[3].ResetRotation ();
    m_sfTetriminos['L'] = sf::Texture ();
    m_sfTetriminos['L'].loadFromFile ("datas/graphics/sprites.png", sf::IntRect (64, 0, 16, 16));

    char cTetros_S[18] = {   ///< 2*3*3 = 18
      char(0), char(0), char(0),
      char(0), 'S', 'S',
      'S', 'S', char(0),

      'S', char(0), char(0),
      'S', 'S', char(0),
      char(0), 'S', char(0)
    };
    m_oTetriminos[4].Initialize (3, 3, 2, cTetros_S);
    m_oTetriminos[4].ResetRotation ();
    m_sfTetriminos['S'] = sf::Texture ();
    m_sfTetriminos['S'].loadFromFile ("datas/graphics/sprites.png", sf::IntRect (80, 0, 16, 16));

    char cTetros_Z[18] = {   ///< 2*3*3 = 18
      char(0), char(0), char(0),
      'Z', 'Z', char(0),
      char(0), 'Z', 'Z',

      char(0), 'Z', char(0),
      'Z', 'Z', char(0),
      'Z', char(0), char(0)
    };
    m_oTetriminos[5].Initialize (3, 3, 2, cTetros_Z);
    m_oTetriminos[5].ResetRotation ();
    m_sfTetriminos['Z'] = sf::Texture ();
    m_sfTetriminos['Z'].loadFromFile ("datas/graphics/sprites.png", sf::IntRect (96, 0, 16, 16));

    char cTetros_T[36] = {   ///< 4*3*3 = 36
      char(0), char(0), char(0),
      'T', 'T', 'T',
      char(0), 'T', char(0),

      char(0), 'T', char(0),
      'T', 'T', char(0),
      char(0), 'T', char(0),

      char(0), 'T', char(0),
      'T', 'T', 'T',
      char(0), char(0), char(0),

      char(0), 'T', char(0),
      char(0), 'T', 'T',
      char(0), 'T', char(0)
    };
    m_oTetriminos[6].Initialize (3, 3, 4, cTetros_T);
    m_oTetriminos[6].ResetRotation ();
    m_sfTetriminos['T'] = sf::Texture ();
    m_sfTetriminos['T'].loadFromFile ("datas/graphics/sprites.png", sf::IntRect (112, 0, 16, 16));

    m_bGotoNext = false;
    m_bCollapse = false;
    m_bFalling = true;
    m_bFallingSlow = false;
    m_bRotationRight = false;
    m_bRotationLeft = false;
    m_bMovingRight = false;
    m_bMovingLeft = false;
    m_bLockGame = false;
    m_bPause = false;

    // Initialise the time.
    m_sfElapsedTime = sf::seconds (0.f);
    m_uiFallTime = 0;

    // Initialise the score, level, etc...
    m_oScores.Initialize ();
    m_uiLinesCount = 0;
    m_uiSlowFallCellsCount = 0;
    m_uiFreeFallCellsCount = 0;

    // Generate the tetriminos.
    m_uiCurrentTetriminos = m_oScores.GetNextTetriminos ();
    m_oScores.GenerateNextTetriminos ();
    m_oTetriminos[m_uiCurrentTetriminos].SetPosition (sf::Vector2u (5, 0));
    m_bDisplayTetriminos = true;

    return true;
  }
  return false;
}

/* Get if the game is running. */
bool Game::IsRunning ( void ) {
  return m_bRunning;
}

/* Get if the game id sleeping. */
bool Game::IsSleeping ( sf::Clock &sfClock ) {
  m_sfElapsedTime = sfClock.getElapsedTime ();
  if (m_sfElapsedTime.asMilliseconds () > 20) {
    if (m_bFalling)
      m_uiFallTime += 20;
    sfClock.restart ();

    return false;
  }
  return true;
}

/* Event of the game. */
void Game::Events ( void ) {
  // Events
  while (m_sfWindow.pollEvent (m_sfEvent)) {
    // To stop the game.
    if (m_sfEvent.type == sf::Event::EventType::Closed) {
      m_bRunning = false;
    }
    if (m_sfEvent.type == sf::Event::EventType::KeyPressed) {
      if (m_sfEvent.key.code == sf::Keyboard::Key::Escape) {
        m_bRunning = false;
        m_bFalling = false;
      }
      if (!m_bLockGame) {
        if (m_sfEvent.key.code == sf::Keyboard::Key::R)
          m_bRotationRight = true;
        if (m_sfEvent.key.code == sf::Keyboard::Key::E)
          m_bRotationLeft = true;
        if (m_sfEvent.key.code == sf::Keyboard::Key::Right)
          m_bMovingRight = true;
        if (m_sfEvent.key.code == sf::Keyboard::Key::Left)
          m_bMovingLeft = true;
        if (m_sfEvent.key.code == sf::Keyboard::Key::P) {
          if (!m_bPause)
            m_bPause = true;
          else
            m_bPause = false;
        }
      }
    }
  }
  // Inputs
  if (!m_bLockGame) {
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down))
      m_bFallingSlow = true;
  }
}

/* Update the game. */
void Game::Update ( void ) {
  if (!m_bLockGame) {
    if (m_bGotoNext) {
      GoToNext ();
      if (!Collide ())
        m_bLockGame = true;
    }
    if (m_bCollapse) {
      m_uiDeleteLineTime += 20;
      if (m_uiDeleteLineTime == 200) {
        m_uiDeleteLineTime = 0;
        Collapse ();
      }
    }

    if (!m_bPause) {
      if (m_bFallingSlow && m_uiFallTime > 100) {
        m_uiFallTime = 0;
        m_oTetriminos[m_uiCurrentTetriminos].Fall (22);
        m_bFallingSlow = false;
        if (Collide ()) {
          m_oTetriminos[m_uiCurrentTetriminos].ApplyMove ();
          m_uiSlowFallCellsCount++;
        } else {
          m_oTetriminos[m_uiCurrentTetriminos].UndoMove ();
          PrintTetriminos ();
          DeleteLines ();
        }
      } else if (m_bFalling && m_uiFallTime > m_oScores.GetFallSpeed ()) {
        m_uiFallTime = 0;
        m_oTetriminos[m_uiCurrentTetriminos].Fall (22);
        if (Collide ()) {
          m_oTetriminos[m_uiCurrentTetriminos].ApplyMove ();
        } else {
          m_oTetriminos[m_uiCurrentTetriminos].UndoMove ();
          PrintTetriminos ();
          DeleteLines ();
        }
      }
      if (m_bMovingRight) {
        m_oTetriminos[m_uiCurrentTetriminos].MoveRight (12);
        m_bMovingRight = false;
        if (Collide ())
          m_oTetriminos[m_uiCurrentTetriminos].ApplyMove ();
        else
          m_oTetriminos[m_uiCurrentTetriminos].UndoMove ();
      }
      if (m_bMovingLeft) {
        m_oTetriminos[m_uiCurrentTetriminos].MoveLeft (1);
        m_bMovingLeft = false;
        if (Collide ())
          m_oTetriminos[m_uiCurrentTetriminos].ApplyMove ();
        else
          m_oTetriminos[m_uiCurrentTetriminos].UndoMove ();
      }
      if (m_bRotationRight) {
        m_oTetriminos[m_uiCurrentTetriminos].RotateRight ();
        m_bRotationRight = false;
        if (Collide ())
          m_oTetriminos[m_uiCurrentTetriminos].ApplyRotation ();
        else
          m_oTetriminos[m_uiCurrentTetriminos].UndoRotation ();
      }
      if (m_bRotationLeft) {
        m_oTetriminos[m_uiCurrentTetriminos].RotateLeft ();
        m_bRotationLeft = false;
        if (Collide ())
          m_oTetriminos[m_uiCurrentTetriminos].ApplyRotation ();
        else
          m_oTetriminos[m_uiCurrentTetriminos].UndoRotation ();
      }
    }
  }
}

/* Draw the game. */
void Game::Draw ( void ) {
  m_sfWindow.clear (sf::Color (10, 10, 10, 255));

  sf::Sprite sfBricks;
  sfBricks.setTexture (m_sfBricks);
  sf::Sprite sfBlocks;

  // Draw the score, level, etc...
  m_oScores.Draw (m_sfWindow);
  // Draw the next tetriminos.
  unsigned int uiNextTetriminos = m_oScores.GetNextTetriminos ();
  char cNextTetriminos;
  float fX = 0.f, fY = 0.f;

  for (unsigned int uiY = 0 ; uiY < m_oTetriminos[uiNextTetriminos].GetHeight () ; uiY++) {
    fX = 0.f;
    for (unsigned int uiX = 0 ; uiX < m_oTetriminos[uiNextTetriminos].GetWidth () ; uiX++) {
      cNextTetriminos = m_oTetriminos[uiNextTetriminos].GetValue (uiX, uiY);
      if (cNextTetriminos != char(0)) {
        sfBlocks.setTexture (m_sfTetriminos[cNextTetriminos]);
        sfBlocks.setPosition (240.f+fX, 240.f+fY);
        m_sfWindow.draw (sfBlocks);
      }
      fX += 16.f;
    }
    fY += 16.f;
  }

  // Draw the playfield.
  fX = 0.f, fY = 0.f;
  for (int iY = 2 ; iY < 22 ; iY++) {
    fX = 0.f;
    for (int iX = 0 ; iX < 13 ; iX++) {
      if (m_cPlayfield[iX][iY] == char(1)) {
        sfBricks.setPosition (fX, fY);
        m_sfWindow.draw (sfBricks);
      } else if (m_cPlayfield[iX][iY] != char(0)) {
        sfBlocks.setTexture (m_sfTetriminos[m_cPlayfield[iX][iY]]);
        sfBlocks.setPosition (fX, fY);
        m_sfWindow.draw (sfBlocks);
      }
      fX += 16.f;
    }
    fY += 16.f;
  }

  // Convert the grid position of the tetriminos to render position.
  sf::Vector2f vfPosition (
                            m_oTetriminos[m_uiCurrentTetriminos].GetPosition ().x*16.f,
                            m_oTetriminos[m_uiCurrentTetriminos].GetPosition ().y*16.f-32.f
                          );

  // Draw the tetriminos.
  if (m_bDisplayTetriminos) {
    char cCurrentTetriminos;
    fY = 0.f;
    for (unsigned int uiY = 0 ; uiY < m_oTetriminos[m_uiCurrentTetriminos].GetHeight () ; uiY++) {
      fX = 0.f;
      for (unsigned int uiX = 0 ; uiX < m_oTetriminos[m_uiCurrentTetriminos].GetWidth () ; uiX++) {
        cCurrentTetriminos = m_oTetriminos[m_uiCurrentTetriminos].GetValue (uiX, uiY);
        if (cCurrentTetriminos != char(0)) {
          sfBlocks.setTexture (m_sfTetriminos[cCurrentTetriminos]);
          sfBlocks.setPosition (vfPosition.x+fX, vfPosition.y+fY);
          m_sfWindow.draw (sfBlocks);
        }
        fX += 16.f;
      }
      fY += 16.f;
    }
  }

  m_sfWindow.display ();
}

/* Select the new tetriminos. */
void Game::SelectTetriminos ( void ) {
  m_oTetriminos[m_uiCurrentTetriminos].ResetRotation ();
  m_uiCurrentTetriminos = m_oScores.GetNextTetriminos ();
  m_oScores.GenerateNextTetriminos ();
}

/* Test the collision of the tetriminos. */
bool Game::Collide ( void ) {
  sf::Vector2u vuPosition = m_oTetriminos[m_uiCurrentTetriminos].GetNextPosition ();
  for (unsigned int uiY = 0 ; uiY < m_oTetriminos[m_uiCurrentTetriminos].GetHeight () ; uiY++)
    for (unsigned int uiX = 0 ; uiX < m_oTetriminos[m_uiCurrentTetriminos].GetWidth () ; uiX++) {
      if (m_cPlayfield[vuPosition.x+uiX][vuPosition.y+uiY] && m_oTetriminos[m_uiCurrentTetriminos].GetNextValue (uiX, uiY))
        return false;
    }
  return true;
}

/* Print the tetriminos on the playfield. */
void Game::PrintTetriminos ( void ) {
  char cCurrentTetriminos;

  sf::Vector2u vuPosition = m_oTetriminos[m_uiCurrentTetriminos].GetPosition ();
  for (unsigned int uiY = 0 ; uiY < m_oTetriminos[m_uiCurrentTetriminos].GetHeight () ; uiY++)
    for (unsigned int uiX = 0 ; uiX < m_oTetriminos[m_uiCurrentTetriminos].GetWidth () ; uiX++) {
      cCurrentTetriminos = m_oTetriminos[m_uiCurrentTetriminos].GetValue (uiX, uiY);
      if (cCurrentTetriminos != char(0)) {
        m_cPlayfield[vuPosition.x+uiX][vuPosition.y+uiY] = cCurrentTetriminos;
        m_uiCheckLine[vuPosition.y+uiY]++;
      }
    }
    m_bPause = true;
}

/* Change the tetriminos to the next. */
void Game::GoToNext ( void ) {
  if (m_uiLinesCount > 0) {
    m_oScores.CheckDeletedLines (m_uiLinesCount);
    if (m_uiLinesCount == 1)
      m_oScores.ComputeScore (Scores::Action::OneLine);
    else if (m_uiLinesCount == 2)
      m_oScores.ComputeScore (Scores::Action::TwoLines);
    else if (m_uiLinesCount == 3)
      m_oScores.ComputeScore (Scores::Action::ThreeLines);
    else if (m_uiLinesCount == 4)
      m_oScores.ComputeScore (Scores::Action::FourLines);
    m_uiLinesCount = 0;
  }
  if (m_uiSlowFallCellsCount > 0) {
    m_oScores.ComputeScore (Scores::Action::SlowFall, m_uiSlowFallCellsCount);
    m_uiSlowFallCellsCount = 0;
  }
  if (m_uiFreeFallCellsCount > 0) {
    m_oScores.ComputeScore (Scores::Action::FreeFall, m_uiFreeFallCellsCount);
    m_uiFreeFallCellsCount = 0;
  }
  SelectTetriminos ();
  m_oTetriminos[m_uiCurrentTetriminos].SetPosition (sf::Vector2u (5, 0));
  m_bDisplayTetriminos = true;
  m_bGotoNext = false;
  m_bPause = false;
}

/* Delete the complete lines. */
void Game::DeleteLines ( void ) {
  unsigned int uiTetriminosY = m_oTetriminos[m_uiCurrentTetriminos].GetPosition ().y;
  unsigned int uiTetriminosHeight = m_oTetriminos[m_uiCurrentTetriminos].GetHeight ();
  unsigned int m_uiLines[4] = { 0, 0, 0, 0 };

  // Eliminate the two first lines of the grid.
  unsigned int uiBegin;
  if (uiTetriminosY == 0) uiBegin = 2;
  else if (uiTetriminosY == 1) uiBegin = 1;
  else uiBegin = 0;
  // Detect the complete lines.
  for ( unsigned int uiY = uiBegin ; uiY < uiTetriminosHeight ; uiY++) {
    if (m_uiCheckLine[uiTetriminosY+uiY] == 10) {
      m_uiLines[uiY] = uiTetriminosY+uiY;
      m_uiLinesCount++;
    }
  }
  if (m_uiLinesCount > 0) {
    m_bCollapse = true;
  } else
    m_bGotoNext = true;
  // Deleting blocks effect.
  for ( unsigned int uiY = uiBegin ; uiY < uiTetriminosHeight ; uiY++) {
    for (unsigned int uiX = 2 ; uiX < 12 ; uiX++) {
      m_cPlayfield[uiX][m_uiLines[uiY]] = char(0);
      m_uiCheckLine[m_uiLines[uiY]] = 0;
    }
  }
  m_bDisplayTetriminos = false;
}

/* Collapse the blocks in the playfield. */
void Game::Collapse ( void ) {
  unsigned int uiY1 = 21;
  unsigned int uiY2 = uiY1-1;
  m_bCollapse = false;

  while ( uiY1 > 1 ) {
    if (m_uiCheckLine[uiY1] == 0) {
      // Search a full line.
      while ( uiY2 > 1 && m_uiCheckLine[uiY2] == 0 ) {
        uiY2--;
        if (uiY2 < 2) {
          m_bGotoNext = true;
          return;
        }
      }
      // Collapse the full lines.
      while ( uiY2 > 1 && m_uiCheckLine[uiY2] > 0 ) {
        for (unsigned int uiX = 2 ; uiX < 12 ; uiX++) {
          m_cPlayfield[uiX][uiY1] = m_cPlayfield[uiX][uiY2];
          m_cPlayfield[uiX][uiY2] = char(0);
        }
        m_uiCheckLine[uiY1] = m_uiCheckLine[uiY2];
        m_uiCheckLine[uiY2] = 0;
        uiY2--;
        uiY1--;
      }
    } else {
      uiY1--;
      uiY2--;
    }
  }
  m_bGotoNext = true;
}
