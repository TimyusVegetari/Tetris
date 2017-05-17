#ifndef TETRIMINOS_HPP_
#define TETRIMINOS_HPP_

#include <includes.hpp>

/* Class to define the tetriminos. */
class Tetriminos {
  private:
    char**        m_cTetriminos;        ///< Set of rotated tetriminos.
    unsigned int  m_uiWidth;            ///< Width of the tetriminos grid.
    unsigned int  m_uiHeight;           ///< Height of the tetriminos grid.
    unsigned int  m_uiRotateCount;      ///< Number of possible rotations.
    unsigned int  m_uiCurrentRotation;  ///< Current rotation of the tetriminos.
    sf::Vector2u  m_vuPosition;         ///< Position of the tetriminos.
    unsigned int  m_uiNextRotation;     ///< Next rotation of the tetriminos.
    sf::Vector2u  m_vuNextPosition;     ///< Next position of the tetriminos.

  public:
    Tetriminos ( void );
    ~Tetriminos ( void );

    void Initialize ( unsigned int uiWidth, unsigned int uiHeight, unsigned int uiRotateCount, char cTetros[] );
    void ResetRotation ( void );
    void RotateRight ( void );
    void RotateLeft ( void );
    unsigned int GetWidth ( void );
    unsigned int GetHeight ( void );
    char GetValue ( unsigned int uiX, unsigned int uiY );
    char GetNextValue ( unsigned int uiX, unsigned int uiY );
    void SetPosition ( sf::Vector2u vuPosition );
    sf::Vector2u GetPosition ( void );
    sf::Vector2u GetNextPosition ( void );
    void MoveRight ( unsigned int uiRightWall );
    void MoveLeft ( unsigned int uiLeftWall );
    void Fall ( unsigned int uiBottom );
    void ApplyMove ( void );
    void UndoMove ( void );
    void ApplyRotation ( void );
    void UndoRotation ( void );
};

#endif // TETRIMINOS_HPP_
