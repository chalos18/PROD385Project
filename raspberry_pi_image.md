# Raspberry Pi Image Setup with Node-RED  

## Overview

This guide explains how to create and configure a Raspberry Pi SD card image  
(e.g. **Raspberry Pi Zero W, Raspberry Pi 3, or Raspberry Pi 4**) with **Node-RED** installed.

The resulting image can be reused for IoT and embedded systems projects.

---

## Requirements

- Raspberry Pi - I have tested this method on the below:
  - Raspberry Pi Zero W  
  - Raspberry Pi 3  
  - Raspberry Pi 4
- Micro SD card:
  - **Minimum 16 GB** (32 GB recommended for long-term use)
  - Class 10 / UHS-I recommended
- Computer with SD card reader
- Monitor, keyboard, and mouse (for initial setup)
- Internet connection (WiFi or Ethernet)

---

## 1. Install Raspberry Pi Imager

On your computer, download and install **Raspberry Pi Imager**:

👉 https://www.raspberrypi.com/software/

This tool is used to flash the operating system onto the SD card.

---

## 2. Flash the SD Card

1. Open **Raspberry Pi Imager**
2. Follow the prompts below.

### Configuration Options

- **Device**  
  Select the Raspberry Pi model you are using.

- **Operating System**  
  Choose:
  - **Raspberry Pi OS (32-bit)** *(recommended)*

  This OS provides the best compatibility with Node-RED and GPIO libraries.

- **Storage**  
  Select your SD card  
  (often listed as `Generic MassStorageClass Media`).

---

### Advanced Settings (⚙️ Icon)

Before clicking *Write*, configure the advanced options:

- **Set Hostname**  
  Choose any name (e.g. `uc-pi-node-red`)  
  *(Write this down — you will need it later)*

- **Username & Password**  
  Set your own credentials  
  *(Do not forget these)*

- **Configure Wireless LAN**
  - You may leave this **blank** if using Ethernet
  - Or enter:
    - WiFi SSID
    - WiFi password
    - Correct country code (e.g. `NZ`)

- **Enable SSH**
  - Enable **SSH**
  - Authentication method: **Password**

- **Raspberry Pi Connect**
  - Leave **disabled**

3. Click **Write**
4. Wait for writing and verification to complete  
   *(This may take several minutes)*

---

## 3. First Boot

1. Remove the SD card from your computer
2. Insert it into the Raspberry Pi
3. Connect:
   - Monitor
   - Keyboard
   - Mouse
   - Power supply
4. Power on the Raspberry Pi
5. Wait **2–5 minutes** for the system to fully boot

You should now see the Raspberry Pi desktop.

---


14.	go back to the terminal and type: 
sudo apt update
15.	Answer any questions with yes or the default
16.	Wait – this may take 5 minutes. When the terminal gets back, type
sudo apt full-upgrade
17.	Answer any questions with yes or the default
18.	Wait (this may take ten minutes or more). When the terminal gets back type:
sudo rpi-update
19.	Wait (this may take five minutes or more). When the terminal gets back type:
sudo reboot

Install NodeRED (this can take over an hour!)

1.	Open the terminal and type: 
sudo apt install build-essential git curl
If asked: Are you really sure you want to do this ? [y/N] : type y
2.	When the terminal gets back type: 
bash <(curl -sL https://github.com/node-red/linux-installers/releases/latest/download/update-nodejs-and-nodered-deb)

•	When asked Are you really sure you want to do this ? [y/N] : type y
•	‘Would you like to install the Pi-specific nodes ? [y/N]‘ type y
•	If it pauses at Settings File, hit enter, then answer the questions.
•	Choose the default theme and text editor.
•	Allow Function nodes to load external modules.
3.	When the terminal gets back type:
sudo reboot
4.	Reopen terminal and type:
sudo systemctl enable nodered.service
5.	When the terminal gets back type:
sudo reboot and check the IP address again.
6.	On another computer on the same network, open an internet browser and go to: http://YourIPAddress:1880 
