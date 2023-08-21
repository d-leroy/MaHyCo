package cas_test.RIDER;

service caseoption Rider implements cas_test.Initialisations {
    override cas_test.Initialisations.initMatMono
        out mahyco.materiau;
    override cas_test.Initialisations.initVarMono
        in mahyco.node_coord,
        out mahyco.pseudo_viscosity,
        out mahyco.density,
        out mahyco.pressure,
        out mahyco.fracvol,
        out mahyco.mass_fraction,
        out mahyco.velocity_n,
        inout mahyco.velocity;
    override cas_test.Initialisations.initMat
        in mahyco.node_coord,
        out mahyco.materiau;
    override cas_test.Initialisations.initVar
        in mahyco.node_coord,
        out mahyco.pseudo_viscosity,
        out mahyco.density,
        out mahyco.pressure,
        out mahyco.fracvol,
        out mahyco.mass_fraction,
        out mahyco.velocity_n,
        inout mahyco.velocity;
}
