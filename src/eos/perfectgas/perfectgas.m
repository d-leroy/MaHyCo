package eos::perfectgas;

service caseoption PerfectGas implements eos::EquationOfState {
    /*!
     * Définition de la tension limite
     */
    opt Real limit_tension = "0.0";
    
    override void initEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::pressure, in mahyco::density,
        out mahyco::internal_energy, out mahyco::sound_speed;

    override void applyEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::density, in mahyco::internal_energy, //in adiabatic_cst,
        inout mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;

    override void applyOneCellEOS(in types_mahyco::IMeshEnvironment env, in EnvCell ev)
        in mahyco::density, in mahyco::internal_energy,
        out mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;
}

service caseoption PerfectGasPAcc implements eos::EquationOfState {
    /*!
     * Définition de la tension limite
     */
    opt Real limit_tension = "0.0";
    
    override void initEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::pressure, in mahyco::density,
        out mahyco::internal_energy, out mahyco::sound_speed;

    override void applyEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::density, in mahyco::internal_energy, //in adiabatic_cst,
        inout mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;

    override void applyOneCellEOS(in types_mahyco::IMeshEnvironment env, in EnvCell ev)
        in mahyco::density, in mahyco::internal_energy,
        out mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;
}

service caseoption PerfectGasNAcc implements eos::EquationOfState {
    /*!
     * Définition de la tension limite
     */
    opt Real limit_tension = "0.0";
    
    override void initEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::pressure, in mahyco::density,
        out mahyco::internal_energy, out mahyco::sound_speed;

    override void applyEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::density, in mahyco::internal_energy, //in adiabatic_cst,
        inout mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;

    override void applyOneCellEOS(in types_mahyco::IMeshEnvironment env, in EnvCell ev)
        in mahyco::density, in mahyco::internal_energy,
        out mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;
}

service caseoption PerfectGasAccWithSupport implements eos::EquationOfState {
    /*!
     * Définition de la tension limite
     */
    opt Real limit_tension = "0.0";
    
    override void initEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::pressure, in mahyco::density,
        out mahyco::internal_energy, out mahyco::sound_speed;

    override void applyEOS(inout types_mahyco::IMeshEnvironment env)
        call applyEOSWithSupport;

    override void applyOneCellEOS(in types_mahyco::IMeshEnvironment env, in EnvCell ev)
        in mahyco::density, in mahyco::internal_energy,
        out mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;

    def void applyEOSWithSupport(inout types_mahyco::IMeshEnvironment env) { EnvCell }
        in mahyco::density, in mahyco::internal_energy, in adiabatic_cst,
        inout mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;
}

service caseoption PerfectGasWithSupport implements eos::EquationOfState {
    /*!
     * Définition de la tension limite
     */
    opt Real limit_tension = "0.0";
    
    override void initEOS(inout types_mahyco::IMeshEnvironment env)
        in mahyco::pressure, in mahyco::density,
        out mahyco::internal_energy, out mahyco::sound_speed;

    override void applyEOS(inout types_mahyco::IMeshEnvironment env)
        call applyEOSWithSupport;

    override void applyOneCellEOS(in types_mahyco::IMeshEnvironment env, in EnvCell ev)
        in mahyco::density, in mahyco::internal_energy,
        out mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;

    def void applyEOSWithSupport(inout types_mahyco::IMeshEnvironment env) { EnvCell }
        in mahyco::density, in mahyco::internal_energy, in adiabatic_cst,
        inout mahyco::pressure, out mahyco::sound_speed, out mahyco::dpde;
}
