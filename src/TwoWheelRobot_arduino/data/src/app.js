import { Map } from "./map/map.js";
import { RobotControl } from "./robot/robotControl.js";

const map = new Map();
const robotControl = new RobotControl();

function mainLoop() {
  map.render();
  requestAnimationFrame(mainLoop);
}

mainLoop();
