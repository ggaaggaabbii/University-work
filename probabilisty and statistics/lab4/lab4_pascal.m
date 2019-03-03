p = input('pro = ');
n = input('trials = ');
m = input('pascal runs = ');
for j = m:-1:0
    sum = 0;
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
        sum = sum + noTrials;
    end
    fprintf("%d\n",sum);
end