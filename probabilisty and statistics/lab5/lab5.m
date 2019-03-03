%1
conflevel = input('conf. level(in(0,1))='); %1-alfa
alfa = 1 - conflevel;

X = [7 7 4 5 9 9 ...
    4 12 8 1 8 7 ...
    3 13 2 1 17 7 ...
    12 5 6 2 1 13 ...
    14 10 2 4 9 11 ...
    3 5 12 6 10 7] ; %sample data

n = length(X);

xbar = mean(X);

%a) sigma known
sigma = 5
q1 = norminv(1 - alfa / 2, 0, 1);
q2 = norminv(alfa / 2, 0, 1);  % q2 = -q1 sym N(0,1)
confint1 = xbar - (sigma / sqrt(n)) * q1;
confint2 = xbar - (sigma / sqrt(n)) * q2;
fprintf('C.I. for the population mean, niu, case sigma known is (%3.5f, %3.5f)\n', confint1, confint2);


%b) sigma unknown
s = std(X);
t1 = tinv(1 - alfa / 2,n - 1);
t2 = tinv(alfa / 2,n - 1); % t2 = -t1 sym T(n-1)
confint1 = xbar - (s / sqrt(n)) * t1;
confint2 = xbar - (s / sqrt(n)) * t2;
fprintf('C.I. for the population mean, niu, case sigma unknown is (%3.5f, %3.5f)\n', confint1, confint2);

%c)
sampleVariance = var(X); %s patrat; the sample variance
q1 = chi2inv(1 - alfa / 2,n - 1);
q2 = chi2inv(alfa / 2,n - 1); % NOT sym
confint1 = (n - 1) * sampleVariance / q1;
confint2 = (n - 1) * sampleVariance / q2;
fprintf('C.I. for the population variance, sigma squared, is (%3.5f, %3.5f)\n', confint1, confint2);
fprintf('C.I. for the population std. dev., sigma, is (%3.5f, %3.5f)\n', sqrt(confint1), sqrt(confint2));

%2
conflevel = input('conf. level(in(0,1))='); %1 - alfa
alfa = 1 - conflevel;

X1 = [22.4 21.7 ...
      24.5 23.4 ...
      21.6 23.3 ...
      22.4 21.6 ...
      24.8 20.0 ] ; %sample data 1
  
X2 = [17.7 14.8  ...
      19.6 19.6  ...
      12.1 14.8  ...
      15.4 12.6  ...
      14.0 12.2  ] ; %sample data 2

n1 = length(X1);
n2 = length(X2);

xbar1 = mean(X1);
xbar2 = mean(X2);

sampleVariance1 = var(X1);
sampleVariance2 = var(X2);

%a) sigma 1 = sigma 2
spSquared = ((n1 - 1) * sampleVariance1 + (n2 - 1) * sampleVariance2) / (n1 + n2 - 2);
t1 = tinv(1 - alfa / 2, n1 + n2 - 2);
t2 = -t1;

confint1 = (xbar1 - xbar2 - t1 * sqrt(spSquared) * (sqrt(1 / n1 + 1 / n2)));
confint2 = (xbar1 - xbar2 - t2 * sqrt(spSquared) * (sqrt(1 / n1 + 1 / n2)));
fprintf('C.I. for the difference of population means, niu1 - niu2,\n case sigma1 = sigma2, is (%3.5f, %3.5f)\n', confint1, confint2);


%b) sigma 1 != sigma 2
c = (sampleVariance1 / n1) / ((sampleVariance1 / n1) + (sampleVariance2 / n2));
oneOverN = (c ^ 2 / (n1 - 1) + ((1 - c) ^ 2) / (n2 - 1));
n = 1 / oneOverN;

t1 = tinv(1 - alfa / 2,n);
t2 = -t1;

confint1 = (xbar1 - xbar2 - t1 * (sqrt(sampleVariance1 / n1 + sampleVariance2 / n2)));
confint2 = (xbar1 - xbar2 - t2 * (sqrt(sampleVariance1 / n1 + sampleVariance2 / n2)));
fprintf('C.I. for the difference of population means, niu1 - niu2,\n case sigma1 != sigma2, is (%3.5f, %3.5f)\n', confint1, confint2);

%c)
f1 = finv(1 - alfa / 2, n1 - 1, n2 - 1);
f2 = finv(alfa / 2, n1 - 1, n2 - 1); %not symmetric

confint1 = sampleVariance1 / (f1 * sampleVariance2);
confint2 = sampleVariance1 / (f2 * sampleVariance2);
fprintf('C.I. for the ratio of population variances, sigma1Squared / sigma2Squared,\n is (%3.5f, %3.5f)\n', confint1, confint2);