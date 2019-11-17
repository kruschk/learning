"use strict";

// Video element and control bar.
const media = document.querySelector("video");
const controls = document.querySelector(".controls");

// Control buttons.
const play = document.querySelector(".play");
const stop = document.querySelector(".stop");
const rwd = document.querySelector(".rwd");
const fwd = document.querySelector(".fwd");

// Timer elements.
const timerWrapper = document.querySelector(".timer");
const timer = document.querySelector(".timer span");
const timerBar = document.querySelector(".timer div");
media.removeAttribute("controls");
controls.style.visibility = "visible";

// Play/pause button functionality.
play.addEventListener("click", playPauseMedia);
function playPauseMedia() {
    rwd.classList.remove("active");
    fwd.classList.remove("active");
    clearInterval(intervalRwd);
    clearInterval(intervalFwd);
    if (media.paused) {
        play.setAttribute("data-icon", 'u');
        media.play();
    } else {
        play.setAttribute("data-icon", 'P');
        media.pause();
    }
}

// Stop button functionality.
stop.addEventListener("click", stopMedia);
media.addEventListener("ended", stopMedia);
function stopMedia() {
    rwd.classList.remove("active");
    fwd.classList.remove("active");
    clearInterval(intervalRwd);
    clearInterval(intervalFwd);
    media.pause();
    media.currentTime = 0;
    play.setAttribute("data-icon", 'P');
}

// Variables for fast-forwarding and rewinding.
let intervalFwd;
let intervalRwd;

// Rewind functionality.
rwd.addEventListener("click", mediaBackward);
function mediaBackward() {
    clearInterval(intervalFwd);
    fwd.classList.remove("active");
    if (rwd.classList.contains("active")) {
        rwd.classList.remove("active");
        clearInterval(intervalRwd);
        media.play();
    } else {
        rwd.classList.add("active");
        media.pause();
        intervalRwd = setInterval(windBackward, 200);
    }
}

function windBackward() {
    if (media.currentTime <= 3) {
        stopMedia();
    } else {
        media.currentTime -= 3;
    }
}

// Fast-forward functionality.
fwd.addEventListener("click", mediaForward);
function mediaForward() {
    clearInterval(intervalRwd);
    rwd.classList.remove("active");
    if (fwd.classList.contains("active")) {
        media.play();
    } else {
        fwd.classList.add("active");
        media.pause();
        intervalFwd = setInterval(windForward, 200);
    }
}

function windForward() {
    if (media.duration - 3 <= media.currentTime) {
        fwd.classList.remove("active");
        clearInterval(intervalFwd);
        stopMedia();
    } else {
        media.currentTime += 3;
    }
}

media.addEventListener("timeupdate", setTime);
function setTime() {
    const minutes = Math.floor(media.currentTime/60);
    const seconds = Math.floor(media.currentTime - minutes*60);
    let minuteValue;
    let secondValue;
    if (minutes < 10) {
        minuteValue = '0' + minutes;
    } else {
        minuteValue = minutes;
    }
    if (seconds < 10) {
        secondValue = '0' + seconds;
    } else {
        secondValue = seconds;
    }
    const mediaTime = `${minuteValue}:${secondValue}`;
    timer.textContent = mediaTime;
    const barLength = timerWrapper.clientWidth*media.currentTime/media.duration;
    timerBar.style.width = `${barLength}px`;
}
