"use strict";

// Store references to elements on the page.
const clock = document.querySelector(".clock");
const startBtn = document.querySelector(".start");
const stopResumeBtn = document.querySelector(".stop-resume");
const resetBtn = document.querySelector(".reset");
// Sets how frequently the clock updates. 0 is as fast as possible.
const refreshInterval = 0;

let interval = 0; // A reference to the interval so we can clear it.
let pauseTime = 0; // Tracks when the clock was paused.
let running = false; // Tells us if the clock is running.
let startTime = 0; // Tracks when the clock was started.

// Start the clock.
function start() {
    startTime = Date.now();
    interval = setInterval(calculateTime, refreshInterval);
    // Toggle flags.
    resetBtn.disabled = false;
    running = true;
    startBtn.disabled = true;
    stopResumeBtn.disabled = false;
}

// Stop or resume the clock, depending on its current state..
function stopResume() {
    // If the watch is running, save the current time, stop the clock, and
    // toggle the running flag.
    if (running) {
        pauseTime = Date.now();
        clearInterval(interval);
        running = false;
    } else {
        // Otherwise, shift the starting time to account for the duration for
        // which the clock was paused, start the clock again, and toggle the
        // running flag.
        startTime += Date.now() - pauseTime;
        interval = setInterval(calculateTime, refreshInterval);
        running = true;
    }
}

// Reset the stopwatch.
function reset() {
    // Stop the clock and display 0 on the stopwatch.
    clearInterval(interval);
    displayTime(0);
    // Toggle button clickable-ness.
    startBtn.disabled = false;
    stopResumeBtn.disabled = true;   
    resetBtn.disabled = true;   
    running = false;
}

// Calculate and display the time based on the starting time.
function calculateTime() {
    displayTime(Date.now() - startTime);
}

// Display the formatted time in the clock element.
function displayTime(t) {
    let hours = Math.floor(t/(3600*1000));
    if (hours < 10) {hours = `0${hours}`;}
    t %= 3600*1000;
    let minutes = Math.floor(t/(60*1000));
    if (minutes < 10) {minutes = `0${minutes}`;}
    t %= 60*1000;
    let seconds = Math.floor(t/1000);
    if (seconds < 10) {seconds = `0${seconds}`;}
    t %= 1000;
    let milliseconds = Math.floor(t);
    if (milliseconds < 10) {
        milliseconds = `00${milliseconds}`;
    } else if (milliseconds < 100) {
        milliseconds = `0${milliseconds}`;
    }
    const formattedTime = `${hours}:${minutes}:${seconds}.${milliseconds}`;
    clock.textContent = formattedTime;
}

// Add event listeners for the buttons.
startBtn.addEventListener("click", start);
stopResumeBtn.addEventListener("click", stopResume);
resetBtn.addEventListener("click", reset);
