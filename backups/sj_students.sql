-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le : Mar 01 Juillet 2014 à 17:12
-- Version du serveur: 5.5.37
-- Version de PHP: 5.3.10-1ubuntu3.12

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
-- Structure de la table `sj_students`
--

CREATE TABLE IF NOT EXISTS `sj_students` (
  `sjs_id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Unique identifier for a student item.',
  `firstname` varchar(255) NOT NULL DEFAULT '' COMMENT 'The firstname of the student.',
  `lastname` varchar(255) NOT NULL DEFAULT '' COMMENT 'The lastname of the student.',
  `gender` varchar(255) NOT NULL DEFAULT '' COMMENT 'The gender of the student.',
  `email` varchar(255) NOT NULL DEFAULT '' COMMENT 'The email of the student.',
  `phone` varchar(255) DEFAULT '' COMMENT 'The phone of the student.',
  `address` varchar(255) NOT NULL DEFAULT '' COMMENT 'The address of the student.',
  `postcode` varchar(255) DEFAULT '' COMMENT 'The postcode of the student.',
  `city` varchar(255) DEFAULT '' COMMENT 'The city of the student.',
  `pass_id` int(10) unsigned DEFAULT NULL COMMENT 'The pass the student bought.',
  `payed` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'Has the student payed.',
  `payment_method` varchar(255) DEFAULT '' COMMENT 'The payment method of student.',
  `waiting_list` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'Is the student on waiting list.',
  `couple_id` int(10) unsigned DEFAULT NULL COMMENT 'The couple id of the student if there is.',
  `enabled` tinyint(3) unsigned NOT NULL DEFAULT '1' COMMENT 'Is the student enabled.',
  `language` varchar(255) DEFAULT 'fr' COMMENT 'Language.',
  `created_at` datetime NOT NULL COMMENT 'The creation date timestamp.',
  PRIMARY KEY (`sjs_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='Stores students.' AUTO_INCREMENT=6 ;

--
-- Contenu de la table `sj_students`
--

INSERT INTO `sj_students` (`sjs_id`, `firstname`, `lastname`, `gender`, `email`, `phone`, `address`, `postcode`, `city`, `pass_id`, `payed`, `payment_method`, `waiting_list`, `couple_id`, `enabled`, `language`, `created_at`) VALUES
(1, 'David', 'Tavani', 'masculin', 'swingjammerzband@gmail.com', '0626237158', '300 avenue Saint Maur', '34000', 'Montpellier', 4, 0, 'paypal', 0, 2, 1, 'fr', '2014-06-12 17:38:09'),
(2, 'Katalin', 'Somlai', 'féminin', 'swingjammerzband@gmail.com', '0626237158', '33 rue Django Reinhardt', '34000', 'Budapest', 4, 0, 'paypal', 0, 1, 1, 'fr', '2014-06-12 17:38:09'),
(3, 'Fernando', 'Morisson', 'masculin', 'fer@fer.com', '065546', 'test', '34598', 'Montpellier', 4, 0, 'cheque', 1, NULL, 1, 'fr', '2014-06-13 11:46:38'),
(4, 'Simon', 'Laurent', 'masculin', 'simon.laurent@gmail.com', '06578648498', 'Adresse de Simon', '34000', 'Montpellier', 4, 0, 'paypal', 0, 5, 1, 'fr', '2014-07-01 17:01:04'),
(5, 'Luana', 'Jugmann', 'féminin', 'luana@gmail.com', '0754651565', 'Adresse Luana', '34000', 'Montpellier', 4, 0, 'paypal', 0, 4, 1, 'fr', '2014-07-01 17:01:04');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
