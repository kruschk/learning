void permute(char *str, const unsigned int l, const unsigned int r) {
	if (l == r) {
		printf("%s\n", str);
	}
	else {
		unsigned int i;
		for (i = l; i <= r; i++) {
			char temp;
			SWAP(str, i, l);
			permute(str, l + 1, r);
			SWAP(str, i, l);
		}
	}
	return;
}
