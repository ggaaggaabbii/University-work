BEGIN{
}{
	sum = 0;
	nr = 0;
	for (i = 1; i <= NF; ++i) {
		sum += $i;
		if ($i ~ "[0-9]+")
			++nr;
	}
	if (NR % 2) {
		if (nr)
			printf("%lf\n",  sum / nr);
		else
			print "No numbers on the line"
	} else {
		print sum;
	}
}
END{
}
