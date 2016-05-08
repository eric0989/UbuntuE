N = input("Please enter N = ");

for i = 1:N
	X(i) = i-1;
endfor

X;
Z(1) = 0;
Z(N+2) = 0;

for i = 2:N+1
	Z(i) = X(i-1);
endfor

for i = N+3:2*N+2
	Z(i) = -X(2*N+3-i);
endfor

Z;
A = imag((fft(Z))/(-2));
S_X = A(2:N+1);
B = imag((fft(A))/(-2));
SS_X = B(2:N+1)*(2/(N+1));

err = max(abs(SS_X-X))
