CREATE DATABASE  IF NOT EXISTS `db_proyectofinal_final` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `db_proyectofinal_final`;
-- MySQL dump 10.13  Distrib 8.0.41, for Win64 (x86_64)
--
-- Host: localhost    Database: db_proyectofinal_final
-- ------------------------------------------------------
-- Server version	8.0.41

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `clientes`
--

DROP TABLE IF EXISTS `clientes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `clientes` (
  `idCliente` int NOT NULL AUTO_INCREMENT,
  `nombres` varchar(60) DEFAULT NULL,
  `apellidos` varchar(60) DEFAULT NULL,
  `NIT` varchar(12) DEFAULT NULL,
  `genero` bit(1) DEFAULT NULL,
  `telefono` varchar(25) DEFAULT NULL,
  `correo_electronico` varchar(45) DEFAULT NULL,
  `fechaingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idCliente`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `clientes`
--

LOCK TABLES `clientes` WRITE;
/*!40000 ALTER TABLE `clientes` DISABLE KEYS */;
INSERT INTO `clientes` VALUES (1,'Andrea Alejandra','Flores Fuentes','123456789',_binary '\0','12345678','andrea@gmail.com','2025-05-31 22:59:49'),(2,'Diana Merary','Enriquez Chinchilla','987456123',_binary '\0','8745612','diana@gmail.com','2025-05-31 23:00:58'),(3,'Brallan Alberto','Villavicencio Perez','963258741',_binary '','14785236','brallan@gmail.com','2025-05-31 23:02:00'),(4,'Pedro Joel','Bamaca Cinto','741258963',_binary '','14563287','bamacamuchoflow@gmail.com','2025-05-31 23:09:13');
/*!40000 ALTER TABLE `clientes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `compras`
--

DROP TABLE IF EXISTS `compras`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `compras` (
  `idCompra` int NOT NULL AUTO_INCREMENT,
  `no_orden_compra` int DEFAULT NULL,
  `idProveedor` int DEFAULT NULL,
  `fecha_orden` date DEFAULT NULL,
  `fechaingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idCompra`),
  KEY `idProveedor` (`idProveedor`),
  CONSTRAINT `compras_ibfk_1` FOREIGN KEY (`idProveedor`) REFERENCES `proveedores` (`idProveedor`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `compras`
--

LOCK TABLES `compras` WRITE;
/*!40000 ALTER TABLE `compras` DISABLE KEYS */;
INSERT INTO `compras` VALUES (1,1,3,'2025-05-31','2025-05-31 23:11:15'),(2,1,1,'2025-05-31','2025-05-31 23:11:56');
/*!40000 ALTER TABLE `compras` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `compras_detalle`
--

DROP TABLE IF EXISTS `compras_detalle`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `compras_detalle` (
  `idcompra_detalle` bigint NOT NULL AUTO_INCREMENT,
  `idCompra` int DEFAULT NULL,
  `idProducto` int DEFAULT NULL,
  `cantidad` int DEFAULT NULL,
  `precio_costo_unitario` decimal(8,2) DEFAULT NULL,
  PRIMARY KEY (`idcompra_detalle`),
  KEY `idCompra` (`idCompra`),
  KEY `idProducto` (`idProducto`),
  CONSTRAINT `compras_detalle_ibfk_1` FOREIGN KEY (`idCompra`) REFERENCES `compras` (`idCompra`),
  CONSTRAINT `compras_detalle_ibfk_2` FOREIGN KEY (`idProducto`) REFERENCES `productos` (`idProducto`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `compras_detalle`
--

LOCK TABLES `compras_detalle` WRITE;
/*!40000 ALTER TABLE `compras_detalle` DISABLE KEYS */;
INSERT INTO `compras_detalle` VALUES (1,2,4,50,25.00);
/*!40000 ALTER TABLE `compras_detalle` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `empleados`
--

DROP TABLE IF EXISTS `empleados`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `empleados` (
  `idEmpleado` int NOT NULL AUTO_INCREMENT,
  `nombres` varchar(60) DEFAULT NULL,
  `apellidos` varchar(60) DEFAULT NULL,
  `direccion` varchar(80) DEFAULT NULL,
  `telefono` varchar(25) DEFAULT NULL,
  `DPI` varchar(15) DEFAULT NULL,
  `genero` bit(1) DEFAULT NULL,
  `fecha_nacimiento` date DEFAULT NULL,
  `idPuesto` smallint DEFAULT NULL,
  `fecha_inicio_labores` date DEFAULT NULL,
  `fechaingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idEmpleado`),
  KEY `idPuesto` (`idPuesto`),
  CONSTRAINT `empleados_ibfk_1` FOREIGN KEY (`idPuesto`) REFERENCES `puestos` (`idPuesto`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `empleados`
--

LOCK TABLES `empleados` WRITE;
/*!40000 ALTER TABLE `empleados` DISABLE KEYS */;
INSERT INTO `empleados` VALUES (1,'Jonathan Ubaldo','Alonso Lopez','col jrb zona 21','58616902','3605105820101',_binary '','2001-11-23',1,'2025-04-15','2025-05-31 23:06:03'),(2,'Escarleth Gabriela','Cuque Martinez','boca del monte','78965412','3650402580101',_binary '\0','2005-01-05',2,'2025-05-01','2025-05-31 23:07:10'),(3,'Juan Alejandro','Paz Paz','ciudad','45678912','1458756980101',_binary '','1990-01-01',3,'2025-05-01','2025-05-31 23:08:13');
/*!40000 ALTER TABLE `empleados` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `marcas`
--

DROP TABLE IF EXISTS `marcas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `marcas` (
  `idMarca` smallint NOT NULL AUTO_INCREMENT,
  `marca` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`idMarca`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `marcas`
--

LOCK TABLES `marcas` WRITE;
/*!40000 ALTER TABLE `marcas` DISABLE KEYS */;
INSERT INTO `marcas` VALUES (1,'Coca Cola'),(2,'Pepsi'),(3,'Laky Men'),(4,'Ducal'),(5,'Kelloggs');
/*!40000 ALTER TABLE `marcas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `productos`
--

DROP TABLE IF EXISTS `productos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `productos` (
  `idProducto` int NOT NULL AUTO_INCREMENT,
  `producto` varchar(50) DEFAULT NULL,
  `idMarca` smallint DEFAULT NULL,
  `Descripcion` varchar(100) DEFAULT NULL,
  `Imagen` varchar(30) DEFAULT NULL,
  `precio_costo` decimal(8,2) DEFAULT NULL,
  `precio_venta` decimal(8,2) DEFAULT NULL,
  `existencia` int DEFAULT NULL,
  `fecha_ingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idProducto`),
  KEY `idMarca` (`idMarca`),
  CONSTRAINT `productos_ibfk_1` FOREIGN KEY (`idMarca`) REFERENCES `marcas` (`idMarca`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `productos`
--

LOCK TABLES `productos` WRITE;
/*!40000 ALTER TABLE `productos` DISABLE KEYS */;
INSERT INTO `productos` VALUES (1,'Coca Cola',1,'Coca cola en lata 500ml','coca cola',8.00,10.00,50,'2025-05-31 23:02:47'),(2,'Pepsi Cola',2,'Pepsi en lata 500ml','pepsi',7.00,9.00,50,'2025-05-31 23:03:22'),(3,'Frijoles Ducal',4,'bolsa de frijoles ducal 800ml','bolsa',12.00,15.00,100,'2025-05-31 23:04:07'),(4,'Froot Loops',5,'Caja de cereal froot loops 800kg','caja',25.00,30.00,50,'2025-05-31 23:04:55');
/*!40000 ALTER TABLE `productos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `proveedores`
--

DROP TABLE IF EXISTS `proveedores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `proveedores` (
  `idProveedor` int NOT NULL AUTO_INCREMENT,
  `proveedor` varchar(60) DEFAULT NULL,
  `nit` varchar(12) DEFAULT NULL,
  `direccion` varchar(80) DEFAULT NULL,
  `telefono` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`idProveedor`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `proveedores`
--

LOCK TABLES `proveedores` WRITE;
/*!40000 ALTER TABLE `proveedores` DISABLE KEYS */;
INSERT INTO `proveedores` VALUES (1,'Industria de Alimentos','12345678','ciudad de Guatemala','12345678'),(2,'Industria de Bebidas GT','78945612','Boca del Monte','74125896'),(3,'SuperFideos GT','85236985','Villa Nueva','45612378');
/*!40000 ALTER TABLE `proveedores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `puestos`
--

DROP TABLE IF EXISTS `puestos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `puestos` (
  `idPuesto` smallint NOT NULL AUTO_INCREMENT,
  `puesto` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`idPuesto`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `puestos`
--

LOCK TABLES `puestos` WRITE;
/*!40000 ALTER TABLE `puestos` DISABLE KEYS */;
INSERT INTO `puestos` VALUES (1,'Gerente'),(2,'Cajero'),(3,'Conserje'),(4,'Sub Gerente'),(5,'auxiliar de bodega');
/*!40000 ALTER TABLE `puestos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ventas`
--

DROP TABLE IF EXISTS `ventas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ventas` (
  `idVenta` int NOT NULL AUTO_INCREMENT,
  `nofactura` int DEFAULT NULL,
  `serie` char(1) DEFAULT NULL,
  `fechafactura` date DEFAULT NULL,
  `idCliente` int DEFAULT NULL,
  `idEmpleado` int DEFAULT NULL,
  `fechaingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idVenta`),
  KEY `idCliente` (`idCliente`),
  KEY `idEmpleado` (`idEmpleado`),
  CONSTRAINT `ventas_ibfk_1` FOREIGN KEY (`idCliente`) REFERENCES `clientes` (`idCliente`),
  CONSTRAINT `ventas_ibfk_2` FOREIGN KEY (`idEmpleado`) REFERENCES `empleados` (`idEmpleado`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ventas`
--

LOCK TABLES `ventas` WRITE;
/*!40000 ALTER TABLE `ventas` DISABLE KEYS */;
INSERT INTO `ventas` VALUES (1,1,'A','2025-05-31',4,2,'2025-05-31 23:09:34');
/*!40000 ALTER TABLE `ventas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ventas_detalle`
--

DROP TABLE IF EXISTS `ventas_detalle`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ventas_detalle` (
  `idventa_detalle` bigint NOT NULL AUTO_INCREMENT,
  `idVenta` int DEFAULT NULL,
  `idProducto` int DEFAULT NULL,
  `cantidad` varchar(45) DEFAULT NULL,
  `precio_unitario` decimal(8,2) DEFAULT NULL,
  PRIMARY KEY (`idventa_detalle`),
  KEY `idVenta` (`idVenta`),
  KEY `idProducto` (`idProducto`),
  CONSTRAINT `ventas_detalle_ibfk_1` FOREIGN KEY (`idVenta`) REFERENCES `ventas` (`idVenta`),
  CONSTRAINT `ventas_detalle_ibfk_2` FOREIGN KEY (`idProducto`) REFERENCES `productos` (`idProducto`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ventas_detalle`
--

LOCK TABLES `ventas_detalle` WRITE;
/*!40000 ALTER TABLE `ventas_detalle` DISABLE KEYS */;
INSERT INTO `ventas_detalle` VALUES (1,1,1,'2',10.00),(2,1,4,'1',30.00);
/*!40000 ALTER TABLE `ventas_detalle` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-05-31 23:16:32
