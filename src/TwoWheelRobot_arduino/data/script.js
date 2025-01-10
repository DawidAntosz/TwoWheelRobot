const speedSlider = document.getElementById("speed-slider");
const speedValue = document.getElementById("speed-value");
const canvas = document.getElementById("robot-map");
const ctx = canvas.getContext("2d");

const width = canvas.width;
const height = canvas.height;
const centerX = width / 2;
const centerY = height / 2;
let robotPosition = {
  x: centerX,
  y: centerY,
};
let currentSpeed = 0;

const activeKeys = new Set();
const controlState = {
  up: false,
  down: false,
  left: false,
  right: false,
  start: false,
};

function drawGrid() {
  const gridSize = 20;
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

function drawAxes() {
  ctx.strokeStyle = "#000";
  ctx.lineWidth = 1;
  ctx.beginPath();
  ctx.moveTo(0, centerY);
  ctx.lineTo(width, centerY);
  ctx.stroke();
  ctx.beginPath();
  ctx.moveTo(centerX, 0);
  ctx.lineTo(centerX, height);
  ctx.stroke();
}

function drawRobot() {
  const robotSize = 3;
  ctx.fillStyle = "red";
  ctx.beginPath();
  ctx.arc(robotPosition.x, robotPosition.y, robotSize, 0, 2 * Math.PI);
  ctx.fill();
}

function init() {
  ctx.clearRect(0, 0, width, height);
  drawGrid();
  drawAxes();
  drawRobot();
}

function updateMap() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  drawGrid();
  drawAxes();
  drawRobot();
}

// =============== Controls buttons

speedSlider.addEventListener("input", (e) => {
  currentSpeed = e.target.value;
  speedValue.textContent = currentSpeed;
  sendDataToRobot({ type: "speed", value: currentSpeed });
});

function resetControlState() {
  controlState.up = false;
  controlState.down = false;
  controlState.left = false;
  controlState.right = false;
}

function updateControlState() {
  const previousControlState = { ...controlState };

  resetControlState();
  console.log(activeKeys);
  activeKeys.forEach((key) => {
    switch (key) {
      case "w":
        controlState.up = true;
        robotPosition.y -= 10;
        break;
      case "s":
        controlState.down = true;
        robotPosition.y += 10;
        break;
      case "a":
        controlState.left = true;
        robotPosition.x -= 10;
        break;
      case "d":
        controlState.right = true;
        robotPosition.x += 10;
        break;
      case " ":
        controlState.start = !controlState.start;
        const startButton = document.querySelector("#start");
        if (startButton) {
          startButton.textContent = controlState.start ? "⏹" : "▶";
        }
        activeKeys.delete(" ");
        break;
      default:
        break;
    }
  });

  if (JSON.stringify(controlState) !== JSON.stringify(previousControlState)) {
    console.log(controlState);
    // sendDataToRobot({ type: "control", state: { ...controlState } });
  }
  updateMap();
}

document.addEventListener("keydown", (e) => {
  const key = e.key.toLowerCase();
  if (!activeKeys.has(key)) {
    activeKeys.add(key);
    updateControlState();
  }
});

document.addEventListener("keyup", (e) => {
  const key = e.key.toLowerCase();
  if (activeKeys.has(key)) {
    activeKeys.delete(key);
    updateControlState();
  }
});

document.querySelectorAll(".control-btn").forEach((button) => {
  const keyMapping = {
    up: "w",
    down: "s",
    left: "a",
    right: "d",
    start: " ",
  };

  button.addEventListener("mousedown", () => {
    const command = button.id;
    const key = keyMapping[command];
    if (!activeKeys.has(key)) {
      activeKeys.add(key);
      updateControlState();
    }
  });

  button.addEventListener("mouseup", () => {
    const command = button.id;
    const key = keyMapping[command];
    if (activeKeys.has(key)) {
      activeKeys.delete(key);
      updateControlState();
    }
  });
});

async function sendDataToRobot(data) {
  try {
    console.log("Wysyłanie danych:", data);
    const response = await fetch("/robot-control", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(data),
    });

    if (!response.ok) {
      console.error("Błąd podczas przesyłania danych:", response.status);
    }
  } catch (error) {
    console.error("Błąd połączenia z robotem:", error);
  }
}

init();
