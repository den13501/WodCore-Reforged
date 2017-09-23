-- Removing custom firestorm creatures
-- Cleanup loyalty npc, transmog npc and exp rate modifier npc
DELETE FROM creature WHERE id IN (SELECT entry FROM creature_template WHERE scriptname IN ('npc_loyalty_point','npc_legendary_transmogrificator','npc_rate_xp_modifier'));

-- delete creatures on GM island
DELETE FROM creature WHERE id IN (370048);
DELETE FROM creature where map=1 AND zoneid=876;

-- Removing custom firestorm gobject spawns based on phasemask and map, zone combination
-- select for zones
-- select * from gameobject where
-- map = 0 and zoneid = 11 and areaid=11;
-- map = 0 and zoneid = 139 and areaid=139;
-- map = 0 and zoneid = 214 and areaid=214;
-- map = 0 and zoneid = 2037 and areaid=2037;
-- map = 1 and zoneid = 0 and areaid=0;
-- map = 1 and zoneid = 876 and areaid=876;
-- map = 530 and zoneid = 0 and areaid=0;
-- map = 646 and zoneid = 0 and areaid=0;
-- map = 646 and zoneid = 5042 and areaid=5042;
-- map = 648 and zoneid = 4737 and areaid=4737;
-- map = 861 and zoneid = 5733 and areaid=5817;

-- delete query
DELETE FROM gameobject WHERE phasemask=4294967295 AND map < 1000 AND map NOT IN (654,720,730,860,870) AND id NOT IN (180751,18890,189990,202747,202748,233600,194264,183323,10227833,243477) ORDER BY map,zoneid;
DELETE FROM gameobject WHERE phasemask=1 AND map=0 AND zoneid=139 AND areaid=139 AND guid BETWEEN 50000000 AND 79999999;
DELETE FROM gameobject WHERE phasemask=1 AND map=0 AND zoneid=214 AND areaid=214 AND guid BETWEEN 50000000 AND 79999999;
DELETE FROM gameobject WHERE phasemask=1 AND map=0 AND zoneid=2037 AND areaid=2037 AND guid BETWEEN 50000000 AND 79999999;
DELETE FROM gameobject WHERE phasemask=1 AND map=1 AND zoneid=0 AND areaid=0 AND guid BETWEEN 30000000 AND 79999999;
DELETE FROM gameobject WHERE map=1 AND zoneid=876 AND areaid=876;
DELETE FROM gameobject WHERE phasemask=65535 AND map=646 AND zoneid=5042 AND areaid=5042 AND guid BETWEEN 4000000 AND 79999999;
DELETE FROM gameobject WHERE phasemask=1 AND map=648 AND zoneid=4737 AND areaid=4737 AND guid BETWEEN 50000000 AND 79999999;
DELETE FROM gameobject WHERE phasemask=1 AND map=861 AND zoneid=5733 AND guid BETWEEN 50000000 AND 79999999;

-- commands reset for our server
-- command
update command set security=3 where security <>3;

-- commands players
update command set security=0 where name in
("account","account lock","account set password","commands","dismount","gm ingame","help","save","server","server info");