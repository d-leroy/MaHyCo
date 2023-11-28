package cas_test::SEDOV;

service caseoption Sedov implements cas_test::Initialisations {
    override void initMatMono(in Int dim)
        out mahyco::materiau;
    override void initVarMono(in Int dim)
        in mahyco::node_coord,
        in mahyco::cell_volume,
        out mahyco::density,
        out mahyco::pressure,
        out mahyco::fracvol,
        out mahyco::mass_fraction,
        out mahyco::velocity,
        inout mahyco::internal_energy;
    override void initMat(in Int dim)
        in mahyco::node_coord,
        out mahyco::materiau;
    override void initVar(in Int dim)
        in mahyco::node_coord,
        in mahyco::cell_volume,
        out mahyco::density,
        out mahyco::pressure,
        out mahyco::fracvol,
        out mahyco::mass_fraction,
        out mahyco::velocity,
        inout mahyco::internal_energy;
}
