"use strict";
// setup canvas
const canvas = document.querySelector("canvas");
const ctx = canvas.getContext("2d");
const width = canvas.width = window.innerWidth;
const height = canvas.height = window.innerHeight;
// function to generate random number
function random(min, max) {
    return Math.floor(Math.random()*(max-min)) + min;
}
function Ball(x, y, velX, velY, color, size) {
    this.x = x;
    this.y = y;
    this.velX = velX;
    this.velY = velY;
    this.color = color;
    this.size = size;
}
Ball.prototype.draw = function() {
    ctx.beginPath();
    ctx.fillStyle = this.color;
    ctx.arc(this.x, this.y, this.size, 0, 2*Math.PI);
    ctx.fill();
}
Ball.prototype.update = function() {
    // Ball has gone past the left or right side edge.
    if ((this.x - this.size <= 0) || (width <= this.x + this.size)) {
        this.velX = -(this.velX);
    }
    // Ball has gone past the lower or upper edge.
    if ((this.y - this.size <= 0) || (height <= this.y + this.size)) {
        this.velY = -(this.velY);
    }
    this.x += this.velX;
    this.y += this.velY;
}
Ball.prototype.collisionDetect = function() {
    for (let i = 0; i < balls.length; i++) {
        if (this !== balls[i]) {
            const dx = this.x - balls[i].x;
            const dy = this.y - balls[i].y;
            const distance = Math.sqrt(dx*dx + dy*dy);
            if (distance < this.size + balls[i].size) {
                balls[i].color = this.color = `rgb(${random(0, 255)}, `
                    + `${random(0, 255)}, ${random(0, 255)})`;
            }
        }
    }
}
let balls = [];
while (balls.length < 25) {
    const size = random(10, 20);
    const ball = new Ball(
        random(0 + size, width - size),
        random(0 + size, height - size),
        random(-7, 7),
        random(-7, 7),
        `rgb(${random(0, 255)}, ${random(0, 255)}, ${random(0, 255)})`,
        size
    );
    balls.push(ball);
}
function loop() {
    ctx.fillStyle = "rgba(0, 0, 0, 0.25)";
    ctx.fillRect(0, 0, width, height);
    for (let i = 0; i < balls.length; i++) {
        balls[i].draw();
        balls[i].update();
        balls[i].collisionDetect();
    }
    requestAnimationFrame(loop);
}
loop();
