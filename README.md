# Update March 2018

This code was written in 2003 for the CD-ROM that accompanied the book AI Game Programming Wisdom 2: http://www.aiwisdom.com/resource_aiwisdom2.html. 

It's the companion to the article Intelligent Steering Using PID Controllers. 

---

## Requirements

This sample requires Windows XP to run, and MS VC.Net 2003 to compile

## Troubleshooting

- On some versions of Windows XP, the program will exit as soon as it's started, and will assert inside MFC code if run in debug mode. To fix this, open a DOS prompt, go to this directory, and type "regsvr32 COMCTL32.OCX" 

## Usage notes

- If you choose to steer the missile using the keyboard, use 8 key on the numpad to accelerate, and use 4 and 6 to steer left and right. Hopefully, you will discover that the missile is actually quite difficult to control.

- Click on the "?" buttons next to the P, I, and D sliders for a brief description of their functions.

- Try setting the P, I, and D values to 1.0, 0.0, and 0.0 respectively. This represents implementing the naive solution of having the missile's steering hooked directly to the direction it wants to be going. Notice how the missile tends to overshoot the target.

- Click on the Reset button to reset all of the sliders to their default values.

- Click on the Pause button to pause the demo if you want to change the value of several sliders at once.

## Files in this project

`CPidController.hpp`, `CPidController.h`:   
    Implements a PID controller. Used to steer the missile.

`CMissile.cpp`, `CMissile.h`:
    Implements the missile.

`CTarget.cpp`, `CTarget.h`:
    Implements the target of the missile.

`CWorld.cpp`, `CWorld.h`:
    Implements the world containing a missile and its target.

`CVector2.cpp`, `CVector2.h`:
    Simple 2D vector class.

`GlView.cpp`, `GlView.h`:
    Implements an OpenGL viewport.

`Texture.cpp`, `Texture.h`:
    Implements an OpenGL texture.   

`picture.cpp`, `picture.h`, `slider.cpp`, `slider.h`:
    Files created by Visual Studio for using the Microsoft Slider Control.

`Textures\`
    Contains all of the textures used in the demo.

`ACKNOWLEDGEMENTS.md`:
    List of people who contributed to this demo.
