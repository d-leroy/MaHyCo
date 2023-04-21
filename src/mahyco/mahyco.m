package mahyco ;

/*! Pas de temps Old */
var real old_deltat { } @axlname("OldDeltat") @dump;
/*! sens de la projection */
var int sens_projection { } @axlname("SensProjection") @dump;
/*! Materiau */
var real materiau { cell } @axlname("Materiau") @dump @sync;
/*! DENSITY OLD N */
var real density_n { matCell } @axlname("DentityN") @dump @sync;
/*! DENSITY */
var real density { matCell } @axlname("Density") @dump @sync;
/*! PRESSURE OLD N */
var real pressure_n { matCell } @axlname("PressureN") @dump @sync;
/*! PRESSURE */
var real pressure { matCell } @axlname("Pressure") @dump @sync;
/*! PSEUDO OLD N-1 */
var real pseudo_viscosity_nmoins1 { matCell } @axlname("PseudoViscosityNmoins1") @dump @sync;
/*! PSEUDO OLD N */
var real pseudo_viscosity_n { matCell } @axlname("PseudoViscosityN") @dump @sync;
/*! PSEUDO */
var real pseudo_viscosity { matCell } @axlname("PseudoViscosity") @dump @sync;
/*! MASS FRACTION */
var real mass_fraction { matCell } @axlname("MassFraction") @dump @sync;
/*! CELL MASS */
var real cell_mass { matCell } @axlname("CellMass") @dump @sync;
/*! INTERNAL ENERGY OLD N */
var real internal_energy_n { matCell } @axlname("InternalEnergyN") @dump @sync;
/*! INTERNAL ENERGY */
var real internal_energy { matCell } @axlname("InternalEnergy") @dump @sync;
/*! DPDE */
var real dpde { matCell } @axlname("DpDe") @dump @sync;
/*! FRACVOL */
var real fracvol { matCell } @axlname("FracVol") @dump @sync;
/*! CELL VOLUME OLD N */
var real cell_volume_n { matCell } @axlname("CellVolumeN") @dump @sync;
/*! CELL VOLUME */
var real cell_volume { matCell } @axlname("CellVolume") @dump @sync;
/*! CELL VOLUME EULER */
var real euler_volume { cell } @axlname("EulerVolume") @dump @sync;
/*! DIV U */
var real div_u { cell } @axlname("DivU") @sync;
/*! TAUX DENSITY */
var real tau_density { matCell } @axlname("TauDensity") @sync;
/*! FORCE */
var real[3] force { node } @axlname("Force");
/*! VELOCITY OLD N */
var real[3] velocity_n { node } @axlname("VelocityN") @dump @sync;
/*! VELOCITY */
var real[3] velocity { node } @axlname("Velocity") @dump @sync;
/*! NODE MASS */
var real node_mass { node } @axlname("NodeMass") @dump @sync;
/*! CARACTERISTIC LENGTH */
var real caracteristic_length { cell } @axlname("CaracteristicLength") @sync;
/*! SOUND SPEED */
var real sound_speed { matCell } @axlname("SoundSpeed") @dump @sync;
/*! NODE COORD */
var real[3] node_coord { node } @axlname("NodeCoord") @dump @sync;
/*! NODE COORD_0 */
var real[3] node_coord_0 { node } @axlname("NodeCoord0") @dump @sync;
/*! CELL COORD */
var real[3] cell_coord { cell } @axlname("CellCoord") @dump @sync;
/*! CELL CQS */
var real[*,3] cell_cqs_n { cell } @axlname("CellCQSN") @dump @sync;
/*! CELL OLD CQS */
var real[*,3] cell_cqs { cell } @axlname("CellCQS") @dump @sync;
/*! FACE COORD */
var real[3] face_coord { face } @axlname("FaceCoord") @dump @sync;
/*! FACE NORMAL */
var real[3] face_normal { face } @axlname("FaceNormal") @dump @sync;
/*! FACE NORMAL VELOCITY */
var real face_normal_velocity { face } @axlname("FaceNormalVelocity") @dump @sync;
/*! FACE LENGHT */
var real[3] face_length_lagrange { face } @axlname("FaceLengthLagrange") @dump @sync;
/*! U LAGRANGE */
var real[*] u_lagrange { cell } @axlname("ULagrange") @dump @sync;
/*! U DUAL LAGRANGE */
var real[*] u_dual_lagrange { node } @axlname("UDualLagrange") @dump @sync;
/*! PHI LAGRANGE */
var real[*] phi_lagrange { cell } @axlname("PhiLagrange") @dump @sync;
/*! PHI DUAL LAGRANGE */
var real[*] phi_dual_lagrange { node } @axlname("PhiDualLagrange") @dump @sync;
/*! GRAD PHI DUAL LAGRANGE pour les vitesses */
var real[*] dual_grad_phi { node } @axlname("DualGradPhi") @dump @sync;
/*! MIXTE */
var int est_mixte { cell } @axlname("EstMixte") @dump @sync;
/*! PURE */
var int est_pure { cell } @axlname("EstPure") @dump @sync;
/*! isDirFace */
var bool[*] is_dir_face { face } @axlname("IsDirFace") @dump @sync;
/*! U REMAP2 */
var real[*,3] outer_face_normal { cell } @axlname("OuterFaceNormal") @dump @sync;

/*! Descripteur du module Mahyco */
module Mahyco {
    /*! Materiaux */
    [1..*] types_mahyco.Material material;
    /*! Milieu */
    [1..*] types_mahyco.Environment environment;
    /*! Service d'initialisation du cas test */
    [1..1] cas_test.Initialisations CasModel;
    /*! Service de projection */
    [1..1] remap.Remap remap;
    /*! Impose le tri cartésien des faces (valable que si le maillage est lui-même cartésien) */
    [1..1] bool CartesianSortFaces = "true";
    /*! Schema CSTS */
    [1..1] bool SchemaCsts;
    /*! Option pseudo-centrée */
    [1..1] bool PseudoCentree;
    /*! Type de longueur caracteristique */
    [1..1] string LongueurCaracteristique;
    /*!
     * Valeur minimale que peut prendre le <em>deltat</em>
     * entre deux itérations.
     */
    [1..1] real DeltatMin;

    /*!
     * Valeur maximale que peut prendre le <em>deltat</em>
     * entre deux itérations. Si le deltat calculé est supérieur
     * à cette valeur, il est ramené à cette valeur.
     */
    [1..1] real DeltatMax;
    /*! Valeur du <em>deltat</em> au moment du démarrage. */
    [1..1] real DeltatInit;
    /*!
     * Temps auquel on stoppe la simulation. Le code s'arrête dès que
     * le temps courant est <strong>strictement</strong> supérieur à ce temps.
     */
    [1..1] real FinalTime namefr "temps-final";
    /*! Définition de la CFL */
    [1..1] real Cfl = "0.3";
    /*! Définition de la valeur limite des petites fractions et autres */
    [1..1] real Threshold = "1.e-10";
    /*! Calcule sans le schema Lagrange */
    [1..1] bool SansLagrange = "false";
    /*! Calcul de l'energie avec newton */
    [1..1] bool WithNewton = "false";
    /*! Calcul avec projection ADI */
    [1..1] bool WithProjection = "true";
    /*! Condition aux limites */
    [0..*] types_mahyco.BoundaryCondition BoundaryCondition;

    // TypesMahyco.BoundaryCondition[*] @opt;

    [1..1] types_mahyco.IGeometryMng geometry;
    def void initGeometricValues()
        in cell_coord, node_coord
        out node_coord_0, outer_face_normal
        inout face_coord, face_normal;

    def void computeGeometricValuesAux()
        in fracvol, velocity
        out cell_cqs
        inout node_coord, cell_volume;

    def void updateVelocityWithoutLagrange()
        in velocity_n
        out velocity;

    def void updateForceAndVelocity()
        in pressure, pseudo_viscosity, cell_cqs, node_mass
        out force
        inout velocity;

    def void updateEnergyAndPressurebyNewton()
        in pseudo_viscosity, pseudo_viscosity_n, pseudo_viscosity_nmoins1, density, density_n, internal_energy_n, pressure_n, dpde, mass_fraction, velocity, velocity_n, cell_cqs, cell_cqs_n, cell_mass
        out internal_energy
        inout pressure, sound_speed;

    def void updateEnergyAndPressureforGP()
        in pseudo_viscosity, pseudo_viscosity_n, pseudo_viscosity_nmoins1, density, density_n, internal_energy_n, pressure_n, mass_fraction, velocity, velocity_n, cell_cqs, cell_cqs_n, cell_mass
        out internal_energy
        inout pressure;

    def void computeAveragePressure()
        in fracvol
        inout pressure, sound_speed;

    def real computeHydroDeltaT()
        in caracteristic_length, sound_speed, velocity;

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
        out cell_cqs, cell_cqs_n;
    @StartInit initDtIni
    /* out ArcaneBuiltins.GlobalDeltaT */;
    @StartInit initHydroVar
        in cell_cqs, mass_fraction, node_coord
        out euler_volume
        inout cell_volume, internal_energy, sound_speed
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
        in density, cell_volume, mass_fraction
        inout cell_mass;
    @StartInit computeNodeMass
        in cell_mass
        out node_mass;

    // <entry-point method-name="continueForMultiMat" name="ContinueForMultiMat" where="continue-init" property="none" />
    // @ContinueInit
    // ContinueForMultiMat;
    @ContinueInit continueForIterationDt
        in old_deltat
    /* out ArcaneBuiltins.GlobalOldDeltaT
    inout ArcaneBuiltins.GlobalIteration */;
    @ComputeLoop saveValuesAtN
        in old_deltat, pseudo_viscosity, pressure, cell_volume, density, internal_energy, cell_cqs, velocity, node_coord_0
        out /* ArcaneBuiltins.GlobalOldDeltaT, */
    pseudo_viscosity_nmoins1, pressure_n, cell_volume_n, density_n, internal_energy_n, cell_cqs_n, velocity_n, node_coord
        inout pseudo_viscosity_n;
    @ComputeLoop updateVelocity
        call updateForceAndVelocity, updateVelocityWithoutLagrange;

    // <entry-point method-name="applyBoundaryCondition" name="ApplyBoundaryCondition" where="compute-loop" property="none" />
    // @ComputeLoop
    // ApplyBoundaryCondition;
    @ComputeLoop updatePosition
        in velocity
        out cell_coord
        inout node_coord;
    @ComputeLoop computeGeometricValues
        call computeGeometricValuesAux;
    @ComputeLoop updateDensity
        in cell_mass, cell_volume, density_n/* , ArcaneBuiltins.GlobalDeltaT */
        out div_u
        inout density, tau_density;
    @ComputeLoop computeArtificialViscosity
        in div_u, caracteristic_length, sound_speed, tau_density, fracvol//, AdiabaticCstEnv (not in AXL)
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

