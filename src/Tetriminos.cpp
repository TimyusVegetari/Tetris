#include <Tetriminos.hpp>

/* Constructor */
Tetriminos::Tetriminos ( void ) :
  m_cTetriminos       (NULL),
  m_uiWidth           (0),
  m_uiHeight          (0),
  m_uiRotateCount     (0),
  m_uiCurrentRotation (0)
{
}

/* Destructor */
Tetriminos::~Tetriminos ( void ) {
  if (m_cTetriminos != NULL) {
    for (unsigned int uiR = 0 ; uiR < m_uiRotateCount ; uiR++) {
      delete[] m_cTetriminos[uiR];
    }
    delete[] m_cTetriminos;
  }
}

/* Initialise the tetriminos and its components. */
void Tetriminos::Initialize ( unsigned int uiWidth, unsigned int uiHeight, unsigned int uiRotateCount, char cTetros[] ) {
  m_uiWidth = uiWidth;
  m_uiHeight = uiHeight;
  m_uiRotateCount = uiRotateCount;

  unsigned int uiSurface = uiHeight*m_uiWidth;
  unsigned int uiCurrentRotation = 0;

  m_cTetriminos = new char*[uiRotateCount];
  for (unsigned int uiR = 0 ; uiR < uiRotateCount ; uiR++) {
    m_cTetriminos[uiR] = new char[uiSurface];
    for (unsigned int uiY = 0 ; uiY < uiSurface ; uiY += m_uiWidth)
      for (unsigned int uiX = 0 ; uiX < uiWidth ; uiX++)
        m_cTetriminos[uiR][uiY+uiX] = cTetros[uiCurrentRotation+uiY+uiX];
    uiCurrentRotation += uiSurface;
  }

  SetPosition (sf::Vector2u (0, 0));
}

/* Reset the rotation of the tetriminos. */
void Tetriminos::ResetRotation ( void ) {
  m_uiCurrentRotation = 0;
  m_uiNextRotation = 0;
}

/* Rotate the tetriminos to the right. */
void Tetriminos::RotateRight ( void ) {
  if (m_uiCurrentRotation == m_uiRotateCount-1)
    m_uiNextRotation = 0;
  else
    m_uiNextRotation = m_uiCurrentRotation+1;
}

/* Rotate the tetriminos to the left. */
void Tetriminos::RotateLeft ( void ) {
  if (m_uiCurrentRotation == 0)
    m_uiNextRotation = m_uiRotateCount-1;
  else
    m_uiNextRotation = m_uiCurrentRotation-1;
}

/* Get the width of the tetriminos. */
unsigned int Tetriminos::GetWidth ( void ) {
  return m_uiWidth;
}

/* Get the height of the tetriminos. */
unsigned int Tetriminos::GetHeight ( void ) {
  return m_uiHeight;
}

/* Get the value in a block. */
char Tetriminos::GetValue ( unsigned int uiX, unsigned int uiY ) {
  return m_cTetriminos[m_uiCurrentRotation][uiY*m_uiWidth+uiX];
}

/* Get the next value in a block. */
char Tetriminos::GetNextValue ( unsigned int uiX, unsigned int uiY ) {
  return m_cTetriminos[m_uiNextRotation][uiY*m_uiWidth+uiX];
}

/* Set the position of the tetriminos. */
void Tetriminos::SetPosition ( sf::Vector2u vuPosition ) {
  m_vuPosition = vuPosition;
  m_vuNextPosition = vuPosition;
}

/* Get the position of the tetriminos. */
sf::Vector2u Tetriminos::GetPosition ( void ) {
  return m_vuPosition;
}

/* Get the next position of the tetriminos. */
sf::Vector2u Tetriminos::GetNextPosition ( void ) {
  return m_vuNextPosition;
}

/* Move the tetriminos to the right. */
void Tetriminos::MoveRight ( unsigned int uiRightWall ) {
  if (m_vuPosition.x+m_uiWidth-2 < uiRightWall)
    m_vuNextPosition.x = m_vuPosition.x+1;
}

/* Move the tetriminos to the left. */
void Tetriminos::MoveLeft ( unsigned int uiLeftWall ) {
  if (m_vuPosition.x > uiLeftWall)
    m_vuNextPosition.x = m_vuPosition.x-1;
}

/* Fall the tetriminos. */
void Tetriminos::Fall ( unsigned int uiBottom ) {
  if (m_vuPosition.y+m_uiHeight-2 < uiBottom)
    m_vuNextPosition.y = m_vuPosition.y+1;
}

/* Apply the movement. */
void Tetriminos::ApplyMove ( void ) {
  m_vuPosition = m_vuNextPosition;
}

/* Undo the next position. */
void Tetriminos::UndoMove ( void ) {
  m_vuNextPosition = m_vuPosition;
}

/* Apply the rotation. */
void Tetriminos::ApplyRotation ( void ) {
  m_uiCurrentRotation = m_uiNextRotation;
}

/* Undo the rotation. */
void Tetriminos::UndoRotation ( void ) {
  m_uiNextRotation = m_uiCurrentRotation;
}
