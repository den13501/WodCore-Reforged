-- --------------------------------------------------------
-- 主機:                           127.0.0.1
-- 伺服器版本:                        5.7.36 - MySQL Community Server (GPL)
-- 伺服器作業系統:                      Win64
-- HeidiSQL 版本:                  11.3.0.6295
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

-- 傾印  資料表 auth.motd 結構
DROP TABLE IF EXISTS `motd`;
CREATE TABLE IF NOT EXISTS `motd` (
  `RealmID` int(10) unsigned NOT NULL,
  `Text` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `TextCN` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `TextTW` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `TextFR` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `TextES` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `TextRU` text COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`RealmID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- 正在傾印表格  auth.motd 的資料：~1 rows (近似值)
DELETE FROM `motd`;
/*!40000 ALTER TABLE `motd` DISABLE KEYS */;
INSERT INTO `motd` (`RealmID`, `Text`, `TextCN`, `TextTW`, `TextFR`, `TextES`, `TextRU`) VALUES
	(1, 'english motd', '歡迎來到魔獸世界！', '歡迎來到魔獸世界！', 'french motd', 'spanish motd', 'russian motd');
/*!40000 ALTER TABLE `motd` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
