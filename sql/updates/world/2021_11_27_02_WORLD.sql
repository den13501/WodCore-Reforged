-- https://github.com/TrinityCore/TrinityCore/commit/17fd20f50c09aaff6b6741353b8ab21bff8f12fd
-- DB/Quest: Redemption
-- Fix missing delete.
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(17, 0, 8593, 0, 0, 29, 0, 17542, 40, 0, 0, 0, '', 'Symbol of Life can be casted within 40 yards of Young Furbolg Shaman'),
(17, 0, 8593, 0, 1, 29, 0, 6172, 40, 0, 0, 0, '', 'Symbol of Life can be casted within 40 yards Henze Faulk'),
(17, 0, 8593, 0, 2, 29, 0, 6177, 40, 0, 0, 0, '', 'Symbol of Life can be casted within 40 yards Henze Faulk')