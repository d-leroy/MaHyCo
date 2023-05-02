package mahyco ;

/*! Pas de temps Old */
var Real old_deltat { } @axlname("OldDeltat") @dump;
/*! sens de la projection */
var Int sens_projection { } @axlname("SensProjection") @dump;
/*! Materiau */
var Real materiau { Cell } @axlname("Materiau") @dump @sync;
/*! DENSITY OLD N */
var Real density_n { MatCell } @axlname("DentityN") @dump @sync;
/*! DENSITY */
var Real density { MatCell } @axlname("Density") @dump @sync;
/*! PRESSURE OLD N */
var Real pressure_n { MatCell } @axlname("PressureN") @dump @sync;
/*! PRESSURE */
var Real pressure { MatCell } @axlname("Pressure") @dump @sync;
/*! PSEUDO OLD N-1 */
var Real pseudo_viscosity_nmoins1 { MatCell } @axlname("PseudoViscosityNmoins1") @dump @sync;
/*! PSEUDO OLD N */
var Real pseudo_viscosity_n { MatCell } @axlname("PseudoViscosityN") @dump @sync;
/*! PSEUDO */
var Real pseudo_viscosity { MatCell } @axlname("PseudoViscosity") @dump @sync;
/*! MASS FRACTION */
var Real mass_fraction { MatCell } @axlname("MassFraction") @dump @sync;
/*! CELL MASS */
var Real cell_mass { MatCell } @axlname("CellMass") @dump @sync;
/*! INTERNAL ENERGY OLD N */
var Real internal_energy_n { MatCell } @axlname("InternalEnergyN") @dump @sync;
/*! INTERNAL ENERGY */
var Real internal_energy { MatCell } @axlname("InternalEnergy") @dump @sync;
/*! DPDE */
var Real dpde { MatCell } @axlname("DpDe") @dump @sync;
/*! FRACVOL */
var Real fracvol { MatCell } @axlname("FracVol") @dump @sync;
/*! CELL VOLUME OLD N */
var Real cell_volume_n { MatCell } @axlname("CellVolumeN") @dump @sync;
/*! CELL VOLUME */
var Real cell_volume { MatCell } @axlname("CellVolume") @dump @sync;
/*! CELL VOLUME EULER */
var Real euler_volume { Cell } @axlname("EulerVolume") @dump @sync;
/*! DIV U */
var Real div_u { Cell } @axlname("DivU") @sync;
/*! TAUX DENSITY */
var Real tau_density { MatCell } @axlname("TauDensity") @sync;
/*! FORCE */
var Real[3] force { Node } @axlname("Force");
/*! VELOCITY OLD N */
var Real[3] velocity_n { Node } @axlname("VelocityN") @dump @sync;
/*! VELOCITY */
var Real[3] velocity { Node } @axlname("Velocity") @dump @sync;
/*! NODE MASS */
var Real node_mass { Node } @axlname("NodeMass") @dump @sync;
/*! CARACTERISTIC LENGTH */
var Real caracteristic_length { Cell } @axlname("CaracteristicLength") @sync;
/*! SOUND SPEED */
var Real sound_speed { MatCell } @axlname("SoundSpeed") @dump @sync;
/*! NODE COORD */
var Real[3] node_coord { Node } @axlname("NodeCoord") @dump @sync;
/*! NODE COORD_0 */
var Real[3] node_coord_0 { Node } @axlname("NodeCoord0") @dump @sync;
/*! CELL COORD */
var Real[3] cell_coord { Cell } @axlname("CellCoord") @dump @sync;
/*! CELL CQS */
var Real[*,3] cell_cqs_n { Cell } @axlname("CellCQSN") @dump @sync;
/*! CELL OLD CQS */
var Real[*,3] cell_cqs { Cell } @axlname("CellCQS") @dump @sync;
/*! FACE COORD */
var Real[3] face_coord { Face } @axlname("FaceCoord") @dump @sync;
/*! FACE NORMAL */
var Real[3] face_normal { Face } @axlname("FaceNormal") @dump @sync;
/*! FACE NORMAL VELOCITY */
var Real face_normal_velocity { Face } @axlname("FaceNormalVelocity") @dump @sync;
/*! FACE LENGHT */
var Real[3] face_length_lagrange { Face } @axlname("FaceLengthLagrange") @dump @sync;
/*! U LAGRANGE */
var Real[*] u_lagrange { Cell } @axlname("ULagrange") @dump @sync;
/*! U DUAL LAGRANGE */
var Real[*] u_dual_lagrange { Node } @axlname("UDualLagrange") @dump @sync;
/*! PHI LAGRANGE */
var Real[*] phi_lagrange { Cell } @axlname("PhiLagrange") @dump @sync;
/*! PHI DUAL LAGRANGE */
var Real[*] phi_dual_lagrange { Node } @axlname("PhiDualLagrange") @dump @sync;
/*! GRAD PHI DUAL LAGRANGE pour les vitesses */
var Real[*] dual_grad_phi { Node } @axlname("DualGradPhi") @dump @sync;
/*! MIXTE */
var Int est_mixte { Cell } @axlname("EstMixte") @dump @sync;
/*! PURE */
var Int est_pure { Cell } @axlname("EstPure") @dump @sync;
/*! isDirFace */
var Bool[*] is_dir_face { Face } @axlname("IsDirFace") @dump @sync;
/*! U REMAP2 */
var Real[*,3] outer_face_normal { Cell } @axlname("OuterFaceNormal") @dump @sync;

/*! Descripteur du module Mahyco */
module Mahyco {
    /*! Materiaux */
    types_mahyco.Material[*] material;
    /*! Milieu */
    types_mahyco.Environment[*] environment;
    /*! Service d'initialisation du cas test */
    cas_test.Initialisations CasModel;
    /*! Service de projection */
    remap.Remap remap;
    /*! Impose le tri cartésien des faces (valable que si le maillage est lui-même cartésien) */
    Bool CartesianSortFaces = "true";
    /*! Schema CSTS */
    Bool SchemaCsts;
    /*! Option pseudo-centrée */
    Bool PseudoCentree;
    /*! Type de longueur caracteristique */
    String LongueurCaracteristique;
    /*!
     * Valeur minimale que peut prendre le <em>deltat</em>
     * entre deux itérations.
     */
    Real DeltatMin;

    /*!
     * Valeur maximale que peut prendre le <em>deltat</em>
     * entre deux itérations. Si le deltat calculé est supérieur
     * à cette valeur, il est ramené à cette valeur.
     */
    Real DeltatMax;
    /*! Valeur du <em>deltat</em> au moment du démarrage. */
    Real DeltatInit;
    /*!
     * Temps auquel on stoppe la simulation. Le code s'arrête dès que
     * le temps courant est <strong>strictement</strong> supérieur à ce temps.
     */
    Real FinalTime namefr "temps-final";
    /*! Définition de la CFL */
    Real Cfl = "0.3";
    /*! Définition de la valeur limite des petites fractions et autres */
    Real Threshold = "1.e-10";
    /*! Calcule sans le schema Lagrange */
    Bool SansLagrange = "false";
    /*! Calcul de l'energie avec newton */
    Bool WithNewton = "false";
    /*! Calcul avec projection ADI */
    Bool WithProjection = "true";
    /*! Condition aux limites */
    opt types_mahyco.BoundaryCondition[*] BoundaryCondition;

    // TypesMahyco.BoundaryCondition[*] @opt;

    types_mahyco.IGeometryMng geometry;
    def void initGeometricValues()
        in cell_coord, in node_coord,
        out node_coord_0, out outer_face_normal,
        inout face_coord, inout face_normal;

    def void computeGeometricValuesAux()
        in fracvol, in velocity,
        out cell_cqs,
        inout node_coord, inout cell_volume;

    def void updateVelocityWithoutLagrange()
        in velocity_n,
        out velocity;

    def void updateForceAndVelocity()
        in pressure, in pseudo_viscosity, in cell_cqs, in node_mass,
        out force,
        inout velocity;

    def void updateEnergyAndPressurebyNewton()
        in pseudo_viscosity, in pseudo_viscosity_n, in pseudo_viscosity_nmoins1, in density, in density_n,
        in internal_energy_n, in pressure_n, in dpde, in mass_fraction, in velocity, in velocity_n,
        in cell_cqs, in cell_cqs_n, in cell_mass,
        out internal_energy,
        inout pressure, inout sound_speed;

    def void updateEnergyAndPressureforGP()
        in pseudo_viscosity, in pseudo_viscosity_n, in pseudo_viscosity_nmoins1, in density, in density_n,
        in internal_energy_n, in pressure_n, in mass_fraction, in velocity, in velocity_n, in cell_cqs,
        in cell_cqs_n, in cell_mass,
        out internal_energy,
        inout pressure;

    def void computeAveragePressure()
        in fracvol,
        inout pressure, inout sound_speed;

    def Real computeHydroDeltaT()
        in caracteristic_length, in sound_speed, in velocity;

    // <entry-point method-name="accBuild" name="AccBuild" where="build" property="none" />
    // @Build
    // AccBuild;

    // <entry-point method-name="checkOptions" name="CheckOptions" where="start-init" property="none" />
    // @StartInit
    // CheckOptions;

    // TODO: manipulates 'legacy' variables not declared in the AXL
    // <entry-point method-name="initCartesianMesh" name="InitCartesianMesh" where="init" property="none" />
    // @Init
    // InitCartesianMesh;
    @StartInit allocCqs
        out cell_cqs, out cell_cqs_n;
    @StartInit initDtIni
    /* out ArcaneBuiltins.GlobalDeltaT */;
    @StartInit initHydroVar
        in cell_cqs, in mass_fraction, in node_coord,
        out euler_volume,
        inout cell_volume, inout internal_energy, inout sound_speed
        call initGeometricValues;





        
    // <entry-point method-name="hydroStartInitEnvAndMat" name="HydroStartInitEnvAndMat" where="start-init" property="none" />
    // @StartInit
    // HydroStartInitEnvAndMat;

    // <entry-point method-name="initEnvForAcc" name="InitEnvForAcc" where="init" property="none" />
    // @Init
    // InitEnvForAcc;
    @StartInit computeGeometricValuesIni
        call computeGeometricValuesAux;
    @StartInit prepareFaceGroupForBc
        in node_coord;

    // <entry-point method-name="initBoundaryConditionsForAcc" name="InitBoundaryConditionsForAcc" where="init" property="none" />
    // @Init
    // InitBoundaryConditionsForAcc;

    // <entry-point method-name="setSyncVarVers" name="SetSyncVarVers" where="start-init" property="none" />
    // @StartInit
    // SetSyncVarVers;
    @StartInit computeCellMass
        in density, in cell_volume, in mass_fraction,
        inout cell_mass;
    @StartInit computeNodeMass
        in cell_mass,
        out node_mass;

    // <entry-point method-name="continueForMultiMat" name="ContinueForMultiMat" where="continue-init" property="none" />
    // @ContinueInit
    // ContinueForMultiMat;
    @ContinueInit continueForIterationDt
        in old_deltat
    /* out ArcaneBuiltins.GlobalOldDeltaT
    inout ArcaneBuiltins.GlobalIteration */;
    @ComputeLoop saveValuesAtN
        in old_deltat, in pseudo_viscosity, in pressure, in cell_volume, in density,
        in internal_energy, in cell_cqs, in velocity, in node_coord_0,
        /* out ArcaneBuiltins.GlobalOldDeltaT, */
        out pseudo_viscosity_nmoins1, out pressure_n, out cell_volume_n, out density_n,
        out internal_energy_n, out cell_cqs_n, out velocity_n, out node_coord,
        inout pseudo_viscosity_n;
    @ComputeLoop updateVelocity
        call updateForceAndVelocity, updateVelocityWithoutLagrange;

    // <entry-point method-name="applyBoundaryCondition" name="ApplyBoundaryCondition" where="compute-loop" property="none" />
    // @ComputeLoop
    // ApplyBoundaryCondition;
    @ComputeLoop updatePosition
        in velocity,
        out cell_coord,
        inout node_coord;
    @ComputeLoop computeGeometricValues
        call computeGeometricValuesAux;
    @ComputeLoop updateDensity
        in cell_mass, in cell_volume, in density_n/* , ArcaneBuiltins.GlobalDeltaT */,
        out div_u,
        inout density, inout tau_density;
    @ComputeLoop computeArtificialViscosity
        in div_u, in caracteristic_length, in sound_speed, in tau_density, in fracvol,// AdiabaticCstEnv, (not in AXL)
        inout pseudo_viscosity;
    @ComputeLoop updateEnergyAndPressure
        call updateEnergyAndPressurebyNewton, updateEnergyAndPressureforGP, computeAveragePressure;

    // <entry-point method-name="computePressionMoyenne" name="ComputePressionMoyenne" where="compute-loop" property="none" />
    // @ComputeLoop
    // ComputePressionMoyenne;

    // <entry-point method-name="remap" name="Remap" where="compute-loop" property="none" />
    // @ComputeLoop
    // Remap;
    @ComputeLoop computeDeltaT
        out old_deltat
    /* inout ArcaneBuiltins.GlobalOldDeltaT, ArcaneBuiltins.GlobalDeltaT */
        call computeHydroDeltaT;
}

