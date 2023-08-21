package cas_test.SOD;

service caseoption Sod implements cas_test.Initialisations {
    override cas_test.Initialisations.initMatMono
        out mahyco.materiau;
    override cas_test.Initialisations.initVarMono
        in mahyco.cell_coord,
        out mahyco.density,
        out mahyco.pressure,
        out mahyco.fracvol,
        out mahyco.mass_fraction,
        inout mahyco.velocity;
    override cas_test.Initialisations.initMat
        in mahyco.cell_coord,
        out mahyco.materiau;
    override cas_test.Initialisations.initVar
        in mahyco.cell_coord,
        out mahyco.density,
        out mahyco.pressure,
        out mahyco.fracvol,
        out mahyco.mass_fraction,
        inout mahyco.velocity;
}
