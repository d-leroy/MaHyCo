package cas_test.OTHER;

service caseoption Other implements cas_test.Initialisations {
    override cas_test.Initialisations.initMatMono;
    override cas_test.Initialisations.initVarMono;
    override cas_test.Initialisations.initMat
        in mahyco.cell_coord,
        out mahyco.materiau;
    override cas_test.Initialisations.initVar
        in mahyco.cell_coord,
        out mahyco.pseudo_viscosity,
        out mahyco.density,
        out mahyco.pressure,
        out mahyco.internal_energy,
        out mahyco.fracvol,
        out mahyco.mass_fraction,
        out mahyco.velocity_n,
        inout mahyco.velocity;
}
