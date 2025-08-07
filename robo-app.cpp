// #include <WiFi.h>
// #include <WebServer.h>

// // Create web server on port 80
// WebServer server(80);

// // Motor driver pins (L298N or similar)
// const int leftMotorPin1 = 21;  // IO21 //in1
// const int leftMotorPin2 = 4;   // IO4//in2
// const int leftMotorENA  = 18;   // IO5 (PWM)ena

// // Right Motor
// const int rightMotorPin1 = 22; // IO 22//in3
// const int rightMotorPin2 = 23; // IO23//in4
// const int rightMotorENB  = 5; // IO18 (PWM)//enb

// // LED pin for status indication
// const int statusLED = 2;

// // Speed control variables
// int currentSpeed = 255;
// String currentState = "S";
// bool motorsEnabled = true;

// // WiFi AP credentials
// const char* ssid = "TasminaDon";
// const char* password = "12345678";

// int getSpeedFromState(String state) {
//   if (state == "0") return 90;
//   if (state == "1") return 130;
//   if (state == "2") return 150;
//   if (state == "3") return 170;
//   if (state == "4") return 190;
//   if (state == "5") return 200;
//   if (state == "6") return 220;
//   if (state == "7") return 240;
//   if (state == "9") return 254;
//   if (state == "q") return 255;
//   return 255;
// }

// // Enhanced HTML page with racing interface
// const char htmlPage[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html>
// <head>
// <meta charset="UTF-8" />
// <meta
// name="viewport"
// content="width=device-width, initial-scale=1.0, user-scalable=no"
// />
// <title>Robo Car Racing Controller</title>
// </head>
// <body>
// <style>
// * {
// margin: 0;
// padding: 0;
// box-sizing: border-box;
// }

// body {
// font-family: "Arial", sans-serif;
// background: linear-gradient(135deg, #2c3e50 0%, #34495e 100%);
// min-height: 100vh;
// display: flex;
// flex-direction: column;
// overflow: hidden;
// -webkit-user-select: none;
// -moz-user-select: none;
// -ms-user-select: none;
// user-select: none;
// -webkit-touch-callout: none;
// }

// .hud-container {
// position: relative;
// z-index: 10;
// height: 100vh;
// display: flex;
// align-items: center;
// justify-content: center;
// padding: 20px;
// }

// .controls-container {
// width: 100%;
// display: flex;
// justify-content: space-between;
// align-items: center;
// max-width: 1200px;
// margin: 0 auto;
// }

// .left-controls {
// display: flex;
// gap: 20px;
// align-items: center;
// }

// .steering-control {
// position: relative;
// width: 120px;
// height: 120px;
// }

// .steering-btn {
// width: 100%;
// height: 100%;
// border: none;
// border-radius: 50%;
// background: linear-gradient(145deg, #3a3a3a, #2a2a2a);
// box-shadow: 0 10px 30px rgba(0, 0, 0, 0.5),
// inset 0 1px 0 rgba(255, 255, 255, 0.1);
// cursor: pointer;
// transition: all 0.3s ease;
// display: flex;
// align-items: center;
// justify-content: center;
// font-size: 2rem;
// color: #fff;
// position: relative;
// overflow: hidden;
// touch-action: manipulation;
// }

// .steering-btn::before {
// content: "";
// position: absolute;
// top: -2px;
// left: -2px;
// right: -2px;
// bottom: -2px;
// background: linear-gradient(45deg, #ff6b35, #ffa726);
// border-radius: 50%;
// z-index: -1;
// opacity: 0;
// transition: opacity 0.3s ease;
// }

// .steering-btn:hover::before,
// .steering-btn.active::before {
// opacity: 1;
// }

// .steering-btn:active,
// .steering-btn.active {
// transform: scale(0.95);
// box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);
// }

// .speedometer {
// position: relative;
// width: 250px;
// height: 150px;
// background: linear-gradient(135deg, #1a1a1a, #333);
// border-radius: 125px 125px 0 0;
// border: 3px solid #ffd700;
// display: flex;
// flex-direction: column;
// align-items: center;
// justify-content: center;
// box-shadow: 0 0 30px rgba(255, 215, 0, 0.3);
// padding: 20px;
// top: 8rem;
// }

// .speed-display {
// font-size: 3rem;
// font-weight: bold;
// color: #ffd700;
// text-shadow: 0 0 10px rgba(255, 215, 0, 0.5);
// margin-bottom: 5px;
// }

// .speed-unit {
// font-size: 1rem;
// color: #fff;
// margin-bottom: 15px;
// }

// .speed-bar {
// position: absolute;
// top: 10rem;
// left: 20px;
// right: 20px;
// height: 8px;
// background: #333;
// border-radius: 4px;
// overflow: hidden;
// }

// .speed-fill {
// height: 100%;
// background: linear-gradient(90deg, #27ae60, #f1c40f, #e74c3c);
// width: 0%;
// transition: width 0.3s ease;
// border-radius: 4px;
// }

// .gear-info {
// display: flex;
// gap: 30px;
// font-size: 0.9rem;
// color: #ccc;
// margin-top: 10px;
// }

// .connection-status {
// position: absolute;
// top: 20px;
// right: 20px;
// display: flex;
// align-items: center;
// gap: 10px;
// background: rgba(0, 0, 0, 0.7);
// padding: 8px 15px;
// border-radius: 20px;
// font-size: 0.8rem;
// color: #fff;
// z-index: 30;
// }

// .status-dot {
// width: 10px;
// height: 10px;
// border-radius: 50%;
// background: #e74c3c;
// animation: blink 1s infinite;
// }

// .status-dot.connected {
// background: #27ae60;
// animation: none;
// }

// @keyframes blink {
// 0%,
// 50% {
// opacity: 1;
// }
// 51%,
// 100% {
// opacity: 0.3;
// }
// }

// .right-controls {
// display: flex;
// flex-direction: column;
// gap: 15px;
// align-items: center;
// }

// .direction-control {
// width: 80px;
// height: 80px;
// border: none;
// border-radius: 15px;
// background: linear-gradient(145deg, #3a3a3a, #2a2a2a);
// box-shadow: 0 8px 20px rgba(0, 0, 0, 0.4),
// inset 0 1px 0 rgba(255, 255, 255, 0.1);
// cursor: pointer;
// transition: all 0.3s ease;
// display: flex;
// align-items: center;
// justify-content: center;
// font-size: 1.8rem;
// color: #fff;
// position: relative;
// overflow: hidden;
// touch-action: manipulation;
// }

// .direction-control::before {
// content: "";
// position: absolute;
// top: -2px;
// left: -2px;
// right: -2px;
// bottom: -2px;
// background: linear-gradient(45deg, #ff6b35, #ffa726);
// border-radius: 15px;
// z-index: -1;
// opacity: 0;
// transition: opacity 0.3s ease;
// }

// .direction-control:hover::before,
// .direction-control.active::before {
// opacity: 1;
// }

// .direction-control:active,
// .direction-control.active {
// transform: scale(0.95);
// }

// .stop-btn {
// width: 100px;
// height: 60px;
// background: linear-gradient(145deg, #e74c3c, #c0392b) !important;
// border-radius: 30px;
// font-size: 1rem;
// font-weight: bold;
// margin-top: 10px;
// animation: pulse-red 2s ease-in-out infinite alternate;
// }

// @keyframes pulse-red {
// 0% {
// box-shadow: 0 8px 20px rgba(231, 76, 60, 0.3);
// }
// 100% {
// box-shadow: 0 8px 20px rgba(231, 76, 60, 0.6);
// }
// }

// .top-container {
// display: flex;
// align-items: center;
// }

// .speed-controls {
// top: 20px;
// border: 1px solid white;
// position: relative;
// left: 50%;
// transform: translateX(-50%);
// display: flex;
// align-items: center;
// gap: 15px;
// background: rgba(0, 0, 0, 0.7);
// padding: 10px 20px;
// border-radius: 25px;
// z-index: 20;
// }

// .speed-label {
// color: #fff;
// font-size: 0.9rem;
// font-weight: bold;
// }

// .speed-slider {
// width: 200px;
// height: 6px;
// border-radius: 3px;
// background: #333;
// outline: none;
// }

// .speed-slider::-webkit-slider-thumb {
// -webkit-appearance: none;
// appearance: none;
// width: 20px;
// height: 20px;
// border-radius: 50%;
// background: linear-gradient(145deg, #ffd700, #ffed4a);
// cursor: pointer;
// box-shadow: 0 0 10px rgba(255, 215, 0, 0.6);
// }

// .speed-slider::-moz-range-thumb {
// width: 20px;
// height: 20px;
// border-radius: 50%;
// background: linear-gradient(145deg, #ffd700, #ffed4a);
// cursor: pointer;
// border: none;
// box-shadow: 0 0 10px rgba(255, 215, 0, 0.6);
// }

// .status-message {
// position: absolute;
// top: 70px;
// left: 50%;
// transform: translateX(-50%);
// background: rgba(0, 0, 0, 0.8);
// color: #fff;
// padding: 8px 20px;
// border-radius: 20px;
// font-size: 0.9rem;
// z-index: 20;
// opacity: 0;
// transition: opacity 0.3s ease;
// }

// .status-message.show {
// opacity: 1;
// }

// .active-commands {
// position: absolute;
// top: 20px;
// left: 20px;
// background: rgba(0, 0, 0, 0.7);
// padding: 10px 15px;
// border-radius: 15px;
// color: #fff;
// font-size: 0.8rem;
// z-index: 30;
// min-width: 150px;
// }

// .active-commands h4 {
// margin-bottom: 5px;
// color: #ffd700;
// }

// .command-list {
// font-family: monospace;
// line-height: 1.3;
// }

// /* Mobile Portrait - Show rotation message */
// @media screen and (max-width: 768px) and (orientation: portrait) {
// .hud-container {
// display: none;
// }

// .rotation-message {
// position: fixed;
// top: 0;
// left: 0;
// width: 100%;
// height: 100%;
// background: linear-gradient(135deg, #2c3e50 0%, #34495e 100%);
// display: flex;
// flex-direction: column;
// justify-content: center;
// align-items: center;
// color: white;
// text-align: center;
// z-index: 1000;
// padding: 20px;
// }

// .rotation-icon {
// font-size: 4rem;
// margin-bottom: 20px;
// animation: rotate 2s linear infinite;
// }

// @keyframes rotate {
// from {
// transform: rotate(0deg);
// }
// to {
// transform: rotate(360deg);
// }
// }

// .rotation-text {
// font-size: 1.5rem;
// font-weight: bold;
// margin-bottom: 10px;
// }

// .rotation-subtext {
// font-size: 1rem;
// opacity: 0.8;
// }
// }

// /* Mobile Landscape - Racing game style */
// @media screen and (max-width: 768px) and (orientation: landscape) {
// .hud-container {
// padding: 10px;
// height: 100vh;
// }

// .controls-container {
// height: 100%;
// max-width: 100%;
// justify-content: space-between;
// align-items: stretch;
// }

// .left-controls {
// gap: 15px;
// justify-content: center;
// padding-left: 20px;
// }

// .steering-control {
// width: 90px;
// height: 90px;
// }

// .steering-btn {
// font-size: 1.8rem;
// }

// .center-hud {
// flex: 1;
// display: flex;
// align-items: center;
// justify-content: center;
// }

// .speedometer {
// width: 200px;
// height: 120px;
// top: 0;
// margin-top: 20px;
// }

// .speed-display {
// font-size: 2.2rem;
// }

// .speed-bar {
// top: 8rem;
// }

// .gear-info {
// gap: 20px;
// font-size: 0.8rem;
// }

// .right-controls {
// flex-direction: column;
// gap: 12px;
// justify-content: center;
// align-items: flex-end;
// padding-right: 20px;
// }

// .direction-control {
// width: 75px;
// height: 75px;
// font-size: 1.6rem;
// }

// .stop-btn {
// width: 90px;
// height: 50px;
// font-size: 0.9rem;
// }

// .top-container {
// position: fixed;
// top: 0;
// left: 0;
// right: 0;
// height: 60px;
// z-index: 40;
// display: flex;
// align-items: center;
// justify-content: space-between;
// padding: 0 15px;
// }

// .speed-controls {
// position: relative;
// transform: none;
// top:1rem;
// left: 0;
// border: none;
// background: rgba(0, 0, 0, 0.5);
// padding: 5px 15px;
// border-radius: 20px;
// gap: 10px;
// }

// .speed-slider {
// width: 120px;
// height: 4px;
// }

// .speed-slider::-webkit-slider-thumb {
// width: 16px;
// height: 16px;
// }

// .speed-label {
// font-size: 0.8rem;
// }

// .connection-status {
// position: static;
// background: rgba(0, 0, 0, 0.5);
// padding: 5px 12px;
// border-radius: 15px;
// font-size: 0.7rem;
// }

// .active-commands{
//   display:none;
// }

// .status-message {
// top: 65px;
// font-size: 0.8rem;
// padding: 6px 15px;
// }
// }

// /* Small mobile landscape */
// @media screen and (max-width: 640px) and (orientation: landscape) {
// .steering-control {
// width: 75px;
// height: 75px;
// }

// .steering-btn {
// font-size: 1.5rem;
// }

// .direction-control {
// width: 65px;
// height: 65px;
// font-size: 1.4rem;
// }

// .speedometer {
// width: 160px;
// height: 100px;
// }

// .speed-display {
// font-size: 1.8rem;
// }

// .speed-bar {
// top: 6rem;
// }

// .gear-info {
// gap: 15px;
// font-size: 0.7rem;
// }

// .left-controls {
// padding-left: 10px;
// }

// .right-controls {
// padding-right: 10px;
// }

// .stop-btn {
// width: 80px;
// height: 45px;
// font-size: 0.8rem;
// }
// }

// /* Very small screens */
// @media screen and (max-width: 480px) and (orientation: landscape) {
// .steering-control {
// width: 65px;
// height: 65px;
// }

// .steering-btn {
// font-size: 1.3rem;
// }

// .direction-control {
// width: 55px;
// height: 55px;
// font-size: 1.2rem;
// }

// .speedometer {
// width: 140px;
// height: 85px;
// }

// .speed-display {
// font-size: 1.5rem;
// }

// .speed-bar {
// top: 5rem;
// }

// .gear-info {
// gap: 10px;
// font-size: 0.65rem;
// }

// .speed-slider {
// width: 100px;
// }

// .speed-label {
// font-size: 0.7rem;
// }

// .stop-btn {
// width: 70px;
// height: 40px;
// font-size: 0.7rem;
// }
// }
// </style>

// <!-- Rotation message for portrait mode -->
// <div class="rotation-message" style="display: none">
// <div class="rotation-icon">📱</div>
// <div class="rotation-text">Rotate Device</div>
// <div class="rotation-subtext">
// Please rotate your device to landscape mode for the best racing
// experience
// </div>
// </div>

// <div class="top-container">
// <div class="connection-status">
// <div class="status-dot" id="statusDot"></div>
// <span id="connectionText">Disconnected</span>
// </div>

// <div class="speed-controls">
// <span class="speed-label">POWER:</span>
// <input
// type="range"
// class="speed-slider"
// id="speedSlider"
// min="0"
// max="255"
// value="255"
// />
// <span class="speed-label" id="speedValue">255</span>
// </div>
// </div>

// <div class="active-commands">
// <h4>Active Commands:</h4>
// <div class="command-list" id="activeCommands">None</div>
// </div>

// <div class="status-message" id="statusMessage">Ready to race!</div>

// <div class="hud-container">
// <div class="controls-container">
// <div class="left-controls">
// <div class="steering-control">
// <button class="steering-btn" id="leftBtn">⬅️</button>
// </div>
// <div class="steering-control">
// <button class="steering-btn" id="rightBtn">➡️</button>
// </div>
// </div>

// <div class="center-hud">
// <div class="speedometer">
// <div class="speed-bar">
// <div class="speed-fill" id="speedFill"></div>
// </div>
// <div class="speed-display" id="speedDisplay">255</div>
// <div class="speed-unit">SPEED</div>
// <div class="gear-info">
// <span>RPM: <span id="rpm">0</span></span>
// <span>GEAR: <span id="gear">P</span></span>
// <span>DIR: <span id="direction">STOP</span></span>
// </div>
// </div>
// </div>

// <div class="right-controls">
// <button class="direction-control" id="upBtn">⬆️</button>
// <button class="direction-control" id="downBtn">⬇️</button>
// <button class="direction-control stop-btn" id="stopBtn">🛑</button>
// </div>
// </div>
// </div>

// <script>
// // Replace with your ESP-32 IP address
// const ESP32_IP = "192.168.4.1";

// // Command mappings for ESP32 firmware
// const commandMap = {
// forward: "F",
// backward: "B",
// left: "L",
// right: "R",
// stop: "S",
// };

// // Button configuration
// const buttons = {
// upBtn: { command: "forward", name: "Forward" },
// downBtn: { command: "backward", name: "Backward" },
// leftBtn: { command: "left", name: "Left" },
// rightBtn: { command: "right", name: "Right" },
// stopBtn: { command: "stop", name: "Stop" },
// };

// // Priority mapping for combined commands
// const combinedCommands = {
// "forward,left": "G", // Forward + Left
// "forward,right": "I", // Forward + Right
// "backward,left": "H", // Backward + Left
// "backward,right": "J", // Backward + Right
// };

// const statusMessage = document.getElementById("statusMessage");
// const speedSlider = document.getElementById("speedSlider");
// const speedValue = document.getElementById("speedValue");
// const speedDisplay = document.getElementById("speedDisplay");
// const speedFill = document.getElementById("speedFill");
// const statusDot = document.getElementById("statusDot");
// const connectionText = document.getElementById("connectionText");
// const rpm = document.getElementById("rpm");
// const gear = document.getElementById("gear");
// const direction = document.getElementById("direction");
// const activeCommands = document.getElementById("activeCommands");

// let isConnected = false;
// let currentSpeed = 255
// let activeButtons = new Set();
// let currentCommands = [];

// // Handle orientation change
// function handleOrientationChange() {
// const rotationMessage = document.querySelector(".rotation-message");
// const hudContainer = document.querySelector(".hud-container");

// if (window.innerWidth <= 768) {
// if (window.innerHeight > window.innerWidth) {
// // Portrait mode
// rotationMessage.style.display = "flex";
// hudContainer.style.display = "none";
// } else {
// // Landscape mode
// rotationMessage.style.display = "none";
// hudContainer.style.display = "flex";
// }
// } else {
// // Desktop
// rotationMessage.style.display = "none";
// hudContainer.style.display = "flex";
// }
// }

// // Listen for orientation changes
// window.addEventListener("orientationchange", () => {
// setTimeout(handleOrientationChange, 100);
// });

// window.addEventListener("resize", handleOrientationChange);

// // Initial orientation check
// handleOrientationChange();

// // Convert speed value to ESP32 speed state
// function getSpeedState(value) {
// if (value >= 0 && value <= 90) return "0";
// if (value >= 91 && value <= 130) return "1";
// if (value >= 131 && value <= 150) return "2";
// if (value >= 151 && value <= 170) return "3";
// if (value >= 171 && value <= 190) return "4";
// if (value >= 191 && value <= 210) return "5";
// if (value >= 211 && value <= 230) return "6";
// if (value >= 231 && value <= 245) return "7";
// if (value >= 246 && value <= 254) return "9";
// if (value === 255) return "q";
// return "5"; // Default to middle speed
// }

// // Handle button mouse/touch events
// Object.keys(buttons).forEach((btnId) => {
// const btn = document.getElementById(btnId);

// // Mouse events
// btn.addEventListener("mousedown", (e) => {
// e.preventDefault();
// activateButton(btnId);
// });

// btn.addEventListener("mouseup", (e) => {
// e.preventDefault();
// deactivateButton(btnId);
// });

// btn.addEventListener("mouseleave", (e) => {
// e.preventDefault();
// deactivateButton(btnId);
// });

// // Touch events for mobile
// btn.addEventListener("touchstart", (e) => {
// e.preventDefault();
// activateButton(btnId);
// });

// btn.addEventListener("touchend", (e) => {
// e.preventDefault();
// deactivateButton(btnId);
// });

// btn.addEventListener("touchcancel", (e) => {
// e.preventDefault();
// deactivateButton(btnId);
// });

// // Also handle click for stop button
// if (btnId === "stopBtn") {
// btn.addEventListener("click", (e) => {
// e.preventDefault();
// stopAllMovement();
// });
// }
// });

// // Handle keyboard controls
// const keyMap = {
// ArrowUp: "upBtn",
// w: "upBtn",
// W: "upBtn",
// ArrowDown: "downBtn",
// s: "downBtn",
// S: "downBtn",
// ArrowLeft: "leftBtn",
// a: "leftBtn",
// A: "leftBtn",
// ArrowRight: "rightBtn",
// d: "rightBtn",
// D: "rightBtn",
// " ": "stopBtn",
// };

// document.addEventListener("keydown", (e) => {
// if (e.repeat) return;

// const btnId = keyMap[e.key];
// if (btnId) {
// e.preventDefault();
// if (btnId === "stopBtn") {
// stopAllMovement();
// } else {
// activateButton(btnId);
// }
// }
// });

// document.addEventListener("keyup", (e) => {
// const btnId = keyMap[e.key];
// if (btnId && btnId !== "stopBtn") {
// e.preventDefault();
// deactivateButton(btnId);
// }
// });

// // Activate button function
// function activateButton(btnId) {
// if (btnId === "stopBtn") {
// stopAllMovement();
// return;
// }

// if (!activeButtons.has(btnId)) {
// activeButtons.add(btnId);
// const btn = document.getElementById(btnId);
// btn.classList.add("active");
// updateCommands();
// }
// }

// // Deactivate button function
// function deactivateButton(btnId) {
// if (activeButtons.has(btnId)) {
// activeButtons.delete(btnId);
// const btn = document.getElementById(btnId);
// btn.classList.remove("active");
// updateCommands();
// }
// }

// // Stop all movement
// function stopAllMovement() {
// activeButtons.clear();
// Object.keys(buttons).forEach((btnId) => {
// const btn = document.getElementById(btnId);
// btn.classList.remove("active");
// });
// currentCommands = [];
// sendCommand("S"); // Send stop command
// updateDisplay();
// }

// // Update commands based on active buttons
// function updateCommands() {
// const activeCommandList = Array.from(activeButtons).map(
// (btnId) => buttons[btnId].command
// );
// currentCommands = activeCommandList;

// if (currentCommands.length === 0) {
// sendCommand("S"); // Stop
// } else {
// // Handle combined commands with priority: F/B first, then L/R
// let finalCommand = "";

// // Check for forward/backward first
// if (
// currentCommands.includes("forward") &&
// currentCommands.includes("left")
// ) {
// finalCommand = combinedCommands["forward,left"] || "F";
// } else if (
// currentCommands.includes("forward") &&
// currentCommands.includes("right")
// ) {
// finalCommand = combinedCommands["forward,right"] || "F";
// } else if (
// currentCommands.includes("backward") &&
// currentCommands.includes("left")
// ) {
// finalCommand = combinedCommands["backward,left"] || "B";
// } else if (
// currentCommands.includes("backward") &&
// currentCommands.includes("right")
// ) {
// finalCommand = combinedCommands["backward,right"] || "B";
// } else if (currentCommands.includes("forward")) {
// finalCommand = commandMap.forward;
// } else if (currentCommands.includes("backward")) {
// finalCommand = commandMap.backward;
// } else if (currentCommands.includes("left")) {
// finalCommand = commandMap.left;
// } else if (currentCommands.includes("right")) {
// finalCommand = commandMap.right;
// }

// sendCommand(finalCommand);
// }

// updateDisplay();
// }

// // Update display information
// function updateDisplay() {
// // Update active commands display
// if (currentCommands.length === 0) {
// activeCommands.textContent = "None";
// gear.textContent = "P";
// direction.textContent = "STOP";
// } else {
// const commandNames = Array.from(activeButtons).map(
// (btnId) => buttons[btnId].name
// );
// activeCommands.textContent = commandNames.join(" + ");

// // Update gear and direction
// if (activeButtons.has("upBtn")) {
// gear.textContent = "D";
// direction.textContent = "FORWARD";
// } else if (activeButtons.has("downBtn")) {
// gear.textContent = "R";
// direction.textContent = "BACKWARD";
// } else {
// gear.textContent = "N";
// direction.textContent = "TURNING";
// }
// }

// // Update RPM based on movement
// if (currentCommands.length > 0) {
// rpm.textContent = Math.floor(currentSpeed * 2.5);
// } else {
// rpm.textContent = "0";
// }
// }

// // Handle speed changes
// speedSlider.addEventListener("input", (e) => {
// currentSpeed = parseInt(e.target.value);
// speedValue.textContent = currentSpeed;
// speedDisplay.textContent = currentSpeed;

// // Update speed bar
// const percentage = (currentSpeed / 255) * 100;
// speedFill.style.width = percentage + "%";

// // Send speed command to ESP32
// const speedState = getSpeedState(currentSpeed);
// sendCommand(speedState);
// updateDisplay();
// });

// // Show status message
// function showStatus(message) {
// statusMessage.textContent = message;
// statusMessage.classList.add("show");
// setTimeout(() => statusMessage.classList.remove("show"), 2000);
// }

// // Send command to ESP-32
// function sendCommand(state) {
// const endpoint = `/?State=${state}`;
// console.log("Sending command:", endpoint);

// fetch(`http://${ESP32_IP}${endpoint}`)
// .then((response) => {
// if (response.ok) {
// isConnected = true;
// statusDot.classList.add("connected");
// connectionText.textContent = "Connected";
// return response.text();
// } else {
// throw new Error("Network response was not ok");
// }
// })
// .then((data) => {
// console.log("Response:", data);
// })
// .catch((error) => {
// isConnected = false;
// statusDot.classList.remove("connected");
// connectionText.textContent = "Disconnected";
// console.error("Error:", error);
// });
// }

// // Initialize display
// speedDisplay.textContent = currentSpeed;
// speedFill.style.width = (currentSpeed / 255) * 100 + "%";
// updateDisplay();

// // Initial connection test - just test connectivity without sending stop
// fetch(`http://${ESP32_IP}/`)
// .then((response) => {
// if (response.ok) {
// isConnected = true;
// statusDot.classList.add("connected");
// connectionText.textContent = "Connected";
// }
// })
// .catch((error) => {
// isConnected = false;
// statusDot.classList.remove("connected");
// connectionText.textContent = "Disconnected";
// });

// // Periodic connection check - test connectivity without sending commands
// setInterval(() => {
// if (!isConnected) {
// fetch(`http://${ESP32_IP}/`)
// .then((response) => {
// if (response.ok) {
// isConnected = true;
// statusDot.classList.add("connected");
// connectionText.textContent = "Connected";
// }
// })
// .catch((error) => {
// isConnected = false;
// statusDot.classList.remove("connected");
// connectionText.textContent = "Disconnected";
// });
// }
// }, 5000);

// // Prevent context menu on long press
// document.addEventListener("contextmenu", (e) => {
// e.preventDefault();
// });

// // Prevent text selection
// document.addEventListener("selectstart", (e) => {
// e.preventDefault();
// });

// // Prevent zoom on double tap
// let lastTouchEnd = 0;
// document.addEventListener(
// "touchend",
// (e) => {
// const now = new Date().getTime();
// if (now - lastTouchEnd <= 300) {
// e.preventDefault();
// }
// lastTouchEnd = now;
// },
// false
// );

// // Prevent scrolling on mobile
// document.addEventListener(
// "touchmove",
// (e) => {
// e.preventDefault();
// },
// { passive: false }
// );

// // Handle visibility change (when app goes to background)
// document.addEventListener("visibilitychange", () => {
// if (document.visibilityState === "hidden") {
// // Stop all movement when app goes to background
// stopAllMovement();
// }
// });
// </script>
// </body>
// </html>

// )rawliteral";

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Starting ESP32 RC Car...");

//   // Initialize motor pins
//   pinMode(leftMotorPin1, OUTPUT);
//   pinMode(leftMotorPin2, OUTPUT);
//   pinMode(rightMotorPin1, OUTPUT);
//   pinMode(rightMotorPin2, OUTPUT);
//   pinMode(statusLED, OUTPUT);

//    // 1. Configure LEDC PWM channels
//   ledcSetup(0, 5000, 8);  // Channel 0, 5kHz, 8-bit resolution (left motor)
//   ledcSetup(1, 5000, 8);  // Channel 1, 5kHz, 8-bit resolution (right motor)
 
//   // 2. Attach pins to channels
//  ledcAttachPin(leftMotorENA, 0);  // Attach left PWM
//   ledcAttachPin(rightMotorENB, 1); // Attach right PWM

//   // Stop motors initially
//   stopMotors();

//   // Start WiFi Access Point
//   Serial.println("Setting up Access Point...");
//   WiFi.softAP(ssid, password);
 
//   IPAddress IP = WiFi.softAPIP();
//   Serial.print("AP IP address: ");
//   Serial.println(IP);
 
//   // Turn on status LED to indicate AP is ready
//   digitalWrite(statusLED, HIGH);

//   // Configure web server routes
//   server.on("/", []() {
//     if (server.hasArg("State")) {
//       String state = server.arg("State");
//       Serial.print("Received command: ");
//       Serial.println(state);
//       processCommand(state);
//       server.send(200, "text/plain", "Command: " + state + " executed");
//     } else {
//       server.send(200, "text/html", htmlPage);
//     }
//   });

//   // Handle 404 errors
//   server.onNotFound([]() {
//     server.send(404, "text/plain", "404: Not Found");
//   });

//   // Start the server
//   server.begin();
//   Serial.println("HTTP server started");
//   Serial.println("Connect to WiFi: " + String(ssid));
//   Serial.println("Password: " + String(password));
//   Serial.println("Then open http://" + IP.toString() + " in your browser");
// }

// void loop() {
//   server.handleClient();
 
//   // Blink status LED to show the system is running
//   static unsigned long lastBlink = 0;
//   if (millis() - lastBlink > 2000) {
//     digitalWrite(statusLED, !digitalRead(statusLED));
//     lastBlink = millis();
//   }
// }

// void processCommand(String command) {
//   currentState = command;
 
//   Serial.print("Processing command: ");
//   Serial.println(command);
 
//   // Handle speed commands first
//   if (command == "0" || command == "1" || command == "2" || command == "3" ||
//       command == "4" || command == "5" || command == "6" || command == "7" ||
//       command == "9" || command == "q") {
//     currentSpeed = getSpeedFromState(command);
//     Serial.print("Speed changed to: ");
//     Serial.println(currentSpeed);
//     return;
//   }
 
//   // Handle movement commands
//   if (command == "F") {
//     moveForward();
//     Serial.println("Moving Forward");
//   }
//   else if (command == "B") {
//     moveBackward();
//     Serial.println("Moving Backward");
//   }
//   else if (command == "L") {
//     turnLeft();
//     Serial.println("Turning Left");
//   }
//   else if (command == "R") {
//     turnRight();
//     Serial.println("Turning Right");
//   }
//   else if (command == "G") {
//     moveForwardLeft();
//     Serial.println("Moving Forward Left");
//   }
//   else if (command == "I") {
//     moveForwardRight();
//     Serial.println("Moving Forward Right");
//   }
//   else if (command == "H") {
//     moveBackwardLeft();
//     Serial.println("Moving Backward Left");
//   }
//   else if (command == "J") {
//     moveBackwardRight();
//     Serial.println("Moving Backward Right");
//   }
//   else if (command == "S") {
//     stopMotors();
//     Serial.println("Stopping Motors");
//   }
//   else {
//     Serial.println("Unknown command: " + command);
//   }
// }

// void moveForward() {
//   digitalWrite(leftMotorPin1, HIGH);
//   digitalWrite(leftMotorPin2, LOW);
//   digitalWrite(rightMotorPin1, HIGH);
//   digitalWrite(rightMotorPin2, LOW);
//   ledcWrite(0, currentSpeed);
//   ledcWrite(1, currentSpeed);
 
// }

// void moveBackward() {
//   digitalWrite(leftMotorPin1, LOW);
//   digitalWrite(leftMotorPin2, HIGH);
//   digitalWrite(rightMotorPin1, LOW);
//   digitalWrite(rightMotorPin2, HIGH);
//   ledcWrite(0, currentSpeed);
//   ledcWrite(1, currentSpeed);
// }

// void turnLeft() {
//   digitalWrite(leftMotorPin1, LOW);
//   digitalWrite(leftMotorPin2, HIGH);
//   digitalWrite(rightMotorPin1, HIGH);
//   digitalWrite(rightMotorPin2, LOW);
//   ledcWrite(0, 150);
//   ledcWrite(1, 150);
// }

// void turnRight() {
//   digitalWrite(leftMotorPin1, HIGH);
//   digitalWrite(leftMotorPin2, LOW);
//   digitalWrite(rightMotorPin1, LOW);
//   digitalWrite(rightMotorPin2, HIGH);
//   ledcWrite(0, 150);
//   ledcWrite(1, 150);
// }

// void moveForwardLeft() {
//   digitalWrite(leftMotorPin1, HIGH);
//   digitalWrite(leftMotorPin2, LOW);
//   digitalWrite(rightMotorPin1, HIGH);
//   digitalWrite(rightMotorPin2, LOW);
//   ledcWrite(0, currentSpeed* 0.5); // Reduce left motor speed
//   ledcWrite(1, currentSpeed);
// }

// void moveForwardRight() {
//   digitalWrite(leftMotorPin1, HIGH);
//   digitalWrite(leftMotorPin2, LOW);
//   digitalWrite(rightMotorPin1, HIGH);
//   digitalWrite(rightMotorPin2, LOW);
//   ledcWrite(0, currentSpeed);
//   ledcWrite(1, currentSpeed*0.5);  // Reduce right motor speed
// }

// void moveBackwardLeft() {
//   digitalWrite(leftMotorPin1, LOW);
//   digitalWrite(leftMotorPin2, HIGH);
//   digitalWrite(rightMotorPin1, LOW);
//   digitalWrite(rightMotorPin2, HIGH);
//   ledcWrite(0, currentSpeed * 0.5);  // Reduce left motor speed
//   ledcWrite(1, currentSpeed);
// }

// void moveBackwardRight() {
//   digitalWrite(leftMotorPin1, LOW);
//   digitalWrite(leftMotorPin2, HIGH);
//   digitalWrite(rightMotorPin1, LOW);
//   digitalWrite(rightMotorPin2, HIGH);
//   ledcWrite(0, currentSpeed);
//   ledcWrite(1, currentSpeed * 0.5);  // Reduce right motor speed
// }

// void stopMotors() {
//   digitalWrite(leftMotorPin1, LOW);
//   digitalWrite(leftMotorPin2, LOW);
//   digitalWrite(rightMotorPin1, LOW);
//   digitalWrite(rightMotorPin2, LOW);
//   ledcWrite(0, 0);
//   ledcWrite(1, 0);
// }
