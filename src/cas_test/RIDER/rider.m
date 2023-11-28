package cas_test::RIDER;

service caseoption Rider implements cas_test::Initialisations {
    override void initMatMono(in Int dim)
        out mahyco::materiau;
    override void initVarMono(in Int dim)
        in mahyco::node_coord,
        out mahyco::pseudo_viscosity,
        out mahyco::density,
        out mahyco::pressure,
        out mahyco::fracvol,
        out mahyco::mass_fraction,
        out mahyco::velocity_n,
        inout mahyco::velocity;
    override void initMat(in Int dim)
        in mahyco::node_coord,
        out mahyco::materiau;
    override void initVar(in Int dim)
        in mahyco::node_coord,
        out mahyco::pseudo_viscosity,
        out mahyco::density,
        out mahyco::pressure,
        out mahyco::fracvol,
        out mahyco::mass_fraction,
        out mahyco::velocity_n,
        inout mahyco::velocity;
}
