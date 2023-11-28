package eos::stiffenedgas;

service caseoption StiffenedGas implements eos::EquationOfState {

    /*! Définition de la tension limite */
    opt Real tension_limit_cst = "0.01";

    override void initEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::pressure, in mahyco::density,
        out mahyco::internal_energy, out mahyco::sound_speed;

    override void applyEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::internal_energy, in mahyco::density, //in tension_limit_cst, in adiabatic_cst,
        out mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;

    override void applyOneCellEOS(in types_mahyco::IMeshEnvironment env, in EnvCell ev)
        in mahyco::internal_energy, in mahyco::density,
        out mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;
}

service caseoption StiffenedGasAcc implements eos::EquationOfState {

    /*! Définition de la tension limite */
    opt Real tension_limit_cst = "0.01";

    override void initEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::pressure, in mahyco::density,
        out mahyco::internal_energy, out mahyco::sound_speed;

    override void applyEOS(inout types_mahyco::IMeshEnvironment env)
        call applyEOSWithSupport;

    override void applyOneCellEOS(in types_mahyco::IMeshEnvironment env, in EnvCell ev)
        in mahyco::internal_energy, in mahyco::density,
        out mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;

    def void applyEOSWithSupport(inout types_mahyco::IMeshEnvironment env) {EnvCell}
        in mahyco::internal_energy, in mahyco::density, in tension_limit_cst, in adiabatic_cst,
        out mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;
}