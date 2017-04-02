-- phpMyAdmin SQL Dump
-- version 4.6.5.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Apr 02, 2017 at 06:44 PM
-- Server version: 5.6.35
-- PHP Version: 7.1.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Database: `calc`
--

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(6) NOT NULL,
  `first_name` varchar(30) NOT NULL,
  `last_name` varchar(30) NOT NULL,
  `email` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `mode` int(6) NOT NULL,
  `history` text NOT NULL,
  `sgroup` text NOT NULL,
  `assign` text NOT NULL,
  `score` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `first_name`, `last_name`, `email`, `password`, `mode`, `history`, `sgroup`, `assign`, `score`) VALUES
(1, 'Konstantin', 'Miagkov', 'kostyamyagkov@gmail.com', 'bububu', 1, 'Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:12:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:6:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:23:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:45:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:367:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:23:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|', '', '', ''),
(11, 'Joe', 'Bruin', 'bruin@ucla.edu', 'gobruins', 2, 'Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:10:1|::|', '', '', ''),
(13, 'John', 'Doe', 'john@doe.com', 'sad', 1, 'Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:23:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:23:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:23:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:24:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:26:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:56:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:36:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:55:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:55:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:4:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:222:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:222:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:22:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:23:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:23:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:21:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:23:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:45:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:34:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:45:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:33:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:333:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:34:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:12:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2323:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:2323:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:23:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:1:1|Evaluate $\\frac{1}{\\sqrt{\\pi}}\\int \\limits_{-\\infty}^{\\infty} e^{-x^2}dx$:23:1|Evaluate $$\\int0dx$$:0:\\log\\left(\\frac{5}{9}\\right)|Evaluate $$\\int\\left(\\frac{-11}{4} \\cdot 1\\right)dx$$:-11/4x:x \\cdot \\frac{-11}{4}|', '', '', ''),
(14, 'Kyle', 'Hess', 'hess.kyler@gmail.com', 'blablabla', 1, '', '', '', '');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(6) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;
