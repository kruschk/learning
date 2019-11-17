"use strict";

const html = document.querySelector("html");
const spinner = document.querySelector("div");
let spinning = true;
let rotateCount = 0;
let startTime = null;
let rAF = null;

function draw(timestamp) {
    if (!startTime) {
        startTime = timestamp;
    }
    rotateCount = (timestamp - startTime)/3;
    if (359 < rotateCount) {
        rotateCount %= 360;
    }
    spinner.style.transform = `rotate(${rotateCount}deg)`;
    rAF = requestAnimationFrame(draw);
}

html.addEventListener("click", function() {
    if (spinning) {
        cancelAnimationFrame(rAF);
        spinning = false;
    } else {
        spinning = true;
        draw();
    }
});

draw();
