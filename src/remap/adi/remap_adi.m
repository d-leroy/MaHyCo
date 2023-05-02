package remap.adi;

service caseoption RemapADI implements remap.Remap {
    /*! Définition de la valeur limite des petites fractions et autres */
    Real Threshold="1.e-10";
    /*!  projection type Euler (retour sur maillage initial) */
    Bool IsEulerScheme="true";
    /*! Définition de la valeur limite des petites fractions et autres */
    Int OrdreProjection="2";
    /*! Conservation de l energie totale lors de la projection */
    Bool ConservationEnergieTotale="false";
    /*!  projection pente borne en volume dans les mailles mixtes et en masse dans les mailles pures */
    Bool ProjectionPenteBorneMixte="false";
    /*!  identifiant du limiteur pour les mailles mixtes */
    Int ProjectionLimiteurId="0";
    /*!  identifiant du limiteur pour les mailles pures */
    Int ProjectionLimiteurPureId="0";
    /*!  projection avec l'algorithme pente-borne */
    Bool ProjectionPenteBorne="false";
    /*!  projection avec l'algorithme pente-borne en evitant l'artefact de debar avec la valeur moyenne (1) ou valeur aux mailles (2) */
    Int ProjectionPenteBorneDebarFix="0";
    /*!  identifiant de la methode de calcul du flux de masse duale */
    Int CalculFluxMasse="0";

    override remap.Remap.appliRemap
        in remap.sens_projection
        call remap.Remap.synchronizeUremap,
        synchronizeDualUremap,
        computeGradPhiFace,
        computeGradPhiCell,
        computeUpwindFaceQuantitiesForProjection,
        computeUremap,
        computeDualUremap,
        remap.Remap.remapVariables;
    
    override remap.Remap.resizeRemapVariables
        out mahyco.u_lagrange, out mahyco.u_dual_lagrange, out mahyco.phi_lagrange,
        out mahyco.phi_dual_lagrange, out mahyco.dual_grad_phi, out remap.grad_phi,
        out remap.phi_face, out remap.grad_phi_face, out remap.delta_phi_face_ar,
        out remap.delta_phi_face_av, out remap.dual_phi_flux, out remap.front_flux_mass_env,
        out remap.back_flux_mass_env, out remap.back_flux_contrib_env, out remap.front_flux_contrib_env;
    
    override remap.Remap.synchronizeUremap
        out mahyco.phi_lagrange, out mahyco.u_lagrange, out remap.dual_phi_flux,
        out mahyco.est_mixte, out mahyco.est_pure;
    
    override remap.Remap.remapVariables
        in mahyco.euler_volume, in mahyco.u_lagrange, in mahyco.u_dual_lagrange,
        out mahyco.est_pure, out mahyco.velocity, out mahyco.node_mass,
        inout mahyco.cell_volume, inout remap.cell_status, inout mahyco.est_mixte, inout mahyco.cell_mass, inout mahyco.fracvol,
        inout mahyco.mass_fraction, inout mahyco.pseudo_viscosity, inout mahyco.density, inout mahyco.internal_energy;
    
    def void synchronizeDualUremap()
        out mahyco.phi_dual_lagrange, out mahyco.u_dual_lagrange;
    
    def void computeGradPhiFace(in Int idir, in Int nb_vars_to_project, in Int nb_env)
        in mahyco.face_normal, in mahyco.cell_coord, in mahyco.phi_lagrange,
        in mahyco.face_coord, in mahyco.cell_coord,
        out remap.is_dir_face, out remap.grad_phi_face,
        inout remap.deltax_lagrange, inout remap.h_cell_lagrange;
    
    def void computeGradPhiCell(in Int idir, in Int nb_vars_to_project, in Int nb_env)
        in mahyco.outer_face_normal, in mahyco.face_normal_velocity,
        in mahyco.face_length_lagrange, in remap.is_dir_face,
        out remap.grad_phi, out remap.dual_phi_flux, out remap.delta_phi_face_av, out remap.delta_phi_face_ar,
        inout mahyco.est_mixte, inout mahyco.est_pure
        call computeGradPhiCell_PBorn0_LimC;

    // TODO: templated function?
    def void computeGradPhiCell_PBorn0_LimC(in Int idir, in Int nb_vars_to_project)
        in remap.grad_phi_face,
        out remap.grad_phi, out remap.delta_phi_face_ar, out remap.delta_phi_face_av;

    def void computeDualGradPhi_LimC(in Int idir)
        in mahyco.phi_dual_lagrange, in mahyco.node_coord,
        out mahyco.dual_grad_phi;

    def void computeUpwindFaceQuantitiesForProjection(in Int idir, in Int nb_vars_to_project, in Int nb_env)
        in mahyco.face_normal_velocity, in remap.deltax_lagrange, in mahyco.phi_lagrange,
        in mahyco.face_coord, in mahyco.cell_coord, in mahyco.face_normal, in remap.grad_phi,
        in remap.delta_phi_face_av, in remap.delta_phi_face_ar, in remap.h_cell_lagrange, in mahyco.est_mixte,
        in mahyco.est_pure,
        inout remap.phi_face
        call computeUpwindFaceQuantitiesForProjection_PBorn0_O2;
    
    def void computeUpwindFaceQuantitiesForProjection_PBorn0_O2(in Int idir, in Int nb_vars_to_project)
        in remap.deltax_lagrange, in mahyco.face_normal_velocity, in mahyco.phi_lagrange,
        in mahyco.face_coord, in mahyco.face_normal, in mahyco.cell_coord, in remap.grad_phi,
        out remap.phi_face;
    
    def void computeUremap(in Int idir, in Int nb_vars_to_project, in Int nb_env)
        in mahyco.face_normal, in mahyco.face_length_lagrange, in mahyco.outer_face_normal,
        in remap.phi_face,
        out remap.dual_phi_flux, out mahyco.est_mixte, out mahyco.est_pure,
        inout mahyco.u_lagrange, inout mahyco.phi_lagrange
        call computeUremap_PBorn0;
    
    def void computeUremap_PBorn0(in Int idir, in Int nb_vars_to_project, in Int nb_env)
        in mahyco.face_normal, in mahyco.face_normal_velocity, in mahyco.face_length_lagrange,
        in mahyco.outer_face_normal, in remap.phi_face,
        out remap.dual_phi_flux, out mahyco.est_mixte, out mahyco.est_pure,
        inout mahyco.u_lagrange, inout mahyco.phi_lagrange;
    
    def void computeDualUremap()
        in remap.dual_phi_flux, in mahyco.node_coord,
        inout mahyco.dual_grad_phi,
        inout remap.back_flux_contrib_env, inout remap.front_flux_contrib_env,
        inout remap.back_flux_mass, inout remap.front_flux_mass,
        inout remap.back_flux_mass_env, inout remap.front_flux_mass_env,
        inout mahyco.u_dual_lagrange, inout mahyco.phi_dual_lagrange
        call computeDualGradPhi_LimC;
}