# Why not ?

Welcome to my custom Hackpad project. "Why not" is a 5 key macropad featuring a Rotary Encoder, an OLED screen, and 2 WS2812B Leds.

##  Features
- **Controller:** Seeed Studio XIAO RP2040
- **Layout:** 5 Physical Mechanical Switches + 1 Integrated Rotary Encoder Press 
- **Display:** 0.91" I2C OLED Screen 
- **RGB Lighting:** SK6812MINI-E Reverse-Mount LEDs
- **Enclosure:** Custom 3D-printable Top Layer designed in Onshape 
##  QMK Firmware 
This Hackpad used QMK Firmware- but certain changes might be make afterwards !
1. **Character Mode (SW1):** Pressing the first switch dynamically changes the OLED state to wake up an animated character.
2. **Timer Mode (SW2):** Features an onboard tracking stopwatch that can be toggled on/off.
3. **Smart Menu Navigation (SW3 & SW4):** Use these dedicated directional switches to navigate Left/Right or Up/Down through the main menu.
4. **Settings Menu (SW5):** Quickly jumps back to the Main Menu overlay.
5. **Interactive Double-Click Detection:** Double-clicking the **Rotary Encoder Press (SW6/D7)** inside the Time or Date screen unlocks the editing state, allowing you to turn the knob to dynamically adjust clock values and day constraints.

## PCB
Here is my pcb ! It is made in Kicad.
-schmetic
<img width="952" height="615" alt="image" src="https://github.com/user-attachments/assets/b3579127-eba9-403e-b1eb-19fd22ca2a33" />

-routing
<img width="749" height="541" alt="image" src="https://github.com/user-attachments/assets/8b9c514f-1289-420f-9654-ccddca55106b" />

## Case
I have used Onshape for my case. It is a simple sanwich case with hole made for type c on the right.
<img width="1060" height="506" alt="image" src="https://github.com/user-attachments/assets/6576bbfb-668c-40e6-b82b-978f20894aec" />


## BOM
-Here are things you need to make "Why not?" !!!
-**1x Unsoldered Seeed Studio XIAO RP2040**
-**5x MX-Style Mechanical Switches**
-**1x EC11 Rotary Encoder**
-**1x 0.91-inch OLED Display** 
-**2x SK6812 MINI-E LEDs** 
-**5x White Blank DSA Keycaps**
-**4x M3x16mm Screws**
-**4x M3x5mmx4mm Heatset Brass Inserts**
