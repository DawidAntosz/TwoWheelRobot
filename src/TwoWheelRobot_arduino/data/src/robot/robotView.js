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
    this.offsetX = -29;
    this.offsetY = 0;

    // Robot controlls
    this.lastUpdateTime = performance.now();
    this.robotPosition = {
      x: mapWidth / 2,
      y: mapWidth / 2,
      theta: -Math.PI / 2,
    };

    this.acceleration = 100;
    this.angularAcceleration = Math.PI / 10;

    this.velocity = 0;
    this.angularVelocity;
    this.wheelRadius = 0.02;
    this.wheelbase = 0.1;
  }

  drawRobot(ctx) {
    if (!this.robotLoaded) return;
    const { x, y, theta } = this.robotPosition;
    this.ctx.save();
    this.ctx.translate(x, y);
    this.ctx.rotate(this.robotPosition.theta);
    this.ctx.drawImage(
      this.robotImage,
      -this.robotSize / 2 - this.offsetX,
      -this.robotSize / 2 - this.offsetY,
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

      let wMax = maxSpeed / this.wheelBase;

      if (up && !down) {
        this.velocity += this.acceleration * deltaTime;
      } else if (down && !up) {
        this.velocity -= this.acceleration * deltaTime;
      } else {
        this.velocity = 0;
      }
      this.velocity = Math.max(Math.min(this.velocity, maxSpeed), -maxSpeed);

      if (left && !right) {
        this.angularVelocity -= this.angularAcceleration * deltaTime;
      } else if (right && !left) {
        this.angularVelocity += this.angularAcceleration * deltaTime;
      } else {
        this.angularVelocity = 0;
      }

      theta += this.angularVelocity * deltaTime;
      theta = ((theta % (2 * Math.PI)) + 2 * Math.PI) % (2 * Math.PI);
      console.log(theta);
      x += this.velocity * Math.cos(theta) * deltaTime;
      y += this.velocity * Math.sin(theta) * deltaTime;
      this.robotPosition = { x, y, theta };
    }
  }
}
