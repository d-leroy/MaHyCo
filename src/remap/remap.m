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
