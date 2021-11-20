GRANT USAGE ON * . * TO 'root'@'localhost' IDENTIFIED BY 'root' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 ;

CREATE DATABASE `world` DEFAULT CHARACTER SET utf8mb4  COLLATE utf8mb4_unicode_ci;
CREATE DATABASE `characters` DEFAULT CHARACTER SET utf8mb4  COLLATE utf8mb4_unicode_ci;
CREATE DATABASE `auth` DEFAULT CHARACTER SET utf8mb4  COLLATE utf8mb4_unicode_ci;
CREATE DATABASE `hotfix` DEFAULT CHARACTER SET utf8mb4  COLLATE utf8mb4_unicode_ci;
CREATE DATABASE `web` DEFAULT CHARACTER SET utf8mb4  COLLATE utf8mb4_unicode_ci;

GRANT ALL PRIVILEGES ON `world` . * TO 'root'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `characters` . * TO 'root'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `auth` . * TO 'root'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `hotfix` . * TO 'root'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `web` . * TO 'root'@'localhost' WITH GRANT OPTION;
