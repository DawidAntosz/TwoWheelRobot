import { RobotView } from "../robot/robotView.js";

export class Map {
  constructor() {
    this.canvas = document.getElementById("robot-map");
    this.ctx = this.canvas.getContext("2d");
    this.width = this.canvas.width;
    this.height = this.canvas.height;
    this.gridSize = 20;
    this.robotView = new RobotView(this.ctx, this.width, this.height);
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

  render() {
    const { ctx, width, height } = this;
    ctx.clearRect(0, 0, width, height);
    this.drawGrid();
    this.drawAxes();
    this.robotView.updatePosition();
    this.robotView.drawRobot(ctx);
  }
}
