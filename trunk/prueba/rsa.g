generarp:=function(n)
local p;
p:=Random([10^(n-1)..10^n-1]);
while not IsPrime(p) do 
	p:=Random([10^(n-1)..10^n-1]);
	od;
return p;
end;

parametrosRSA:=function(nd)
local n,f,d,e,p,q;
p:=generarp(nd);
q:=generarp(nd);
n:=p*q;
f:=(p-1)*(q-1);
d:=Random([3..f-1]);
while Gcd(f,d)<>1 do 
	d:=Random([3..f-1]);
	od;
e:=PowerMod(d,-1,f);
return [n,p,q,f,d,e];
end;

