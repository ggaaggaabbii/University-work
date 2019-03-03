X = []; 
for i = 1:100000 
	a = rand();
	b = rand(); 
	c = rand(); 
	count = 0; 
	if (a > 0.5)
		count = count + 1; 
	endif 
	if (b > 0.5) 
		count = count + 1; 
	endif 
	if (c > 0.5) 
		count = count + 1;
	endif
	 X = [X count]; 
endfor
hist(X);