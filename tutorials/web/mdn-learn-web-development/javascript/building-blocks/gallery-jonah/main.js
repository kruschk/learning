"use strict";
const displayedImage = document.querySelector(".displayed-img");
const thumbBar = document.querySelector(".thumb-bar");
const btn = document.querySelector("button");
const overlay = document.querySelector(".overlay");
// Looping through images
for (let i = 1; i <= 5; i++) {
    const newImage = document.createElement("img");
    newImage.setAttribute("src", "images/pic" + i + ".jpg");
    thumbBar.appendChild(newImage);
    newImage.addEventListener("click", (e) => {
        setDisplayedImage(e.target.getAttribute("src"));
    });
}
function setDisplayedImage(path) {
    displayedImage.setAttribute("src", path);
}
// Wiring up the Darken/Lighten button
btn.addEventListener("click", (e) => {
    let btnClass = e.target.getAttribute("class");
    if ("dark" === btnClass) {
        e.target.setAttribute("class", "light");
        e.target.textContent = "Lighten";
        overlay.style.backgroundColor = "rgba(0, 0, 0, 0.5)";
    }
    else {
        e.target.setAttribute("class", "dark");
        e.target.textContent = "Darken";
        overlay.style.backgroundColor = "rgba(0, 0, 0, 0.0)";
    }
});
