p = input('pro = ');
n = input('trials = ');
for i = n:-1:0
    rez = 0;
    noTrials = 0;
    while rez == 0
        x=rand;
        noTrials = noTrials + 1;
        if x <= p
            rez = 1;
        end
    end
    fprintf("%d\n",noTrials);
end