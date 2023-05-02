#ifndef REMAP___REMAPADISERVICEVARS_H
#define REMAP___REMAPADISERVICEVARS_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "arcane/materials/ComponentItemVector.h"
#include "arcane/materials/ComponentItemVectorView.h"
#include "arcane/materials/MeshEnvironmentVariableRef.h"
#include "arcane/materials/MeshMaterialVariableRef.h"
#include "arcane/materials/IMeshMaterialMng.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Remap {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de variable pour synchronizeDualUremap
struct RemapADISynchronizeDualUremapVars final
{
  RemapADISynchronizeDualUremapVars(VariableNodeArrayReal& phi_dual_lagrange,
      VariableNodeArrayReal& u_dual_lagrange)
  : m_phi_dual_lagrange(phi_dual_lagrange)
  , m_u_dual_lagrange(u_dual_lagrange)
  {}

  /*!
  [out] phi_dual_lagrange
  */
  VariableNodeArrayReal& m_phi_dual_lagrange;
  /*!
  [out] u_dual_lagrange
  */
  VariableNodeArrayReal& m_u_dual_lagrange;
};

//! Classe de variable pour computeGradPhiFace
struct RemapADIComputeGradPhiFaceVars final
{
  RemapADIComputeGradPhiFaceVars(const VariableFaceReal3& face_normal,
      const VariableCellReal3& cell_coord,
      const VariableCellArrayReal& phi_lagrange,
      const VariableFaceReal3& face_coord,
      const VariableCellReal3& cell_coord,
      VariableFaceArrayByte& is_dir_face,
      VariableFaceArrayReal& grad_phi_face,
      VariableFaceReal& deltax_lagrange,
      VariableCellReal& h_cell_lagrange)
  : m_face_normal(face_normal)
  , m_cell_coord(cell_coord)
  , m_phi_lagrange(phi_lagrange)
  , m_face_coord(face_coord)
  , m_cell_coord(cell_coord)
  , m_is_dir_face(is_dir_face)
  , m_grad_phi_face(grad_phi_face)
  , m_deltax_lagrange(deltax_lagrange)
  , m_h_cell_lagrange(h_cell_lagrange)
  {}

  /*!
  [in] face_normal
  */
  const VariableFaceReal3& m_face_normal;
  /*!
  [in] cell_coord
  */
  const VariableCellReal3& m_cell_coord;
  /*!
  [in] phi_lagrange
  */
  const VariableCellArrayReal& m_phi_lagrange;
  /*!
  [in] face_coord
  */
  const VariableFaceReal3& m_face_coord;
  /*!
  [in] cell_coord
  */
  const VariableCellReal3& m_cell_coord;
  /*!
  [out] is_dir_face
  */
  VariableFaceArrayByte& m_is_dir_face;
  /*!
  [out] grad_phi_face
  */
  VariableFaceArrayReal& m_grad_phi_face;
  /*!
  [inout] deltax_lagrange
  */
  VariableFaceReal& m_deltax_lagrange;
  /*!
  [inout] h_cell_lagrange
  */
  VariableCellReal& m_h_cell_lagrange;
};

//! Classe de variable pour computeGradPhiCell
struct RemapADIComputeGradPhiCellVars final
{
  RemapADIComputeGradPhiCellVars(const VariableCellArrayReal3& outer_face_normal,
      const VariableFaceReal& face_normal_velocity,
      const VariableFaceReal3& face_length_lagrange,
      const VariableFaceArrayByte& is_dir_face,
      VariableCellArrayReal& grad_phi,
      VariableCellArrayReal& dual_phi_flux,
      VariableCellArrayReal& delta_phi_face_av,
      VariableCellArrayReal& delta_phi_face_ar,
      VariableCellInteger& est_mixte,
      VariableCellInteger& est_pure)
  : m_outer_face_normal(outer_face_normal)
  , m_face_normal_velocity(face_normal_velocity)
  , m_face_length_lagrange(face_length_lagrange)
  , m_is_dir_face(is_dir_face)
  , m_grad_phi(grad_phi)
  , m_dual_phi_flux(dual_phi_flux)
  , m_delta_phi_face_av(delta_phi_face_av)
  , m_delta_phi_face_ar(delta_phi_face_ar)
  , m_est_mixte(est_mixte)
  , m_est_pure(est_pure)
  {}

  /*!
  [in] outer_face_normal
  */
  const VariableCellArrayReal3& m_outer_face_normal;
  /*!
  [in] face_normal_velocity
  */
  const VariableFaceReal& m_face_normal_velocity;
  /*!
  [in] face_length_lagrange
  */
  const VariableFaceReal3& m_face_length_lagrange;
  /*!
  [in] is_dir_face
  */
  const VariableFaceArrayByte& m_is_dir_face;
  /*!
  [out] grad_phi
  */
  VariableCellArrayReal& m_grad_phi;
  /*!
  [out] dual_phi_flux
  */
  VariableCellArrayReal& m_dual_phi_flux;
  /*!
  [out] delta_phi_face_av
  */
  VariableCellArrayReal& m_delta_phi_face_av;
  /*!
  [out] delta_phi_face_ar
  */
  VariableCellArrayReal& m_delta_phi_face_ar;
  /*!
  [inout] est_mixte
  */
  VariableCellInteger& m_est_mixte;
  /*!
  [inout] est_pure
  */
  VariableCellInteger& m_est_pure;
};

//! Classe de variable pour computeGradPhiCell_PBorn0_LimC
struct RemapADIComputeGradPhiCell_PBorn0_LimCVars final
{
  RemapADIComputeGradPhiCell_PBorn0_LimCVars(const VariableFaceArrayReal& grad_phi_face,
      VariableCellArrayReal& grad_phi,
      VariableCellArrayReal& delta_phi_face_ar,
      VariableCellArrayReal& delta_phi_face_av)
  : m_grad_phi_face(grad_phi_face)
  , m_grad_phi(grad_phi)
  , m_delta_phi_face_ar(delta_phi_face_ar)
  , m_delta_phi_face_av(delta_phi_face_av)
  {}

  /*!
  [in] grad_phi_face
  */
  const VariableFaceArrayReal& m_grad_phi_face;
  /*!
  [out] grad_phi
  */
  VariableCellArrayReal& m_grad_phi;
  /*!
  [out] delta_phi_face_ar
  */
  VariableCellArrayReal& m_delta_phi_face_ar;
  /*!
  [out] delta_phi_face_av
  */
  VariableCellArrayReal& m_delta_phi_face_av;
};

//! Classe de variable pour computeDualGradPhi_LimC
struct RemapADIComputeDualGradPhi_LimCVars final
{
  RemapADIComputeDualGradPhi_LimCVars(const VariableNodeArrayReal& phi_dual_lagrange,
      const VariableNodeReal3& node_coord,
      VariableNodeArrayReal& dual_grad_phi)
  : m_phi_dual_lagrange(phi_dual_lagrange)
  , m_node_coord(node_coord)
  , m_dual_grad_phi(dual_grad_phi)
  {}

  /*!
  [in] phi_dual_lagrange
  */
  const VariableNodeArrayReal& m_phi_dual_lagrange;
  /*!
  [in] node_coord
  */
  const VariableNodeReal3& m_node_coord;
  /*!
  [out] dual_grad_phi
  */
  VariableNodeArrayReal& m_dual_grad_phi;
};

//! Classe de variable pour computeUpwindFaceQuantitiesForProjection
struct RemapADIComputeUpwindFaceQuantitiesForProjectionVars final
{
  RemapADIComputeUpwindFaceQuantitiesForProjectionVars(const VariableFaceReal& face_normal_velocity,
      const VariableFaceReal& deltax_lagrange,
      const VariableCellArrayReal& phi_lagrange,
      const VariableFaceReal3& face_coord,
      const VariableCellReal3& cell_coord,
      const VariableFaceReal3& face_normal,
      const VariableCellArrayReal& grad_phi,
      const VariableCellArrayReal& delta_phi_face_av,
      const VariableCellArrayReal& delta_phi_face_ar,
      const VariableCellReal& h_cell_lagrange,
      const VariableCellInteger& est_mixte,
      const VariableCellInteger& est_pure,
      VariableFaceArrayReal& phi_face)
  : m_face_normal_velocity(face_normal_velocity)
  , m_deltax_lagrange(deltax_lagrange)
  , m_phi_lagrange(phi_lagrange)
  , m_face_coord(face_coord)
  , m_cell_coord(cell_coord)
  , m_face_normal(face_normal)
  , m_grad_phi(grad_phi)
  , m_delta_phi_face_av(delta_phi_face_av)
  , m_delta_phi_face_ar(delta_phi_face_ar)
  , m_h_cell_lagrange(h_cell_lagrange)
  , m_est_mixte(est_mixte)
  , m_est_pure(est_pure)
  , m_phi_face(phi_face)
  {}

  /*!
  [in] face_normal_velocity
  */
  const VariableFaceReal& m_face_normal_velocity;
  /*!
  [in] deltax_lagrange
  */
  const VariableFaceReal& m_deltax_lagrange;
  /*!
  [in] phi_lagrange
  */
  const VariableCellArrayReal& m_phi_lagrange;
  /*!
  [in] face_coord
  */
  const VariableFaceReal3& m_face_coord;
  /*!
  [in] cell_coord
  */
  const VariableCellReal3& m_cell_coord;
  /*!
  [in] face_normal
  */
  const VariableFaceReal3& m_face_normal;
  /*!
  [in] grad_phi
  */
  const VariableCellArrayReal& m_grad_phi;
  /*!
  [in] delta_phi_face_av
  */
  const VariableCellArrayReal& m_delta_phi_face_av;
  /*!
  [in] delta_phi_face_ar
  */
  const VariableCellArrayReal& m_delta_phi_face_ar;
  /*!
  [in] h_cell_lagrange
  */
  const VariableCellReal& m_h_cell_lagrange;
  /*!
  [in] est_mixte
  */
  const VariableCellInteger& m_est_mixte;
  /*!
  [in] est_pure
  */
  const VariableCellInteger& m_est_pure;
  /*!
  [inout] phi_face
  */
  VariableFaceArrayReal& m_phi_face;
};

//! Classe de variable pour computeUpwindFaceQuantitiesForProjection_PBorn0_O2
struct RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2Vars final
{
  RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2Vars(const VariableFaceReal& deltax_lagrange,
      const VariableFaceReal& face_normal_velocity,
      const VariableCellArrayReal& phi_lagrange,
      const VariableFaceReal3& face_coord,
      const VariableFaceReal3& face_normal,
      const VariableCellReal3& cell_coord,
      const VariableCellArrayReal& grad_phi,
      VariableFaceArrayReal& phi_face)
  : m_deltax_lagrange(deltax_lagrange)
  , m_face_normal_velocity(face_normal_velocity)
  , m_phi_lagrange(phi_lagrange)
  , m_face_coord(face_coord)
  , m_face_normal(face_normal)
  , m_cell_coord(cell_coord)
  , m_grad_phi(grad_phi)
  , m_phi_face(phi_face)
  {}

  /*!
  [in] deltax_lagrange
  */
  const VariableFaceReal& m_deltax_lagrange;
  /*!
  [in] face_normal_velocity
  */
  const VariableFaceReal& m_face_normal_velocity;
  /*!
  [in] phi_lagrange
  */
  const VariableCellArrayReal& m_phi_lagrange;
  /*!
  [in] face_coord
  */
  const VariableFaceReal3& m_face_coord;
  /*!
  [in] face_normal
  */
  const VariableFaceReal3& m_face_normal;
  /*!
  [in] cell_coord
  */
  const VariableCellReal3& m_cell_coord;
  /*!
  [in] grad_phi
  */
  const VariableCellArrayReal& m_grad_phi;
  /*!
  [out] phi_face
  */
  VariableFaceArrayReal& m_phi_face;
};

//! Classe de variable pour computeUremap
struct RemapADIComputeUremapVars final
{
  RemapADIComputeUremapVars(const VariableFaceReal3& face_normal,
      const VariableFaceReal3& face_length_lagrange,
      const VariableCellArrayReal3& outer_face_normal,
      const VariableFaceArrayReal& phi_face,
      VariableCellArrayReal& dual_phi_flux,
      VariableCellInteger& est_mixte,
      VariableCellInteger& est_pure,
      VariableCellArrayReal& u_lagrange,
      VariableCellArrayReal& phi_lagrange)
  : m_face_normal(face_normal)
  , m_face_length_lagrange(face_length_lagrange)
  , m_outer_face_normal(outer_face_normal)
  , m_phi_face(phi_face)
  , m_dual_phi_flux(dual_phi_flux)
  , m_est_mixte(est_mixte)
  , m_est_pure(est_pure)
  , m_u_lagrange(u_lagrange)
  , m_phi_lagrange(phi_lagrange)
  {}

  /*!
  [in] face_normal
  */
  const VariableFaceReal3& m_face_normal;
  /*!
  [in] face_length_lagrange
  */
  const VariableFaceReal3& m_face_length_lagrange;
  /*!
  [in] outer_face_normal
  */
  const VariableCellArrayReal3& m_outer_face_normal;
  /*!
  [in] phi_face
  */
  const VariableFaceArrayReal& m_phi_face;
  /*!
  [out] dual_phi_flux
  */
  VariableCellArrayReal& m_dual_phi_flux;
  /*!
  [out] est_mixte
  */
  VariableCellInteger& m_est_mixte;
  /*!
  [out] est_pure
  */
  VariableCellInteger& m_est_pure;
  /*!
  [inout] u_lagrange
  */
  VariableCellArrayReal& m_u_lagrange;
  /*!
  [inout] phi_lagrange
  */
  VariableCellArrayReal& m_phi_lagrange;
};

//! Classe de variable pour computeUremap_PBorn0
struct RemapADIComputeUremap_PBorn0Vars final
{
  RemapADIComputeUremap_PBorn0Vars(const VariableFaceReal3& face_normal,
      const VariableFaceReal& face_normal_velocity,
      const VariableFaceReal3& face_length_lagrange,
      const VariableCellArrayReal3& outer_face_normal,
      const VariableFaceArrayReal& phi_face,
      VariableCellArrayReal& dual_phi_flux,
      VariableCellInteger& est_mixte,
      VariableCellInteger& est_pure,
      VariableCellArrayReal& u_lagrange,
      VariableCellArrayReal& phi_lagrange)
  : m_face_normal(face_normal)
  , m_face_normal_velocity(face_normal_velocity)
  , m_face_length_lagrange(face_length_lagrange)
  , m_outer_face_normal(outer_face_normal)
  , m_phi_face(phi_face)
  , m_dual_phi_flux(dual_phi_flux)
  , m_est_mixte(est_mixte)
  , m_est_pure(est_pure)
  , m_u_lagrange(u_lagrange)
  , m_phi_lagrange(phi_lagrange)
  {}

  /*!
  [in] face_normal
  */
  const VariableFaceReal3& m_face_normal;
  /*!
  [in] face_normal_velocity
  */
  const VariableFaceReal& m_face_normal_velocity;
  /*!
  [in] face_length_lagrange
  */
  const VariableFaceReal3& m_face_length_lagrange;
  /*!
  [in] outer_face_normal
  */
  const VariableCellArrayReal3& m_outer_face_normal;
  /*!
  [in] phi_face
  */
  const VariableFaceArrayReal& m_phi_face;
  /*!
  [out] dual_phi_flux
  */
  VariableCellArrayReal& m_dual_phi_flux;
  /*!
  [out] est_mixte
  */
  VariableCellInteger& m_est_mixte;
  /*!
  [out] est_pure
  */
  VariableCellInteger& m_est_pure;
  /*!
  [inout] u_lagrange
  */
  VariableCellArrayReal& m_u_lagrange;
  /*!
  [inout] phi_lagrange
  */
  VariableCellArrayReal& m_phi_lagrange;
};

//! Classe de variable pour computeDualUremap
struct RemapADIComputeDualUremapVars final
{
  RemapADIComputeDualUremapVars(const VariableCellArrayReal& dual_phi_flux,
      const VariableNodeReal3& node_coord,
      VariableNodeArrayReal& dual_grad_phi,
      VariableCellArrayReal& back_flux_contrib_env,
      VariableCellArrayReal& front_flux_contrib_env,
      VariableNodeReal& back_flux_mass,
      VariableNodeReal& front_flux_mass,
      VariableNodeArrayReal& back_flux_mass_env,
      VariableNodeArrayReal& front_flux_mass_env,
      VariableNodeArrayReal& u_dual_lagrange,
      VariableNodeArrayReal& phi_dual_lagrange)
  : m_dual_phi_flux(dual_phi_flux)
  , m_node_coord(node_coord)
  , m_dual_grad_phi(dual_grad_phi)
  , m_back_flux_contrib_env(back_flux_contrib_env)
  , m_front_flux_contrib_env(front_flux_contrib_env)
  , m_back_flux_mass(back_flux_mass)
  , m_front_flux_mass(front_flux_mass)
  , m_back_flux_mass_env(back_flux_mass_env)
  , m_front_flux_mass_env(front_flux_mass_env)
  , m_u_dual_lagrange(u_dual_lagrange)
  , m_phi_dual_lagrange(phi_dual_lagrange)
  {}

  /*!
  [in] dual_phi_flux
  */
  const VariableCellArrayReal& m_dual_phi_flux;
  /*!
  [in] node_coord
  */
  const VariableNodeReal3& m_node_coord;
  /*!
  [inout] dual_grad_phi
  */
  VariableNodeArrayReal& m_dual_grad_phi;
  /*!
  [inout] back_flux_contrib_env
  */
  VariableCellArrayReal& m_back_flux_contrib_env;
  /*!
  [inout] front_flux_contrib_env
  */
  VariableCellArrayReal& m_front_flux_contrib_env;
  /*!
  [inout] back_flux_mass
  */
  VariableNodeReal& m_back_flux_mass;
  /*!
  [inout] front_flux_mass
  */
  VariableNodeReal& m_front_flux_mass;
  /*!
  [inout] back_flux_mass_env
  */
  VariableNodeArrayReal& m_back_flux_mass_env;
  /*!
  [inout] front_flux_mass_env
  */
  VariableNodeArrayReal& m_front_flux_mass_env;
  /*!
  [inout] u_dual_lagrange
  */
  VariableNodeArrayReal& m_u_dual_lagrange;
  /*!
  [inout] phi_dual_lagrange
  */
  VariableNodeArrayReal& m_phi_dual_lagrange;
};

//! Classe de variable pour appliRemap
struct RemapADIAppliRemapVars final
{
  explicit RemapADIAppliRemapVars(const VariableScalarInteger& sens_projection)
  : m_sens_projection(sens_projection)
  {}

  /*!
  [in] sens_projection
  */
  const VariableScalarInteger& m_sens_projection;
};

//! Classe de variable pour resizeRemapVariables
struct RemapADIResizeRemapVariablesVars final
{
  RemapADIResizeRemapVariablesVars(VariableCellArrayReal& u_lagrange,
      VariableNodeArrayReal& u_dual_lagrange,
      VariableCellArrayReal& phi_lagrange,
      VariableNodeArrayReal& phi_dual_lagrange,
      VariableNodeArrayReal& dual_grad_phi,
      VariableCellArrayReal& grad_phi,
      VariableFaceArrayReal& phi_face,
      VariableFaceArrayReal& grad_phi_face,
      VariableCellArrayReal& delta_phi_face_ar,
      VariableCellArrayReal& delta_phi_face_av,
      VariableCellArrayReal& dual_phi_flux,
      VariableNodeArrayReal& front_flux_mass_env,
      VariableNodeArrayReal& back_flux_mass_env,
      VariableCellArrayReal& back_flux_contrib_env,
      VariableCellArrayReal& front_flux_contrib_env)
  : m_u_lagrange(u_lagrange)
  , m_u_dual_lagrange(u_dual_lagrange)
  , m_phi_lagrange(phi_lagrange)
  , m_phi_dual_lagrange(phi_dual_lagrange)
  , m_dual_grad_phi(dual_grad_phi)
  , m_grad_phi(grad_phi)
  , m_phi_face(phi_face)
  , m_grad_phi_face(grad_phi_face)
  , m_delta_phi_face_ar(delta_phi_face_ar)
  , m_delta_phi_face_av(delta_phi_face_av)
  , m_dual_phi_flux(dual_phi_flux)
  , m_front_flux_mass_env(front_flux_mass_env)
  , m_back_flux_mass_env(back_flux_mass_env)
  , m_back_flux_contrib_env(back_flux_contrib_env)
  , m_front_flux_contrib_env(front_flux_contrib_env)
  {}

  /*!
  [out] u_lagrange
  */
  VariableCellArrayReal& m_u_lagrange;
  /*!
  [out] u_dual_lagrange
  */
  VariableNodeArrayReal& m_u_dual_lagrange;
  /*!
  [out] phi_lagrange
  */
  VariableCellArrayReal& m_phi_lagrange;
  /*!
  [out] phi_dual_lagrange
  */
  VariableNodeArrayReal& m_phi_dual_lagrange;
  /*!
  [out] dual_grad_phi
  */
  VariableNodeArrayReal& m_dual_grad_phi;
  /*!
  [out] grad_phi
  */
  VariableCellArrayReal& m_grad_phi;
  /*!
  [out] phi_face
  */
  VariableFaceArrayReal& m_phi_face;
  /*!
  [out] grad_phi_face
  */
  VariableFaceArrayReal& m_grad_phi_face;
  /*!
  [out] delta_phi_face_ar
  */
  VariableCellArrayReal& m_delta_phi_face_ar;
  /*!
  [out] delta_phi_face_av
  */
  VariableCellArrayReal& m_delta_phi_face_av;
  /*!
  [out] dual_phi_flux
  */
  VariableCellArrayReal& m_dual_phi_flux;
  /*!
  [out] front_flux_mass_env
  */
  VariableNodeArrayReal& m_front_flux_mass_env;
  /*!
  [out] back_flux_mass_env
  */
  VariableNodeArrayReal& m_back_flux_mass_env;
  /*!
  [out] back_flux_contrib_env
  */
  VariableCellArrayReal& m_back_flux_contrib_env;
  /*!
  [out] front_flux_contrib_env
  */
  VariableCellArrayReal& m_front_flux_contrib_env;
};

//! Classe de variable pour synchronizeUremap
struct RemapADISynchronizeUremapVars final
{
  RemapADISynchronizeUremapVars(VariableCellArrayReal& phi_lagrange,
      VariableCellArrayReal& u_lagrange,
      VariableCellArrayReal& dual_phi_flux,
      VariableCellInteger& est_mixte,
      VariableCellInteger& est_pure)
  : m_phi_lagrange(phi_lagrange)
  , m_u_lagrange(u_lagrange)
  , m_dual_phi_flux(dual_phi_flux)
  , m_est_mixte(est_mixte)
  , m_est_pure(est_pure)
  {}

  /*!
  [out] phi_lagrange
  */
  VariableCellArrayReal& m_phi_lagrange;
  /*!
  [out] u_lagrange
  */
  VariableCellArrayReal& m_u_lagrange;
  /*!
  [out] dual_phi_flux
  */
  VariableCellArrayReal& m_dual_phi_flux;
  /*!
  [out] est_mixte
  */
  VariableCellInteger& m_est_mixte;
  /*!
  [out] est_pure
  */
  VariableCellInteger& m_est_pure;
};

//! Classe de variable pour remapVariables
struct RemapADIRemapVariablesVars final
{
  RemapADIRemapVariablesVars(const VariableCellReal& euler_volume,
      const VariableCellArrayReal& u_lagrange,
      const VariableNodeArrayReal& u_dual_lagrange,
      VariableCellInteger& est_pure,
      VariableNodeReal3& velocity,
      VariableNodeReal& node_mass,
      MaterialVariableCellReal& cell_volume,
      VariableCellInteger& cell_status,
      VariableCellInteger& est_mixte,
      MaterialVariableCellReal& cell_mass,
      MaterialVariableCellReal& fracvol,
      MaterialVariableCellReal& mass_fraction,
      MaterialVariableCellReal& pseudo_viscosity,
      MaterialVariableCellReal& density,
      MaterialVariableCellReal& internal_energy)
  : m_euler_volume(euler_volume)
  , m_u_lagrange(u_lagrange)
  , m_u_dual_lagrange(u_dual_lagrange)
  , m_est_pure(est_pure)
  , m_velocity(velocity)
  , m_node_mass(node_mass)
  , m_cell_volume(cell_volume)
  , m_cell_status(cell_status)
  , m_est_mixte(est_mixte)
  , m_cell_mass(cell_mass)
  , m_fracvol(fracvol)
  , m_mass_fraction(mass_fraction)
  , m_pseudo_viscosity(pseudo_viscosity)
  , m_density(density)
  , m_internal_energy(internal_energy)
  {}

  /*!
  [in] euler_volume
  */
  const VariableCellReal& m_euler_volume;
  /*!
  [in] u_lagrange
  */
  const VariableCellArrayReal& m_u_lagrange;
  /*!
  [in] u_dual_lagrange
  */
  const VariableNodeArrayReal& m_u_dual_lagrange;
  /*!
  [out] est_pure
  */
  VariableCellInteger& m_est_pure;
  /*!
  [out] velocity
  */
  VariableNodeReal3& m_velocity;
  /*!
  [out] node_mass
  */
  VariableNodeReal& m_node_mass;
  /*!
  [inout] cell_volume
  */
  MaterialVariableCellReal& m_cell_volume;
  /*!
  [inout] cell_status
  */
  VariableCellInteger& m_cell_status;
  /*!
  [inout] est_mixte
  */
  VariableCellInteger& m_est_mixte;
  /*!
  [inout] cell_mass
  */
  MaterialVariableCellReal& m_cell_mass;
  /*!
  [inout] fracvol
  */
  MaterialVariableCellReal& m_fracvol;
  /*!
  [inout] mass_fraction
  */
  MaterialVariableCellReal& m_mass_fraction;
  /*!
  [inout] pseudo_viscosity
  */
  MaterialVariableCellReal& m_pseudo_viscosity;
  /*!
  [inout] density
  */
  MaterialVariableCellReal& m_density;
  /*!
  [inout] internal_energy
  */
  MaterialVariableCellReal& m_internal_energy;
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Remap

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP___REMAPADISERVICEVARS_H
