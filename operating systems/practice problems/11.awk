BEGIN {
	sum = 0
}{
	sum += $2
}
END {
	printf("%.2lf\n", sum / (NR - 1))
}
