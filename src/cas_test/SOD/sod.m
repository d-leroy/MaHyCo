package cas_test::SOD;

service caseoption Sod implements cas_test::Initialisations {
    override void initMatMono(in Int dim)
        out mahyco::materiau;
    override void initVarMono(in Int dim)
        in mahyco::cell_coord,
        out mahyco::density,
        out mahyco::pressure,
        out mahyco::fracvol,
        out mahyco::mass_fraction,
        inout mahyco::velocity;
    override void initMat(in Int dim)
        in mahyco::cell_coord,
        out mahyco::materiau;
    override void initVar(in Int dim)
        in mahyco::cell_coord,
        out mahyco::density,
        out mahyco::pressure,
        out mahyco::fracvol,
        out mahyco::mass_fraction,
        inout mahyco::velocity;
}
