package remap;

var Bool[*] is_dir_face { Face } @axlname("IsDirFace") @dump @sync;
var Int sens_projection { } @axlname("SensProjection") @dump;

var Real deltax_lagrange { Face } @axlname("DeltaxLagrange") @dump @sync;  

var Real[*] phi_face { Face } @axlname("PhiFace") @dump @sync; 
var Real[*] grad_phi_face { Face } @axlname("GradPhiFace") @dump @sync; 
var Real[*] grad_phi { Cell } @axlname("GradPhi") @dump @sync;
var Real[*] delta_phi_face_ar { Cell } @axlname("DeltaPhiFaceAr") @dump @sync; 
var Real[*] delta_phi_face_av { Cell } @axlname("DeltaPhiFaceAv") @dump @sync; 
var Real[*] dual_phi_flux { Cell } @axlname("DualPhiFlux") @dump @sync;
var Real h_cell_lagrange { Cell } @axlname("HCellLagrange") @dump @sync;
var Real[*] back_flux_mass_env { Node } @axlname("BackFluxMassEnv") @dump @sync; 
var Real[*] front_flux_mass_env { Node } @axlname("FrontFluxMassEnv") @dump @sync; 
var Real back_flux_mass { Node } @axlname("BackFluxMass") @dump @sync; 
var Real front_flux_mass { Node } @axlname("FrontFluxMass") @dump @sync; 
var Real[*] back_flux_contrib_env { Cell } @axlname("BackFluxContribEnv") @dump @sync; 
var Real[*] front_flux_contrib_env { Cell } @axlname("FrontFluxContribEnv") @dump @sync; 

var Int cell_status { Cell } @axlname("CellStatus");

interface Remap {
    /*! Définition de la valeur limite des petites fractions et autres */
    Int OrdreProjection="2";
    /*! Définition de la valeur limite des petites fractions et autres */
    Real Threshold="1.e-10";
    Real ArithmeticThreshold = "1.e-300";
    /*! projection type Euler (retour sur maillage initial) */
    Bool IsEulerScheme="true";
    /*! Conservation de l energie totale lors de la projection */
    Bool ConservationEnergieTotale="false";
    /*! projection pente borne en volume dans les mailles mixtes et en masse dans les mailles pures */
    Bool ProjectionPenteBorneMixte="false";
    /*! identifiant du limiteur pour les mailles mixtes */
    types_mahyco.Limiteur ProjectionLimiteurId="minmod";
    /*! identifiant du limiteur pour les mailles pures */
    types_mahyco.Limiteur ProjectionLimiteurPureId="minmod";
    /*! projection avec l'algorithme pente-borne */
    Bool ProjectionPenteBorne="false";
    /*! projection avec l'algorithme pente-borne en evitant l'artefact de debar avec la valeur moyenne (1) ou valeur aux mailles (2) */
    Int ProjectionPenteBorneDebarFix="0";
    
    /*!
     * main du remap
     */
    def void appliRemap(in Int dimension, in Int withDualProjection, in Int nb_vars_to_project, in Int nb_env);
    /*!
     * resize les variables du remap
     */
    def void resizeRemapVariables(in Int nb_vars_to_project, in Int nb_env);
    /*!
     * synchronisation des valeurs aux cellules 
     */
    def void synchronizeUremap();
    /*!
     * fonction final de la projection
     */
    def void remapVariables(in Int dimension, in Int withDualProjection, in Int nb_vars_to_project, in Int nb_env);

}
