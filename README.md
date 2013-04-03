tetris
======

"first" small project to improve my programming skills 

file "field.h" contains class Field, which keeps information about figures that have fallen down on the bottom of the screen; can delete full rows.
file "form.h" contains base abstract class Form, which is used to simulate behaviour of objects of seven derived classes (Cube, Stick, ZetL, ZetR, GamaL, GamaR, Triangle) via polimorphic architecture.
file "manager.h" contains class Manager, which simulates the game Tetris. Because this realization is a console application, gameplay is awful, but the main goal was to train in OOD. From this point of view class Manager doesn't have the best realization, but it works :)

class Cube corresponds to figure
**
**
class Triangle corresponds to figure
 * 
***
class Stick corresponds to figure
****
class ZetL corresponds to figure
**
 **
class ZetR corresponds to figure
 **
**
class GamaL corresponds to figure
*
***
class GamaR corresponds to figure
  *
***
