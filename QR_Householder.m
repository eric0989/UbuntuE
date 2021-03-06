N = 3;

for i = 1:N
	for j = 1:N
		A(i, j) = N*(i-1) + j;
	end
end

R = A;
I = eye(N);
Q = eye(N);

for k = 1:N
	e = I(k:N, k);
	x = R(k:N, k);
	v = sign(x(1))*norm(x)*e + x;
	v = v/norm(v);
	R(k:N, k:N) = R(k:N, k:N) - 2*v*(v'*R(k:N, k:N));
	V(k:N, k) = v;
%	Q(k:N, k:N) = Q(k:N, k:N) - 2*v*(v'*Q(k:N, k:N));
end

for k = N:-1:1
	Q(k:N, k:N) = Q(k:N, k:N) - 2*V(k:N, k)*(V(k:N, k)'*Q(k:N, k:N));
end

A
Q
R
QR = Q*R
err = max(max(abs(QR-A)))
