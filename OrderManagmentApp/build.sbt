name := """OrderManagmentApp"""

version := "1.0-SNAPSHOT"

lazy val root = (project in file(".")).enablePlugins(PlayScala)


resolvers += Resolver.sonatypeRepo("snapshots")

scalaVersion := "2.12.7"

crossScalaVersions := Seq("2.11.12", "2.12.7")

libraryDependencies += guice
libraryDependencies += "org.scalatestplus.play" %% "scalatestplus-play" % "3.1.2" % Test
libraryDependencies += "com.h2database" % "h2" % "1.4.197"
libraryDependencies += javaForms
libraryDependencies += filters
libraryDependencies ++= Seq(evolutions, jdbc)
libraryDependencies += "mysql" % "mysql-connector-java" % "5.1.24"



