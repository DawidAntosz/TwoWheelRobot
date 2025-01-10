export class RobotUI {
  constructor() {
    this.updateRobotPanel = this.updateRobotPanel.bind(this);
  }

  updateRobotPanel(data) {
    document.getElementById("left-speed").textContent = data.leftSpeed || 0;
    document.getElementById("left-distance").textContent =
      data.leftDistance || 0;
    document.getElementById("right-speed").textContent = data.rightSpeed || 0;
    document.getElementById("right-distance").textContent =
      data.rightDistance || 0;
    document.getElementById("current-x").textContent = data.currentX || 0;
    document.getElementById("current-y").textContent = data.currentY || 0;
    document.getElementById("current-theta").textContent =
      data.currentTheta || 0;
  }
}
