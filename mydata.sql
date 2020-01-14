/*
Navicat MySQL Data Transfer

Source Server         : wwj
Source Server Version : 80018
Source Host           : localhost:3306
Source Database       : mydata

Target Server Type    : MYSQL
Target Server Version : 80018
File Encoding         : 65001

Date: 2019-12-31 10:36:27
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for admin
-- ----------------------------
DROP TABLE IF EXISTS `admin`;
CREATE TABLE `admin` (
  `user` varchar(255) NOT NULL,
  `pwd` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`user`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of admin
-- ----------------------------
INSERT INTO `admin` VALUES ('1', '1');
INSERT INTO `admin` VALUES ('11', '1');
INSERT INTO `admin` VALUES ('1111111', '11111');
INSERT INTO `admin` VALUES ('2', '2');
INSERT INTO `admin` VALUES ('3', '3');
INSERT INTO `admin` VALUES ('5', '5');
INSERT INTO `admin` VALUES ('e', 'e');
INSERT INTO `admin` VALUES ('ee', 'ee');
INSERT INTO `admin` VALUES ('q', 'q');
INSERT INTO `admin` VALUES ('w', 'w');

-- ----------------------------
-- Table structure for chatcontent
-- ----------------------------
DROP TABLE IF EXISTS `chatcontent`;
CREATE TABLE `chatcontent` (
  `id` int(255) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `time` varchar(255) NOT NULL,
  `content` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of chatcontent
-- ----------------------------
INSERT INTO `chatcontent` VALUES ('16', '172.19.101.21', '2019-12-20 10:59', '11');
INSERT INTO `chatcontent` VALUES ('17', '172.19.101.21', '2019-12-20 13:49', '1');
INSERT INTO `chatcontent` VALUES ('18', 'Server', '2019-12-20 13:49', '1');
INSERT INTO `chatcontent` VALUES ('19', 'Server', '2019-12-20 13:49', '2131231');
INSERT INTO `chatcontent` VALUES ('20', '172.19.101.21', '2019-12-20 13:50', '31231');
INSERT INTO `chatcontent` VALUES ('21', 'Server', '2019-12-20 14:06', '1');
INSERT INTO `chatcontent` VALUES ('22', '172.19.101.21', '2019-12-20 14:06', '1111');
INSERT INTO `chatcontent` VALUES ('23', 'Server', '2019-12-20 14:06', '我去打球我的');
INSERT INTO `chatcontent` VALUES ('24', '172.19.101.21', '2019-12-20 14:06', '倒萨倒萨达成');
INSERT INTO `chatcontent` VALUES ('25', '172.19.101.21', '2019-12-20 14:07', '大苏打大');
INSERT INTO `chatcontent` VALUES ('26', '172.19.101.21', '2019-12-20 14:07', '嘻嘻嘻嘻嘻嘻嘻嘻');
INSERT INTO `chatcontent` VALUES ('27', 'Server', '2019-12-20 14:08', '1111111111111111111111111111');
INSERT INTO `chatcontent` VALUES ('28', 'Server', '2019-12-23 08:57', '11');
INSERT INTO `chatcontent` VALUES ('29', '172.19.101.21', '2019-12-23 08:57', '11');
INSERT INTO `chatcontent` VALUES ('30', 'Server', '2019-12-23 08:57', '11');
INSERT INTO `chatcontent` VALUES ('31', 'Server', '2019-12-23 08:59', '1');
INSERT INTO `chatcontent` VALUES ('32', '172.19.101.21', '2019-12-23 08:59', '1');
INSERT INTO `chatcontent` VALUES ('33', '服务器', '2019-12-23 09:02', '1');
INSERT INTO `chatcontent` VALUES ('34', '172.19.101.21', '2019-12-23 09:02', '1');
