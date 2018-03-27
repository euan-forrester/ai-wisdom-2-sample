//
// Our missile. It has 2 control modes: either keyboard or PID controller. 
//
// The desired forward and angular accelerations from the keyboard are passed 
// into SetUserDesiredAcceleration() and SetUserDesiredAngularAcceleration() every 
// timestep. They're either used to set the missile's actual accelerations, or ignored,
// depending on the missile's current control mode.
//


#ifndef CMISSILE_H
#define CMISSILE_H

#include "CVector2.h"
#include "Texture.h"
#include "CPidController.h"

class CGlView;
class CWorld;
class CTarget;

// Possible control modes for our missile
enum eMissileControlMode
{
    eMISSILE_CONTROL_PID = 0,
    eMISSILE_CONTROL_KEYBOARD,

    NUM_MISSILE_CONTROL_MODES,
};

// Possible textures to use to draw our missile
enum eMissileTexture
{
    eMISSILE_TEXTURE_NO_FLAME = 0,
    eMISSILE_TEXTURE_FLAME_1,
    eMISSILE_TEXTURE_FLAME_2,
    eMISSILE_TEXTURE_FLAME_3,
    eMISSILE_TEXTURE_EXPLOSION,

    NUM_MISSILE_TEXTURES,
};

// Possible states our missile can be in
enum eMissileState
{
    eMISSILE_STATE_FLYING = 0,
    eMISSILE_STATE_EXPLODING,
    eMISSILE_STATE_FINISHED_EXPLODING,

    NUM_MISSILE_STATES,
};

class CMissile
{
public:
    CMissile()          { Init(); Reset(); }
    ~CMissile()         { }

    void                Init();
    void                Reset();
    void                SetCurrentWorld(CWorld *current_world)                  { m_pCurrentWorld = current_world; }
                        
    void                SetControlMode(eMissileControlMode new_control_mode)    { m_ControlMode = new_control_mode; }
    void                SetTarget(CTarget *new_target)                          { m_pTarget = new_target; }
        
    void                SetSteeringPIDCoefficients(float new_p, float new_i, float new_d)   { m_SteeringPidController.SetCoefficients(new_p, new_i, new_d); }

    void                SetUserDesiredAcceleration(float acceleration)                  { m_UserDesiredAcceleration         = acceleration; }
    void                SetUserDesiredAngularAcceleration(float angular_acceleration)   { m_UserDesiredAngularAcceleration  = angular_acceleration; }
    
    void                Steer(float timestep);
    void                Move(float timestep);
    void                CheckCollisionWithTarget();
    
    void                SetPosition(float new_position_x, float new_position_y) { m_Position.x = new_position_x; m_Position.y = new_position_y; }
    void                SetPosition(CVector2 *new_position)                     { m_Position = *new_position; }
    CVector2*           GetPosition()                                           { return &m_Position; }

    bool                NeedToBeReset()                                         { return (m_CurrentState == eMISSILE_STATE_FINISHED_EXPLODING); }
    eMissileState       GetCurrentState()                                       { return m_CurrentState; }

    CVector2*           GetDirection()                                          { return &m_Direction; }
    float               GetAngle()                                              { return m_Direction.GetAngle(); }
                        
    void                SetTexture(const char *filename, int index, int width, int height, int bit_depth);
    CTexture*           GetTexture(int index)                                   { return &m_Texture[index]; }
                        
    float               GetHeight();
    float               GetWidth();
    float               GetMaxAngularAcceleration();
    
    void                SetMaxAcceleration(float max_acceleration)              { m_MaxAcceleration = max_acceleration; }
    float               GetMaxAcceleration()                                    { return m_MaxAcceleration; }
                        
    int                 Draw(CGlView *gl_view); 
                        
    void                DumpState();
                    
private:
    float               GetNumSecondsToExplode();

    void                SetAcceleration(float acceleration)                     { m_Acceleration        = acceleration; }
    void                SetAngularAcceleration(float angular_acceleration)      { m_AngularAcceleration = angular_acceleration; }
    
    eMissileControlMode m_ControlMode;                      // Our current control mode (PID or keyboard)
    eMissileState       m_CurrentState;                     // Our current state (flying, exploding, or finished exploding)

    float               m_UserDesiredAcceleration;          // Acceleration forward that the user at the keyboard would like us to have. Will be ignored if in PID control mode
    float               m_UserDesiredAngularAcceleration;   // Angular acceleration that the user at the keyboard would like us to have. Will be ignored if in PID control mode

    float               m_Acceleration;                     // Current acceleration forward in distance/s^2
    float               m_AngularAcceleration;              // Current angular accleration in degrees/s^2
    float               m_MaxAcceleration;                  // Maximum acceleration allowed in world units/s^2
                                                            
    CVector2            m_Position;                         // Current position of the missile
    float               m_Speed;                            // Current speed of the missile (always in the direction of m_Direction)
    CVector2            m_Direction;                        // Current direction the missile is facing
    float               m_AngularVelocity;                  // Current rate of change of m_Direction in degrees/second. +ve for counterclockwise, -ve for clockwise
                    
    float               m_ExplosionTimeLeft;                // If m_CurrentState is eMISSILE_STATE_EXPLODING, how many seconds are left before we're finished exploding?

    CPidController      m_SteeringPidController;            // Our PID controller for steering
                        
    CTexture            m_Texture[NUM_MISSILE_TEXTURES];    // Texture to use when drawing this missile
                        
    CWorld*             m_pCurrentWorld;                    // World that we reside in
    CTarget*            m_pTarget;                          // The target that we're trying to hit
};

#endif