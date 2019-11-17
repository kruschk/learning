"use strict";

// setup canvas
const scoreCounter = document.querySelector("p");
const canvas = document.querySelector("canvas");
const ctx = canvas.getContext("2d");
const width = canvas.width = window.innerWidth;
const height = canvas.height = window.innerHeight;

// Generates a random number between `min` and `max`.
function random(min, max) {
    return Math.floor(Math.random()*(max - min)) + min;
}

// Define a `Shape` class.
class Shape {
    constructor(x, y, velX, velY, exists) {
        this.x = x;
        this.y = y;
        this.velX = velX;
        this.velY = velY;
        this.exists = true;
    }
}

// Define a `Ball` class.
class Ball extends Shape {
    constructor(x, y, velX, velY, exists, color, size) {
        super(x, y, velX, velY, exists);
        this.color = color;
        this.size = size;
    }
    // Draw a `Ball` on the canvas.
    draw = function() {
        ctx.beginPath();
        ctx.fillStyle = this.color;
        ctx.arc(this.x, this.y, this.size, 0, 2 * Math.PI);
        ctx.fill();
    }
    // Update the `Ball's` position.
    update = function() {
        if((this.x - this.size <= 0) || (width <= this.x + this.size)) {
            this.velX = -(this.velX);
        }
        if((this.y - this.size <= 0) || (height <= this.y + this.size)) {
            this.velY = -(this.velY);
        }
        this.x += this.velX;
        this.y += this.velY;
    }
    // Collision detection for the `Ball`.
    collisionDetect = function() {
        for(let i = 0; i < balls.length; i++) {
            if(this !== balls[i] && balls[i].exists) {
                const dx = this.x - balls[i].x;
                const dy = this.y - balls[i].y;
                const distance = Math.sqrt(dx*dx + dy*dy);
                if (distance < this.size + balls[i].size) {
                    balls[i].color = this.color
                        = `rgb(${random(0,255)}, ${random(0,255)}, `
                        + `${random(0,255)})`;
                }
            }
        }
    }
}

// Define an `EvilCircle` class.
class EvilCircle extends Shape {
    constructor(x, y, exists) {
        super(x, y, 20, 20, true);
        this.color = "white";
        this.size = 10;
    }
    // Draw the `EvilCircle` on the canvas.
    draw = function() {
        ctx.beginPath();
        ctx.strokeStyle = this.color;
        ctx.lineWidth = 3;
        ctx.arc(this.x, this.y, this.size, 0, 2 * Math.PI);
        ctx.stroke();
    }
    // Keep the ball within the boundaries of the canvas.
    checkBounds = function() {
        if (this.x - this.size <= 0) {
            this.x += this.size;
        }
        if (width <= this.x + this.size) {
            this.x -= this.size;
        }
        if(this.y - this.size <= 0) {
            this.y += this.size;
        }
        if (height <= this.y + this.size) {
            this.y -= this.size;
        }
    }
    // Add event listeners for keypresses on 'w', 'a', s', and 'd'.
    setControls = function() {
        const _this = this;
        window.addEventListener("keydown", function(e) {
            // 'a' goes left.
            if (65 === e.keyCode) {
                _this.x -= _this.velX;
            } else if (68 === e.keyCode) {
                // 'd' goes right.
                _this.x += _this.velX;
            } else if (87 === e.keyCode) {
                // 's' goes down.
                _this.y -= _this.velY;
            } else if (83 === e.keyCode) {
                // 'w' goes up.
                _this.y += _this.velY;
            }
        });
    }
    // Collision detection for the `EvilCircle`.
    collisionDetect = function() {
        for(let i = 0; i < balls.length; i++) {
            if(balls[i].exists) {
                const dx = this.x - balls[i].x;
                const dy = this.y - balls[i].y;
                const distance = Math.sqrt(dx*dx + dy*dy);
                if (distance < this.size + balls[i].size) {
                    balls[i].exists = false;
                    totalBalls--;
                    scoreCounter.textContent = totalBalls;
                }
            }
        }
    }
}

// A counter for the balls remaining on the screen.
let totalBalls = 25;
scoreCounter.textContent = totalBalls;
// Define an array to store the balls and populate it.
const balls = [];
while(balls.length < totalBalls) {
    const size = random(10,20);
    // The `Ball`'s position is always drawn at least one ball radius away
    // from the edge of the canvas to avoid drawing errors.
    const ball = new Ball(
        random(0 + size, width - size),
        random(0 + size, height - size),
        random(-7,7),
        random(-7,7),
        true,
        `rgb(${random(0,255)}, ${random(0,255)}, ${random(0,255)})`,
        size
    );
    balls.push(ball);
}
const player = new EvilCircle(random(0, width), random(0, height));
player.setControls();
// Define the main game loop which draws the scene forever (recursively).
function loop() {
    ctx.fillStyle = 'rgba(0, 0, 0, 0.25)';
    ctx.fillRect(0, 0, width, height);
    for(let i = 0; i < balls.length; i++) {
        if (balls[i].exists) {
            balls[i].draw();
            balls[i].update();
            balls[i].collisionDetect();
        }
    }
    player.draw();
    player.checkBounds();
    player.collisionDetect();
    requestAnimationFrame(loop);
}
loop();
