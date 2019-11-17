"use strict";

// setup canvas
const scoreCounter = document.querySelector("p");
const canvas = document.querySelector("canvas");
const ctx = canvas.getContext("2d");
const width = canvas.width = window.innerWidth;
const height = canvas.height = window.innerHeight;

// function to generate random number
function random(min,max) {
    return Math.floor(Math.random()*(max-min)) + min;
}

// Define a `Shape` class.
function Shape(x, y, velX, velY, exists) {
    this.x = x;
    this.y = y;
    this.velX = velX;
    this.velY = velY;
    this.exists = true;
}

// Define a `Ball` class.
function Ball(x, y, velX, velY, exists, color, size) {
    Shape.call(this, x, y, velX, velY, exists);
    this.color = color;
    this.size = size;
}
// A `Ball` inherits from the `Shape` class.
Ball.prototype = Object.create(Shape.prototype);
// Reset the constructor from `Shape` back to `Ball`.
Object.defineProperty(Ball.prototype, "constructor", {
    value: Ball,
    enumerable: false,
    writable: true
});
// Draw a `Ball` on the canvas.
Ball.prototype.draw = function() {
    ctx.beginPath();
    ctx.fillStyle = this.color;
    ctx.arc(this.x, this.y, this.size, 0, 2 * Math.PI);
    ctx.fill();
}
// Update the `Ball's` position.
Ball.prototype.update = function() {
    if((this.x - this.size <= 0) || (width <= this.x + this.size)) {
        this.velX = -(this.velX);
    }
    if((this.y - this.size <= 0) || (height <= this.y + this.size)) {
        this.velY = -(this.velY);
    }
    this.x += this.velX;
    this.y += this.velY;
}
// Collision detection for the ball.
Ball.prototype.collisionDetect = function() {
    for(let i = 0; i < balls.length; i++) {
        if(this !== balls[i] && balls[i].exists) {
            const dx = this.x - balls[i].x;
            const dy = this.y - balls[i].y;
            const distance = Math.sqrt(dx*dx + dy*dy);
            if (distance < this.size + balls[i].size) {
                balls[i].color = this.color
                    = `rgb(${random(0,255)}, ${random(0,255)}, ${random(0,255)})`;
            }
        }
    }
}

// Define an `EvilCircle` class.
function EvilCircle(x, y, exists) {
    Shape.call(this, x, y, 20, 20, exists);
    this.color = "white";
    this.size = 10;
}
EvilCircle.prototype = Object.create(Shape.prototype);
Object.defineProperty(EvilCircle.prototype, "constructor", {
    value: EvilCircle,
    enumerable: false,
    writable: true
});
EvilCircle.prototype.draw = function() {
    ctx.beginPath();
    ctx.strokeStyle = this.color;
    ctx.lineWidth = 3;
    ctx.arc(this.x, this.y, this.size, 0, 2 * Math.PI);
    ctx.stroke();
}
EvilCircle.prototype.checkBounds = function() {
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
EvilCircle.prototype.setControls = function() {
    const _this = this;
    window.addEventListener("keydown", function(e) {
        if (65 === e.keyCode) {
            _this.x -= _this.velX;
        } else if (68 === e.keyCode) {
            _this.x += _this.velX;
        } else if (87 === e.keyCode) {
            _this.y -= _this.velY;
        } else if (83 === e.keyCode) {
            _this.y += _this.velY;
        }
    });
}
EvilCircle.prototype.collisionDetect = function() {
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

// define array to store balls and populate it
let totalBalls = 25;
scoreCounter.textContent = totalBalls;
const balls = [];
while(balls.length < totalBalls) {
    const size = random(10,20);
    const ball = new Ball(
        // ball position always drawn at least one ball width
        // away from the adge of the canvas, to avoid drawing errors
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
const player = new EvilCircle(50, 50, true);
player.setControls();
// define loop that keeps drawing the scene constantly
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
