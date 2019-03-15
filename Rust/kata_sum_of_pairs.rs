fn sum_pairs(ints: &[i8], s: i8) -> Option<(i8, i8)> {
    /* Generate an upper-triangular matrix whose elements are the
     * sums of the row and column values:
     *
     * _+_|_11__3__7__5
     * 11 |    14 18 16
     *  3 |       10  8
     *  7 |          12
     *  5 |
     *
     * The first element that matches when going through the matrix
     * from left to right, columnwise, should be the answer.
     */
    let mut c = 1;
    while c < ints.len() {
        let mut r = 0;
        let ints_c = ints[c];
        while r < c {
            let sum = ints[r] + ints_c;
            if sum == s {
                return Some((ints[r], ints_c));
            }
            r += 1;
        }
        c += 1;
    }
    None
}