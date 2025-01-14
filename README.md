# TwoWheelRobot
Differential wheeled robot

This project is focused on building a two-wheel differential robot with the ability to control and navigate in area.

## Project Structure
The project is organized into the following directories:

- `src/`: Contains the source code for the project.
  - `arduino/`: Source code using the Arduino framework (PlatformIO).
  - `esp_rtos_sdk/`: (For future development of the project using the ESP8266 RTOS SDK).


##### Control page:

![obraz](https://github.com/user-attachments/assets/38fbeb17-e8d2-4559-942d-c8bff26c4116)


##### Robot V1:

![obraz](https://github.com/user-attachments/assets/38b9f7e8-5eff-4320-b6f4-4259ef2db660)


##### Math model

![obraz](https://github.com/user-attachments/assets/35ea4db8-ad05-4e44-a2db-79f5267f586a)


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
