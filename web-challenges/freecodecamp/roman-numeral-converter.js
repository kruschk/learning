/* Convert a number to a Roman Numeral, as a string. It will only
 * work for numbers up to 3999, but larger numbers can be
 * represented by defining a symbol for larger factors of ten
 * (e.g. 10,000). */
function convertToRoman(num) {
    /* Define powers of ten. */
    let powersTen = ["I", "X", "C", "M"];
    /* Array of powers of ten divided by two. */
    let halfPowersTen = ["", "V", "L", "D"];
    /* Initialize an array to hold the Roman Numeral. */
    let romanArr = [];
    /* Go through each digit of num. Note that the Roman Numeral
     * gets built in reverse order; it is reversed later. */
    for (let i = 0; num !== 0; i++) {
        /* Get the least significant digit. */
        let numAtPos = num%10;
        /* Divide the number by 10 and discard the fractional part
         * so that the next digit becomes the least significant. */
        num = Math.floor(num/10);
        /* 9 becomes the next power of ten followed by the current
         * power of ten, e.g. 9 = IX, 90 = XC. */
        if (numAtPos === 9) {
            romanArr.push(powersTen[i+1]);
            romanArr.push(powersTen[i]);
        } 
        /* 4 becomes the next half power of ten followed by the
         * current power of ten, e.g. 4 = IV, 40 = XL. */
        else if (numAtPos === 4) {
            romanArr.push(halfPowersTen[i+1]);
            romanArr.push(powersTen[i]);
        }
        else {
            /* halfPowNumAtPos will be 0 or 1, depending on if
             * numAtPos is in the range [0, 4] or [5, 9]. */
            let halfPowNumAtPos = Math.floor(numAtPos/5);
            /* Set numAtPos to the remainder after dividing by 5, so
             * it's in the range [0, 4]. */
            numAtPos %= 5;
            /* Push powers of 10 onto romanArr until we run out of
             * numAtPos. */
            while (numAtPos) {
                romanArr.push(powersTen[i]);
                numAtPos--;
            }
            /* Push the next half powers of 10 onto romanArr until
             * we run out of halfPowNumAtPos. */
            while (halfPowNumAtPos) {
                romanArr.push(halfPowersTen[i+1]);
                halfPowNumAtPos--;
            }
        }
    }
    /* Reverse the array and join it to make a string. */
    return romanArr.reverse().join("");
}

console.clear();
console.log(convertToRoman(99));
