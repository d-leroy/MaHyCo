package cas_test::OTHER;

service caseoption Other implements cas_test::Initialisations {
    override void initMatMono(in Int dim);
    override void initVarMono(in Int dim);
    override void initMat(in Int dim)
        in mahyco::cell_coord,
        out mahyco::materiau;
    override void initVar(in Int dim)
        in mahyco::cell_coord,
        out mahyco::pseudo_viscosity,
        out mahyco::density,
        out mahyco::pressure,
        out mahyco::internal_energy,
        out mahyco::fracvol,
        out mahyco::mass_fraction,
        out mahyco::velocity_n,
        inout mahyco::velocity;
}
