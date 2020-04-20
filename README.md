This code was written in 2003 for the CD-ROM that accompanied the book AI Game Programming Wisdom 2: http://www.aiwisdom.com/resource_aiwisdom2.html. 

It's the companion to the article Intelligent Steering Using PID Controllers. 

A more advanced, self-tuning, version of this same demo can be found here: https://github.com/euan-forrester/ai-wisdom-3-sample

## Some GIFs

#### Standard settings

![The demo with standard settings](/images/settings-standard.gif)

When you first start the demo, it opens with a missile chasing a target. The target moves about randomly (or can be controlled with the keyboard), and the missile tries to follow it. The PID controller steering the missile is initialized with tuning values that make it track the target reasonably well.

### The P term

![Setting the PID values to 1, 0, 0](/images/settings-p1.gif)

If we try changing the tuning values to P = 1, I = 0, and D = 0 we can see the effects of the naive solution of having the missile constantly steering towards the target. Note that the angular momentum of the missile makes it overshoot the target.

![Explanation of the P term](/images/p-explanation.png)

Clicking on the ? beside the P term gives us this explanation.

### The I term

![Setting the PID values to 0, 1, 0](/images/settings-i1.gif)

We can further explore the tuning values by setting P = 0, I = 1, and D = 0. Here we see the missile overshooting the target even more.

![Explanation of the I term](/images/i-explanation.png)

And the demo gives us this explanation of the I term.

### The D term

![Setting the PID values to 0, 0, 1](/images/settings-d1.gif)

Lastly we can explore the final term by setting P = 0, I = 0, and D = 1. Since the D term is for damping the missile's turning, we see the missile behaving pretty erratically when it's used alone. Note that I had to manually control the target so I could eventually steer it into the missile otherwise they may have taken a long time to collide.

![Explanation of the D term](/images/d-explanation.png)

Here's the demo's explanation for the D term.

## Running the demo

### Requirements

This sample runs on Windows, and can run on Windows 10: see the Releases tab for more info and to download the executable. 

I haven't tried compiling it in a long time! But at the time I used MS VC.Net 2003.

### Usage notes

- If you choose to steer the missile using the keyboard, use 8 key on the numpad to accelerate, and use 4 and 6 to steer left and right. Hopefully, you will discover that the missile is actually quite difficult to control.

- Click on the "?" buttons next to the P, I, and D sliders for a brief description of their functions.

- Try setting the P, I, and D values to 1.0, 0.0, and 0.0 respectively. This represents implementing the naive solution of having the missile's steering hooked directly to the direction it wants to be going. Notice how the missile tends to overshoot the target.

- Click on the Reset button to reset all of the sliders to their default values.

- Click on the Pause button to pause the demo if you want to change the value of several sliders at once.

## Files in this project

`CPidController.hpp`, `CPidController.h`: Implements a PID controller. Used to steer the missile.

`CMissile.cpp`, `CMissile.h`: Implements the missile.

`CTarget.cpp`, `CTarget.h`: Implements the target of the missile.

`CWorld.cpp`, `CWorld.h`: Implements the world containing a missile and its target.

`CVector2.cpp`, `CVector2.h`: Simple 2D vector class.

`GlView.cpp`, `GlView.h`: Implements an OpenGL viewport.

`Texture.cpp`, `Texture.h`: Implements an OpenGL texture.   

`picture.cpp`, `picture.h`, `slider.cpp`, `slider.h`: Files created by Visual Studio for using the Microsoft Slider Control.

`Textures\`: Contains all of the textures used in the demo.

`ACKNOWLEDGEMENTS.md`: List of people who contributed to this demo.

`images\`: Contains the images used in this readme file
