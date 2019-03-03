p = input('pro = ');
nr = input('nr trials = ');
bnr = input('nr of binomial = ');
for k = bnr:-1:0
    sum = 0;
    for v = nr:-1:0
        rand1 = rand();
        rez = 0;
        if rand1 <=p
            rez = 1;
        end
        sum = sum + rez;
    end
    fprintf("%d\n",sum);
end