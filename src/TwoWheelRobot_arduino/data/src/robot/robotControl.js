import { globalState } from "../utils/states.js";
import { keyMapping } from "../utils/constants.js";
import { sendDataToRobot } from "./api.js";

export class RobotControl {
  constructor() {
    this.controlState = {
      up: false,
      down: false,
      left: false,
      right: false,
      start: false,
    };
    this.speedSlider = document.getElementById("speed-slider");
    this.speedValue = document.getElementById("speed-value");

    this.activeKeys = new Set();

    this.initControllsListener();
  }

  initControllsListener() {
    this.initSpeedControl();
    this.initKeyboardControls();
  }

  initSpeedControl() {
    this.speedSlider.addEventListener("input", (e) => {
      globalState.currentSpeed = e.target.value;
      this.speedValue.textContent = globalState.currentSpeed;
      console.log(this.speedValue.textContent);
      // sendDataToRobot({ type: "speed", value: globalState.currentSpeed });
    });
  }

  initKeyboardControls() {
    document.addEventListener("keydown", (e) => {
      const key = e.key.toLowerCase();
      if (!this.activeKeys.has(key)) {
        this.activeKeys.add(key);
        this.updateControlState();
      }
    });

    document.addEventListener("keyup", (e) => {
      const key = e.key.toLowerCase();
      if (this.activeKeys.has(key)) {
        this.activeKeys.delete(key);
        this.updateControlState();
      }
    });

    document.querySelectorAll(".control-btn").forEach((button) => {
      button.addEventListener("mousedown", () => {
        const command = button.id;
        const key = keyMapping[command];
        if (!this.activeKeys.has(key)) {
          this.activeKeys.add(key);
          this.updateControlState();
        }
      });

      button.addEventListener("mouseup", () => {
        const command = button.id;
        const key = keyMapping[command];
        if (this.activeKeys.has(key)) {
          this.activeKeys.delete(key);
          this.updateControlState();
        }
      });
    });
  }

  resetControlState() {
    this.controlState.up = false;
    this.controlState.down = false;
    this.controlState.left = false;
    this.controlState.right = false;
  }

  updateControlState() {
    const previousControlState = { ...this.controlState };
    this.resetControlState();

    if (!this.controlState.start) {
      this.activeKeys.forEach((key) => {
        if (key === " ") {
          this.controlState.start = !this.controlState.start;
          const startButton = document.querySelector("#start");
          if (startButton) {
            startButton.textContent = this.controlState.start ? "⏹" : "▶";
          }
          this.activeKeys.delete(" ");
        }
      });
      return;
    }
    console.log(this.activeKeys);
    this.activeKeys.forEach((key) => {
      switch (key) {
        case "w":
          this.controlState.up = true;
          globalState.robotPosition.y -= 10;
          break;
        case "s":
          this.controlState.down = true;
          globalState.robotPosition.y += 10;
          break;
        case "a":
          this.controlState.left = true;
          globalState.robotPosition.x -= 10;
          break;
        case "d":
          this.controlState.right = true;
          globalState.robotPosition.x += 10;
          break;
        case " ":
          this.controlState.start = !this.controlState.start;
          const startButton = document.querySelector("#start");
          if (startButton) {
            startButton.textContent = this.controlState.start ? "⏹" : "▶";
          }
          this.activeKeys.delete(" ");
          break;
        default:
          break;
      }
    });

    if (
      JSON.stringify(this.controlState) !== JSON.stringify(previousControlState)
    ) {
      console.log(this.controlState);
      // sendDataToRobot({ type: "control", state: { ...controlState } });
    }
  }
}
