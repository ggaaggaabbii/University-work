BEGIN{
}{
	if (NR % 2)
		print $0
}
END{
	print NR
}
