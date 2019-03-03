x = -10:0.1:10
y = normpdf(x, 0, 1)
y1 = chi2pdf(x, 4)
y2 = tpdf(x, 2)
y3 = fpdf(x, 5, 2)
plot(x, y, x, y1, x, y2, x, y3)


printf("norm x <=0 : %f\n", normcdf(0,0,1) - normcdf(-inf, 0, 1))
printf("chi2 x <=0 : %f\n", chi2cdf(0, 4) - chi2cdf(-inf, 4))
printf("t x <=0 : %f\n", tcdf(0,2) - tcdf(-inf, 2))
printf("f x <=0 : %f\n", fcdf(0,5,2) - fcdf(-inf, 5, 2))
printf("norm x >1 : %f\n", (normcdf(inf,0,1) - normcdf(1, 0, 1)))
printf("chi2 x >1 : %f\n",  (chi2cdf(inf,4) - chi2cdf(1, 4)))
printf("t x >1 : %f\n",  (tcdf(inf,2) - tcdf(1, 2)))
printf("f x >1 : %f\n",  (fcdf(inf,5,2) - fcdf(1, 5, 2)))

norminv(X, 0, 1)