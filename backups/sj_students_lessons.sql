-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le : Ven 13 Juin 2014 à 11:49
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
-- Structure de la table `sj_students_lessons`
--

CREATE TABLE IF NOT EXISTS `sj_students_lessons` (
  `sj_student_id` int(10) unsigned NOT NULL COMMENT 'Unique identifier for a student item.',
  `sj_lesson_id` int(10) unsigned NOT NULL COMMENT 'Unique identifier for a lesson item.'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Stores relation between students and lessons.';

--
-- Contenu de la table `sj_students_lessons`
--

INSERT INTO `sj_students_lessons` (`sj_student_id`, `sj_lesson_id`) VALUES
(1, 6),
(2, 6),
(1, 7),
(2, 7),
(1, 9),
(2, 9),
(3, 6),
(3, 7);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
