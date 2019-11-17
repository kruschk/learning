"use strict";

const spinner = document.querySelector(".spinner p");
const spinnerContainer = document.querySelector(".spinner");
let rotateCount = 0;
let startTime = null;
let rAF;
const btn = document.querySelector("button");
const result = document.querySelector(".result");

function random(min, max) {
    return Math.floor(Math.random()*(max - min)) + min;
}

function draw(timestamp) {
    if (!startTime) {
        startTime = timestamp;
    }
    rotateCount = (timestamp - startTime)/3;
    if (359 < rotateCount) {
        rotateCount %= 360;
    }
    spinner.style.transform = `rotate(${rotateCount});`;
    rAF = requestAnimationFrame(draw);
}

result.style.display = "none";
spinnerContainer.style.display = "none";

function reset() {
    btn.style.display = "block";
    result.textContent = "";
    result.style.display = "none";
}

btn.addEventListener("click", start);

function start() {
    spinnerContainer.style.display = "block";
    btn.style.display = "none";
    draw(Date.now());
    setTimeout(setEndGame, random(5000, 10000));
}

function setEndGame() {
    cancelAnimationFrame(rAF);
    spinnerContainer.style.display = "none";
    result.style.display = "block";
    result.textContent = "PLAYERS GO!!";
    document.addEventListener("keydown", keyHandler);
    function keyHandler(e) {
        console.log(e.key);
        if ('a' === e.key) {
            result.textContent = "Player 1 won!!";
        } else if ('l' === e.key) {
            result.textContent = "Player 1 won!!";
        }
        document.removeEventListener("keydown", keyHandler);
        setTimeout(reset, 5000);
    };
}
