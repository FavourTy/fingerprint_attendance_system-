# Fingerprint Attendance System

## Project Overview

This project is designed to streamline attendance taking in educational settings using biometric verification. The Fingerprint Attendance System is built to handle up to 300 students, ensuring a quick and secure way to record attendance with minimal manual input.

## Features

- **Biometric Authentication:** Utilizes fingerprints for secure and reliable student identification.
- **Scalable Storage:** Incorporates external data storage to manage attendance records for up to 300 students.
- **Real-Time Updates:** Automatically updates attendance records in real-time to ensure accurate tracking.
- **Efficient Processing:** Designed to handle multiple authentication requests swiftly to avoid delays during peak times.

## Hardware Components

- **Arduino Uno:** Serves as the central processing unit for managing data flow and device interactions.
- **Fingerprint Scanner:** Captures and verifies fingerprints.
- **LCD Display:** Provides user feedback and system status updates.
- **Real-Time Clock (RTC):** Keeps track of time and date for accurate attendance records.
- **Micro SD Card:** Used for external storage of attendance data.

## Software Components

- **Arduino IDE:** Used for programming the Arduino Uno with necessary logic for operation.
- **External Libraries:**
  - `Adafruit_Fingerprint.h` - For interfacing with the fingerprint scanner.
  - `RTClib.h` - For managing the real-time Clock.
  - `SD.h` - For operations related to the micro SD card.

## Setup and Installation

1. Assemble the hardware components based on the circuit diagram provided in the `schematics` folder.
2. Install the necessary libraries through the Arduino IDE's Library Manager.
3. Upload the provided script to the Arduino Uno.
4. Perform initial configuration as described in the `setup_instructions.md`.

## Usage

- **Registering a New Student:** Follow the steps in `registration_guide.md` to add a new student's fingerprint to the system.
- **Taking Attendance:** Students can authenticate by placing their registered finger on the scanner at the start of each class.
- **Viewing Records:** Access the attendance records via the micro SD card.

## Contributions

Contributions to this project are welcome. Please fork this repository and submit a pull request with your proposed fancyanges...Thannksss❤🎉

## License
This project is licensed under the MIT License 
