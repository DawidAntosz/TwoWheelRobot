import { globalState } from "../utils/states.js";

export class Map {
  constructor() {
    this.canvas = document.getElementById("robot-map");
    this.ctx = this.canvas.getContext("2d");
    this.width = this.canvas.width;
    this.height = this.canvas.height;
    this.gridSize = 20;
    this.robotSize = 3;
    globalState.robotPosition = { x: this.width / 2, y: this.height / 2 };
  }

  drawGrid() {
    const { ctx, width, height, gridSize } = this;
    ctx.strokeStyle = "#ddd";
    ctx.lineWidth = 0.5;
    for (let x = 0; x <= width; x += gridSize) {
      ctx.beginPath();
      ctx.moveTo(x, 0);
      ctx.lineTo(x, height);
      ctx.stroke();
    }
    for (let y = 0; y <= height; y += gridSize) {
      ctx.beginPath();
      ctx.moveTo(0, y);
      ctx.lineTo(width, y);
      ctx.stroke();
    }
  }

  drawAxes() {
    const { ctx, width, height } = this;
    ctx.strokeStyle = "#000";
    ctx.lineWidth = 1;
    const centerX = width / 2;
    const centerY = height / 2;
    ctx.beginPath();
    ctx.moveTo(0, centerY);
    ctx.lineTo(width, centerY);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(centerX, 0);
    ctx.lineTo(centerX, height);
    ctx.stroke();
  }

  drawRobot() {
    const { robotPosition } = globalState;
    const { ctx } = this;
    ctx.fillStyle = "red";
    // console.log(robotPosition);
    ctx.beginPath();
    ctx.arc(robotPosition.x, robotPosition.y, this.robotSize, 0, 2 * Math.PI);
    ctx.fill();
  }

  render() {
    const { ctx, width, height } = this;
    ctx.clearRect(0, 0, width, height);
    this.drawGrid();
    this.drawAxes();
    this.drawRobot();
  }
}
