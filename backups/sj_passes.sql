-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le : Lun 09 Juin 2014 à 17:45
-- Version du serveur: 5.5.37
-- Version de PHP: 5.3.10-1ubuntu3.11

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `swingjammerz`
--

-- --------------------------------------------------------

--
-- Structure de la table `sj_passes`
--

CREATE TABLE IF NOT EXISTS `sj_passes` (
  `sjp_id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Unique identifier for a pass item.',
  `name` varchar(255) NOT NULL DEFAULT '' COMMENT 'The name of the pass.',
  `price` varchar(255) NOT NULL DEFAULT '' COMMENT 'The price of the pass.',
  `currency` varchar(255) NOT NULL DEFAULT 'EUR' COMMENT 'The currency of the pass.',
  `year` varchar(255) NOT NULL DEFAULT '2014' COMMENT 'The year of the pass.',
  `nb_lessons` varchar(255) NOT NULL DEFAULT '1' COMMENT 'The number of lessons allowed by the pass.',
  `enabled` tinyint(3) unsigned NOT NULL DEFAULT '1' COMMENT 'The available capacity of follower in the lesson.',
  `created_at` datetime NOT NULL COMMENT 'The creation date timestamp.',
  PRIMARY KEY (`sjp_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='Stores passes.' AUTO_INCREMENT=5 ;

--
-- Contenu de la table `sj_passes`
--

INSERT INTO `sj_passes` (`sjp_id`, `name`, `price`, `currency`, `year`, `nb_lessons`, `enabled`, `created_at`) VALUES
(1, 'Pass 1 cours à l''année', '150', 'EUR', '2014', '1', 1, '2014-06-09 17:11:07'),
(2, 'Pass 2 cours à l''année', '230', 'EUR', '2014', '2', 1, '2014-06-09 17:11:19'),
(3, 'Pass cours', '300', 'EUR', '2014', 'all', 1, '2014-06-09 17:11:32'),
(4, 'Pass Swing', '500', 'EUR', '2014', 'all', 1, '2014-06-09 17:11:46');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
