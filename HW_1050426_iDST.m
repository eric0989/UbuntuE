N = input("Please enter N = ");

for i = 1:N
  X(i) = i-1;
endfor

S_X = DST(X)

SS_X = DST(S_X)*(2/(N+1))

err = max(abs(SS_X-X))
