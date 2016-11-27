class Fraction {
	public final static Fraction ZERO = Fraction . valueOf (0);
	public final static Fraction ONE = Fraction . valueOf (1);
	BigInteger p, q;
	Fraction ( BigInteger x) {p = x;q = BigInteger .ONE;}
	Fraction ( BigInteger u, BigInteger v) {
		if (v. signum () < 0) {	u = u. negate ();v = v. negate ();}
		BigInteger d = u.gcd(v);
		if (!d. equals ( BigInteger .ONE )) {
			u = u. divide (d);
			v = v. divide (d);
		}
		p = u; q = v;
	}
	public static Fraction valueOf (int x) {
		return new Fraction ( BigInteger . valueOf (x));
	}
	Fraction add( Fraction o) {
		return new Fraction (p.multiply(o.q).add(o.p.multiply(q)), q.multiply(o.q));
	}
	Fraction subtract ( Fraction o) {
		return new Fraction (p.multiply(o.q).subtract(o.p. multiply(q)),
q.multiply(o.q));
	}
	Fraction multiply ( Fraction o) {
		return new Fraction (p.multiply(o.p), q.multiply(o.q));
	}
	Fraction divide ( Fraction o) {
		return new Fraction (p. multiply (o.q), q. multiply (o.p));
	}
	Fraction negate () {return new Fraction (p. negate (), q);}
	Fraction inverse () {return new Fraction (q, p);}
	public boolean equals ( Object o) {
		return p.multiply(((Fraction)o).q).equals(q.multiply(((Fraction)o).p));
	}
	public String toString () {
		if (q. equals ( BigInteger .ONE )) return p. toString ();
		else	return p. toString () + "/" + q. toString ();
	}
}
