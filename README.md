# Robot Mapping on a 5x5 Grid

## Overview

Welcome to our robot mapping project! This project focuses on developing a robot that can autonomously map its environment on a 5x5 grid using ultrasonic sensors and Bayesian occupancy mapping. Our team of ten dedicated members worked together to bring this innovative project to life.



## Project Description

Our robot uses a 5x5 grid to divide its environment into distinct cells. Equipped with ultrasonic sensors, it measures distances to objects and maps out its surroundings. By applying Bayesian occupancy mapping, we determine the probability of each cell being occupied.

## Features

- **Grid Setup:** Divides the environment into a 5x5 grid for structured mapping.
- **Ultrasonic Sensors:** Detects obstacles by measuring sound wave reflections.
- **Bayesian Occupancy Mapping:** Calculates the probability of cell occupancy using Bayesian methods.
- **Efficient Movement Algorithm:** Optimizes the robot's path to minimize steps and avoid redundant scans.
- **Wireless Data Transmission:** Uses a Bluetooth module for seamless data transfer from the Arduino to the laptop.
- **Dynamic Map Updating:** Continuously updates the map in real-time based on sensor data.

## Bayesian Occupancy Mapping

1. **Initial Probability:** Each cell starts with an initial probability of being occupied.
2. **Sensor Data Integration:** Updates cell probabilities using Bayes' theorem.
3. **Update Formula:** 
   \[
   P(O | S) = \frac{P(S | O) \cdot P(O)}{P(S)}
   \]
4. **Dynamic Updating:** Repeats the process as the robot gathers more data, refining probabilities continuously.
5. **Occupancy Determination:** Marks cells as occupied if their probability exceeds a threshold.

## How It Works

1. **Setup:** The robot initializes and divides the environment into a 5x5 grid.
2. **Exploration:** The robot moves through each cell, using ultrasonic sensors to measure distances to objects.
3. **Mapping:** The robot applies Bayesian occupancy mapping to calculate the probability of each cell being occupied.
4. **Data Transmission:** Sensor data is sent wirelessly to a laptop via a Bluetooth module.
5. **Map Updating:** The map is updated in real-time based on the latest sensor data.

## Requirements

- Arduino Board
- Ultrasonic Sensors
- Bluetooth Module
- Batteries (10.8V)


