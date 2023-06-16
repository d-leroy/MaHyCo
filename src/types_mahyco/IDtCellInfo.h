#ifndef TYPES_MAHYCO__IDTCELLINFO_H
#define TYPES_MAHYCO__IDTCELLINFO_H

#include "accenv/AcceleratorUtils.h"

#include "arcane/MeshVariableScalarRef.h"
#include "arcane/VariableTypedef.h"
#include "arcane/VariableBuildInfo.h"
#include "arcane/IMesh.h"
#include "arcane/utils/StringBuilder.h"

#include "arcane/accelerator/VariableViews.h"

#include "arcane/materials/IMeshMaterial.h"
#include "arcane/materials/MeshMaterialVariableRef.h"
#include "arcane/materials/CellToAllEnvCellConverter.h"

using namespace Arcane;
using namespace Arcane::Materials;

class DtCellInfoVoid {
 public:
  // VarCellSetter vide, n'affecte rien aucune variable sur accélérateur
  class VarCellSetter {
   public:
    ARCCORE_HOST_DEVICE inline void
    DtCellInfoVoid::VarCellSetter::setCellValue(CellLocalId cid, Real value) const {
      // aucune valeur modifiée
    }
  };

  DtCellInfoVoid::VarCellSetter
  DtCellInfoVoid::dxSoundSetter([[maybe_unused]] ax::RunCommand& command) {
    return DtCellInfoVoid::VarCellSetter();
  }

  Real
  DtCellInfoVoid::computeMinCellInfo([[maybe_unused]] CellGroup cell_group, [[maybe_unused]] Materials::IMeshMaterialMng* mm, 
      [[maybe_unused]] const Materials::MaterialVariableCellReal& v_sound_speed,
      [[maybe_unused]] const VariableCellReal& v_caracteristic_length) {
    return FloatInfo < Real >::maxValue();
  }

  String
  DtCellInfoVoid::strInfo() const {
    return String(" (aucune info sur les mailles)");
  }
};

#endif