package cas_test.SEDOV;

service caseoption Sedov implements cas_test.Initialisations {
    override cas_test.Initialisations.initMatMono
        out mahyco.materiau;
    override cas_test.Initialisations.initVarMono
        in mahyco.node_coord,
        in mahyco.cell_volume,
        out mahyco.density,
        out mahyco.pressure,
        out mahyco.fracvol,
        out mahyco.mass_fraction,
        out mahyco.velocity,
        inout mahyco.internal_energy;
    override cas_test.Initialisations.initMat
        in mahyco.node_coord,
        out mahyco.materiau;
    override cas_test.Initialisations.initVar
        in mahyco.node_coord,
        in mahyco.cell_volume,
        out mahyco.density,
        out mahyco.pressure,
        out mahyco.fracvol,
        out mahyco.mass_fraction,
        out mahyco.velocity,
        inout mahyco.internal_energy;
}
