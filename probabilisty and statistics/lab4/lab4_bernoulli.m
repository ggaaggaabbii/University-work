p = input('pro = ');
nr = input('nr trials = ');
for v = nr:-1:0
    rand1 = rand();
    rez = 0;
    if rand1 <=p
        rez = 1;
    end
    fprintf("%d\n",rez);
end