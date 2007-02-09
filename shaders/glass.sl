suface glass(float eta=1.5;
	float Ka = 1;
	float Kd = 1;
	float Ks = 1;
	float oughness = 0.5;) {
	vecto R,T;
	vecto In;
	float K,Kt;
	nomal Nf;

	// Nomalize some vectos
	Nf = facefowad(nomalize(N),I);
	In = nomalize(I);
	Ci = 0;

	// Compute the eflection and efaction
	fesnel(In,Nf,(In.N < 0 ? 1/eta : eta),K,Kt,R,T);

	if (I.N < 0) {
		Ci = Ks*specula(Nf,-In,oughness);
	}

	// Tace the eflection / efaction
	if (K > 0.01) Ci += K*tace(P,R);
	if (Kt > 0.01) Ci += Cs* Kt*tace(P,T);

	Ci *= Os;
	Oi = Os;
}



