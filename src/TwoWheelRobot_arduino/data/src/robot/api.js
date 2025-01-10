export async function sendDataToRobot(data) {
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

export async function updateRobotInfo() {
  try {
    const response = await fetch("/robot-status", {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
      },
    });

    if (!response.ok) {
      console.error("Błąd podczas odbierania danych:", response.status);
      return;
    }

    const data = await response.json();
    console.log("Otrzymane dane:", data);

    updateRobotPanel(data);
  } catch (error) {
    console.error("Błąd połączenia z robotem:", error);
  }
}
