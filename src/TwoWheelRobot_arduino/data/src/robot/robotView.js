import { controlState, globalState } from "../utils/states.js";

export class RobotView {
  constructor(mapContext, mapWidth, mapHeight) {
    this.ctx = mapContext;

    // Image robot
    this.robotImage = new Image();
    this.robotImage.src = "../assets/robot.png";
    this.robotLoaded = false;
    this.robotImage.onload = () => {
      this.robotLoaded = true;
    };
    this.robotSize = 100;

    // Robot controlls
    this.lastUpdateTime = performance.now();
    this.robotPosition = {
      x: mapWidth / 2,
      y: mapWidth / 2,
      theta: -Math.PI / 2,
    };

    this.acceleration = 10;
    this.angularAcceleration = Math.PI / 2;
  }

  drawRobot(ctx) {
    if (!this.robotLoaded) return;

    const { x, y, theta } = this.robotPosition;

    this.ctx.save();
    this.ctx.translate(this.robotPosition.x, this.robotPosition.y);
    this.ctx.rotate(this.robotPosition.theta);
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
    const { up, down, left, right, start } = controlState;
    const maxSpeed = globalState.currentSpeed;

    if (start && maxSpeed != 0) {
      let { x, y, theta } = this.robotPosition;

      const currentTime = performance.now();
      const deltaTime = (currentTime - this.lastUpdateTime) / 100;
      this.lastUpdateTime = currentTime;

      let dv = 0;
      let w = 0;

      if (up) dv += this.acceleration * deltaTime;
      if (down) dv -= this.acceleration * deltaTime;

      if (left) w -= this.angularAcceleration * deltaTime;
      if (right) w += this.angularAcceleration * deltaTime;

      theta += w * deltaTime;

      x += dv * Math.cos(theta) * deltaTime;
      y += dv * Math.sin(theta) * deltaTime;

      this.robotPosition = { x, y, theta };
      console.log(`Position: (${x}, ${y}), Theta: ${theta}`);
    }
  }
}
