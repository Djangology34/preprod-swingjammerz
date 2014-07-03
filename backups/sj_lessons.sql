-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le : Jeu 12 Juin 2014 à 17:30
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
-- Structure de la table `sj_lessons`
--

CREATE TABLE IF NOT EXISTS `sj_lessons` (
  `sjl_id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Unique identifier for a lesson item.',
  `name` varchar(255) NOT NULL DEFAULT '' COMMENT 'The name of the lesson.',
  `type` varchar(255) NOT NULL DEFAULT '' COMMENT 'The type of lesson.',
  `day` varchar(255) NOT NULL DEFAULT '' COMMENT 'The day of lesson.',
  `time` varchar(255) DEFAULT '' COMMENT 'The time of lesson.',
  `level` varchar(255) NOT NULL DEFAULT '' COMMENT 'The level of lesson.',
  `place` varchar(255) DEFAULT '' COMMENT 'The place of lesson.',
  `max_capacity_leader` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'The max capacity of leader in the lesson.',
  `max_capacity_follower` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'The max capacity of follower in the lesson.',
  `enabled` tinyint(3) unsigned NOT NULL DEFAULT '1' COMMENT 'The available capacity of follower in the lesson.',
  `full` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'The available capacity of follower in the lesson.',
  `language` varchar(255) DEFAULT 'fr' COMMENT 'Language.',
  `year` varchar(255) NOT NULL DEFAULT '2014' COMMENT 'The year of the lesson.',
  PRIMARY KEY (`sjl_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='Stores lessons.' AUTO_INCREMENT=11 ;

--
-- Contenu de la table `sj_lessons`
--

INSERT INTO `sj_lessons` (`sjl_id`, `name`, `type`, `day`, `time`, `level`, `place`, `max_capacity_leader`, `max_capacity_follower`, `enabled`, `full`, `language`, `year`) VALUES
(3, 'Cours Lundi - Lindy Hop Avancé Mpt Chopin', 'lindy hop', 'lundi', '19:00', 'avancé', 'MPT Chopin', 12, 18, 1, 0, 'fr', '2014'),
(6, 'Cours Mardi - Lindy Hop Débutant Entrepôt', 'lindy hop', 'mardi', '21:00', 'débutant', 'Entrepôt', 20, 20, 1, 0, 'fr', '2014'),
(7, 'Cours Lundi - Lindy Hop Débutant Mpt Chopin', 'lindy hop', 'lundi', '19:00', 'débutant', 'Mpt Chopin', 15, 25, 1, 0, 'fr', '2014'),
(8, 'Cours Mercredi - Charleston Solo Intermédiaire Figuerolles', 'lindy hop', 'mercredi', '22:00', 'intermédiaire', 'Figuerolles', 0, 30, 1, 0, 'fr', '2015'),
(9, 'Cours Jeudi - Charleston Solo Mpt Chopin', 'charleston solo', 'jeudi', '21:00', 'débutant', 'MPT Chopin', 25, 0, 1, 0, 'fr', '2014');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
