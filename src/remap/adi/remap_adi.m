package remap.adi;

service caseoption RemapADI implements remap.Remap {
    /*!  identifiant de la methode de calcul du flux de masse duale */
    Int calcul_flux_masse="0";

    override remap.Remap.appliRemap
        in remap.sens_projection
        call remap.Remap.synchronizeUremap,
        call synchronizeDualUremap,
        call computeGradPhiFace,
        call computeGradPhiCell,
        call computeUpwindFaceQuantitiesForProjection,
        call computeUremap,
        call computeDualUremap,
        call remap.Remap.remapVariables;
    
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
    
    def void computeAndLimitGradPhi(in types_mahyco.Limiteur projectionLimiterId, in Face frontFace, in Face backFace, 
                                    in Cell cell, in Cell frontcell, in Cell backcell, in Int nb_vars)
        out remap.grad_phi,
        in remap.grad_phi_face,
        in mahyco.phi_lagrange,
        in remap.h_cell_lagrange
        call fluxLimiter, call fluxLimiterG;
    
    def void computeDualGradPhi(in Node inode, in Node frontfrontnode, in Node frontnode, 
                                in Node backnode, in Node backbacknode, in Int idir)
        in mahyco.phi_dual_lagrange, in mahyco.node_coord
        call computeAndLimitGradPhiDual, call fluxLimiter;
    
    def void computeAndLimitGradPhiDual(in types_mahyco.Limiteur projectionLimiterId, in Node inode, in Node frontnode, in Node backnode, 
                                        in Real[3] grad_front, in Real[3] grad_back, in Real h0, in Real hplus, in Real hmoins)
        in mahyco.phi_dual_lagrange,
        out mahyco.dual_grad_phi
        call fluxLimiter, call fluxLimiterG;
    
    def Real fluxLimiter(in types_mahyco.Limiteur projectionLimiterId, in Real r);
    
    def Real fluxLimiterG(in types_mahyco.Limiteur projectionLimiterId, in Real gradplus, in Real gradmoins,
                          in Real y0, in Real yplus,in Real ymoins,
                          in Real h0, in Real hplus, in Real hmoins);
    
    def void computeFluxPP(in Cell cell, in Cell frontcell, in Cell backcell,
                           in Real face_normal_velocity, in Real deltat_n,
                           in Int type, in Real flux_threshold, 
                           in Int projectionPenteBorneDebarFix, 
                           in Real dual_normal_velocity,
                           in Int calcul_flux_dual,
                           inout types_mahyco.RealArrayView flux,
                           inout types_mahyco.RealArrayView flux_dual,
                           in Int nbmat, in Int nb_vars)
        in remap.h_cell_lagrange,
        in mahyco.phi_lagrange,
        in remap.grad_phi
        call computeY0,
        call computexgxd,
        call computeygyd,
        call intY;
    
    def Real computeY0(in types_mahyco.Limiteur projectionLimiterId, in Real y0, in Real yplus, in Real ymoins,
                       in Real h0, in Real hplus, in Real hmoins, in Int type);
    
    def Real computexgxd(in Real y0, in Real yplus, in Real ymoins, in Real h0,
                         in Real y0plus, in Real y0moins, in Int type);
    
    def Real computeygyd(in Real y0, in Real yplus, in Real ymoins, in Real h0,
                         in Real y0plus, in Real y0moins, in Real grady,in Int type);
    
    def Real intY(in Real X,in Real x0,in Real y0, in Real x1, in Real y1);

    def void computeFluxPPPure(in Cell cell, in Cell frontcell, in Cell backcell, 
                               in Real face_normal_velocity, in Real deltat_n,
                               in Int type, in Real flux_threshold, 
                               in Int projectionPenteBorneDebarFix, 
                               in Real dual_normal_velocity,
                               in Int calcul_flux_dual,
                               inout types_mahyco.RealArrayView Flux,
                               inout types_mahyco.RealArrayView Flux_dual,
                               in Int nbmat, in Int nb_vars)
        in remap.h_cell_lagrange,
        in mahyco.phi_lagrange,
        in remap.grad_phi
        call computeY0,
        call computexgxd,
        call computeygyd,
        call intY;

    def void computeGradPhiFace(in Int idir, in Int nb_vars_to_project, in Int nb_env)
        in mahyco.face_normal, in mahyco.cell_coord, in mahyco.phi_lagrange, in mahyco.face_coord,
        out remap.is_dir_face, out remap.grad_phi_face,
        inout remap.deltax_lagrange, inout remap.h_cell_lagrange;
    
    def void computeGradPhiCell(in Int idir, in Int nb_vars_to_project, in Int nb_env)
        in mahyco.outer_face_normal, in mahyco.face_normal_velocity,
        in mahyco.face_length_lagrange, in remap.is_dir_face,
        out remap.grad_phi, out remap.dual_phi_flux, out remap.delta_phi_face_av, out remap.delta_phi_face_ar,
        inout mahyco.est_mixte, inout mahyco.est_pure;
        // call computeGradPhiCell_PBorn0_LimC;

    // TODO: templated function? at least import legacy function, that can be template functions
    // def void computeGradPhiCell_PBorn0_LimC(in Int idir, in Int nb_vars_to_project)
    //     in remap.grad_phi_face,
    //     out remap.grad_phi, out remap.delta_phi_face_ar, out remap.delta_phi_face_av;

    // def void computeDualGradPhi_LimC<types_mahyco.limiter>(in Int idir)
    //     in mahyco.phi_dual_lagrange, in mahyco.node_coord,
    //     out mahyco.dual_grad_phi;

    def void computeUpwindFaceQuantitiesForProjection(in Int idir, in Int nb_vars_to_project, in Int nb_env)
        in mahyco.face_normal_velocity, in remap.deltax_lagrange, in mahyco.phi_lagrange,
        in mahyco.face_coord, in mahyco.cell_coord, in mahyco.face_normal, in remap.grad_phi,
        in remap.delta_phi_face_av, in remap.delta_phi_face_ar, in remap.h_cell_lagrange, in mahyco.est_mixte,
        in mahyco.est_pure,
        inout remap.phi_face
        call computeUpwindFaceQuantitiesForProjectionPBorn0O2;
    
    def void computeUpwindFaceQuantitiesForProjectionPBorn0O2(in Int idir, in Int nb_vars_to_project)
        in remap.deltax_lagrange, in mahyco.face_normal_velocity, in mahyco.phi_lagrange,
        in mahyco.face_coord, in mahyco.face_normal, in mahyco.cell_coord, in remap.grad_phi,
        out remap.phi_face;
    
    def void computeUremap(in Int idir, in Int nb_vars_to_project, in Int nb_env)
        in mahyco.face_normal, in mahyco.face_length_lagrange, in mahyco.outer_face_normal,
        in mahyco.face_normal_velocity,in remap.phi_face,
        out remap.dual_phi_flux, out mahyco.est_mixte, out mahyco.est_pure,
        inout mahyco.u_lagrange, inout mahyco.phi_lagrange
        call computeUremapPBorn0;
    
    def void computeUremapPBorn0(in Int idir, in Int nb_vars_to_project, in Int nb_env)
        in mahyco.face_normal, in mahyco.face_normal_velocity, in mahyco.face_length_lagrange,
        in mahyco.outer_face_normal, in remap.phi_face,
        out remap.dual_phi_flux, out mahyco.est_mixte, out mahyco.est_pure,
        inout mahyco.u_lagrange, inout mahyco.phi_lagrange;
    
    def void computeDualUremap(in Int idir, in Int nb_env)
        in remap.dual_phi_flux, in mahyco.node_coord,
        inout mahyco.dual_grad_phi,
        inout remap.back_flux_contrib_env, inout remap.front_flux_contrib_env,
        inout remap.back_flux_mass, inout remap.front_flux_mass,
        inout remap.back_flux_mass_env, inout remap.front_flux_mass_env,
        inout mahyco.u_dual_lagrange, inout mahyco.phi_dual_lagrange
        /*call computeDualGradPhi_LimC*/;

    def Real computeRemapFlux(in Int projectionOrder, in Int projectionAvecPlateauPente,
                              in Real face_normal_velocity, in Real[3] face_normal,
                              in Real face_length, in Real phi_face,
                              in Real[3] outer_face_normal, in Real[3] exy, in Real deltat_n);
}