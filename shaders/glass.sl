surface glass(float eta=1.5;
	float Ka = 1;
	float Kd = 1;
	float Ks = 1;
	float roughness = 0.5;) {
	vector R,T;
	vector In;
	float Kr,Kt;
	normal Nf;

	// Normalize some vectors
	Nf = faceforward(normalize(N),I);
	In = normalize(I);
	Ci = 0;

	// Compute the reflection and refraction
	fresnel(In,Nf,(In.N < 0 ? 1/eta : eta),Kr,Kt,R,T);

	if (I.N < 0) {
		Ci = Ks*specular(Nf,-In,roughness);
	}

	// Trace the reflection / refraction
	if (Kr > 0.01) Ci += Kr*trace(P,R);
	if (Kt > 0.01) Ci += Cs* Kt*trace(P,T);

	Ci *= Os;
	Oi = Os;
}

