BEGIN{
	FS = ":"
	time = 0;
	l = 0;
}
/popb/{
	time += $2 * 60 + $3;
	l++;
}
END{
	printf("popb %lf\n", 1.0 * time / l);
}
