p = input('p = ');
n = input('n = ');

function ans = Bern(p)
  r = rand();
  ans = 0;
  if r <= p
    ans = 1;
  end
end

function ans = Bino(n, p)
  rez = 0
  for v = 0:1:n
    rez += Bern(p)
  end
  ans = rez
end

rez = Bino(n, p)