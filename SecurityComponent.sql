USE SecurityComponent;

DROP TABLE IF EXISTS `T_USER_ROLES`;
DROP TABLE IF EXISTS `T_USERS`;
DROP TABLE IF EXISTS `T_ROLES`;

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `T_ROLES` (
  `IdRole` int(11) NOT NULL,
  `RoleName` varchar(50) NOT NULL,
  PRIMARY KEY (`IdRole`),
  UNIQUE KEY `RoleName` (`RoleName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `T_ROLES`
--

LOCK TABLES `T_ROLES` WRITE;
/*!40000 ALTER TABLE `T_ROLES` DISABLE KEYS */;
INSERT INTO `T_ROLES` VALUES (1,'admin'),(2,'demo');
/*!40000 ALTER TABLE `T_ROLES` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `T_USERS`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `T_USERS` (
  `IdUser` int(11) NOT NULL,
  `Login` varchar(50) NOT NULL,
  `Password` varchar(50) NOT NULL,
  `ConnectionNumber` int(11) NOT NULL DEFAULT 0,
  `LastConnection` int(11) DEFAULT NULL,
  `ConsecutiveError` int(11) DEFAULT 0,
  `IsDisabled` int(11) DEFAULT 0,
  `FirstName` varchar(25) NOT NULL DEFAULT '',
  `LastName` varchar(25) NOT NULL DEFAULT '',
  `Email` varchar(50) NOT NULL DEFAULT '',
  PRIMARY KEY (`IdUser`),
  UNIQUE KEY `Login` (`Login`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `T_USERS`
--

LOCK TABLES `T_USERS` WRITE;
/*!40000 ALTER TABLE `T_USERS` DISABLE KEYS */;
INSERT INTO `T_USERS` VALUES (1,'root','password',0,0,0,0,'root','administrator','root@devs.com');
INSERT INTO `T_USERS` VALUES (2,'ripley','alien',0,0,0,0,'Ripley','Ellen','ellen@nostromo.star');
INSERT INTO `T_USERS` VALUES (3,'bond','007',0,0,0,0,'James','Bond','007@mi6.uk');
/*!40000 ALTER TABLE `T_USERS` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `T_USER_ROLES`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `T_USER_ROLES` (
  `IdUser` int(11) DEFAULT NULL,
  `IdRole` int(11) DEFAULT NULL,
  KEY `IdUser` (`IdUser`),
  KEY `IdRole` (`IdRole`),
  CONSTRAINT `T_USER_ROLES_ibfk_1` FOREIGN KEY (`IdUser`) REFERENCES `T_USERS` (`IdUser`),
  CONSTRAINT `T_USER_ROLES_ibfk_2` FOREIGN KEY (`IdRole`) REFERENCES `T_ROLES` (`IdRole`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `T_USER_ROLES`
--

LOCK TABLES `T_USER_ROLES` WRITE;
/*!40000 ALTER TABLE `T_USER_ROLES` DISABLE KEYS */;
INSERT INTO `T_USER_ROLES` VALUES (1,1);
/*!40000 ALTER TABLE `T_USER_ROLES` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-11-21 23:08:22
