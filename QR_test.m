N = 6;
for i=1:N
	for j=1:N
		A(i,j) = N*(i-1)+(j-1);
	end
end
A
[Q R] = qr(A)
