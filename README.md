# TwoWheelRobot
Differential wheeled robot

This project is focused on building a two-wheel differential robot with the ability to control and navigate in area.

## Project Structure
The project is organized into the following directories:

- `src/`: Contains the source code for the project.
  - `arduino/`: Source code using the Arduino framework (PlatformIO).
  - `esp_rtos_sdk/`: (For future development of the project using the ESP8266 RTOS SDK).


##### Control page:
<p align="center">
<!--   <img src="https://github.com/user-attachments/assets/38fbeb17-e8d2-4559-942d-c8bff26c4116" width="600" />  -->
  <img src="https://github.com/user-attachments/assets/2f06915f-ba95-41ab-ba28-fcc3190b7068" width="600" /> 
<!--   <img src="" width="600" />  -->
</p>


##### Robot V1:

![obraz](https://github.com/user-attachments/assets/38b9f7e8-5eff-4320-b6f4-4259ef2db660)


##### Math model
<p align="center">
  <img src="https://github.com/user-attachments/assets/ae9696d6-e501-4e7d-8e18-3af48c804a24" width="400" /> 

</p>

$$
\dot{x} = \frac{R}{2}(v_r + v_\ell)\cos\phi
$$
$$
\dot{y} = \frac{R}{2}(v_r + v_\ell)\sin\phi
$$
$$
\dot{\phi} = \frac{R}{L}(v_r - v_\ell)
$$

$$
\dot{x} = v\cos\phi
$$
$$
\dot{y} = v\sin\phi
$$
$$
\dot{\phi} = \omega
$$

$$
v = \frac{R}{2}(v_r + v_\ell) \implies \frac{2v}{R} = v_r + v_\ell
$$

$$
\omega = \frac{R}{L}(v_r - v_\ell) \implies \frac{\omega L}{R} = v_r - v_\ell
$$

$$
\ v_r = \\frac{2v + \\omega L}{2R} \\\ 
$$
$$
 v_l = \\frac{2v - \\omega L}{2R} \
$$

Description parameters:
- \( v_r \): the speed of the right wheel
- \( v_\ell \): the speed of the left wheel
- \( R \): the radius of the wheel
- \( L \): the distance between the wheels
- \( $$\omega$$ \): the angular velocity of the robot
