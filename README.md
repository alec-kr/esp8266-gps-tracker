# ESP8266 GPS Tracker with SIM900 + Flask Map

This project tracks GPS coordinates using an ESP8266 + GPS module and sends them over GSM (SIM900/SIM800) or mesh Wi-Fi to a Flask server. The server displays the live route on an interactive Leaflet map.

## 🚀 Features
- ESP8266 reads GPS data (NEO-6M)
- Sends data via SIM900 (GPRS HTTP POST) or ESP mesh
- Flask server stores route coordinates
- Leaflet map (`index.html`) displays markers & routes
- Time filter UI for selecting journey segments

## 📂 Repo Structure
- `arduino/` – ESP8266 Arduino sketches
- `server/` – Flask + test client
- `web/` – Leaflet-based map UI
- `schematics/` – Block diagrams of wiring

## 🛠 Hardware
- ESP8266 (NodeMCU / Wemos D1 mini)
- SIM900 / SIM800 GSM module (4.0–4.2V supply, ≥2A peak)
- GPS module (NEO-6M / BN-880)
- Common ground + proper power regulation
