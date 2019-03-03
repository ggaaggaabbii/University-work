p = input('p = ');
n = input('n = ');

function ans = Bern(p)
  r = rand();
  ans = 0;
  if r <= p
    ans = 1;
  end
end

function ans = Geo(p)
  rez = 0;
  noTrials = 0;
  while rez == 0
    x=Bern(p);
    noTrials = noTrials + 1;
    if x == 1
      rez = 1;
    end
  end
    ans = noTrials
end

function ans = Pas(n, p)
  rez = 0;
  for i = n:-1:0
    rez += Geo(p)
    fprintf("%d\n",rez);
  end
  ans = rez
end

rez = Pas(n, p)