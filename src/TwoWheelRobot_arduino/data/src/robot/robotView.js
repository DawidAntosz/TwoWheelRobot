import { globalState, controlState } from "../utils/states.js";

export class RobotView {
  constructor(mapContext) {
    this.ctx = mapContext;
    this.robotImage = new Image();
    this.robotImage.src = "../assets/robot.png";
    this.robotLoaded = false;
    this.robotImage.onload = () => {
      this.robotLoaded = true;
    };
    this.robotSize = 100;
    this.lastUpdateTime = performance.now();
    globalState.robotPosition = { x: this.width / 2, y: this.height / 2 };
  }

  drawRobot(ctx) {
    if (!this.robotLoaded) return;

    const { x, y, theta } = globalState.robotPosition;

    this.ctx.save();
    this.ctx.translate(
      globalState.robotPosition.x,
      globalState.robotPosition.y
    );
    this.ctx.rotate(globalState.robotPosition.theta);
    this.ctx.drawImage(
      this.robotImage,
      -this.robotSize / 2,
      -this.robotSize / 2,
      this.robotSize,
      this.robotSize
    );
    this.ctx.restore();
  }

  updatePosition() {
    const currentTime = performance.now();
    const deltaTime = (currentTime - this.lastUpdateTime) / 1000;
    this.lastUpdateTime = currentTime;

    const { up, down, left, right } = controlState;
    const acceleration = 1;
    const angularVelocity = Math.PI / 10;

    let { x, y, theta } = globalState.robotPosition;
    let v = globalState.currentSpeed; // Aktualna prędkość
    let w = 0;

    if (up) v += acceleration * deltaTime; // Wolniejsze przyspieszanie
    if (down) v -= acceleration * deltaTime; // Wolniejsze hamowanie
    if (left) w += angularVelocity * deltaTime; // Powolna rotacja w lewo
    if (right) w -= angularVelocity * deltaTime; // Powolna rotacja w prawo

    if (w > Math.PI / 2) w = Math.PI / 2;
    if (w < -Math.PI / 2) w = -Math.PI / 2;

    theta += w * deltaTime;
    x += v * Math.cos(theta) * deltaTime;
    y += v * Math.sin(theta) * deltaTime;
    globalState.robotPosition = { x: 200, y: 200, theta: Math.PI / 4 };
    // Aktualizacja stanu globalnego
    // globalState.robotPosition = { x, y, theta };
    // globalState.currentSpeed = v;

    // console.log(`Position: (${x}, ${y}), Theta: ${theta}`);
    // console.log(`deltaTime: ${deltaTime}`);
  }
}
