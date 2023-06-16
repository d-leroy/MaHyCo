#include "IDtCellInfo.h"

ARCCORE_HOST_DEVICE inline void
DtCellInfoVoid::VarCellSetter::setCellValue(CellLocalId cid, Real value) const {
  // aucune valeur modifiée
}

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
