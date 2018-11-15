package services

import java.sql._
import java.util
import java.util._

import models.Item

object DBO {

  val list: List[Item] = new ArrayList[Item]
  val url = "jdbc:mysql://localhost/shoesdb"
  val driver = "com.mysql.jdbc.Driver"
  val username = "root"
  val password = ""

  case class modelObject(names: List[String], ages: List[Int], colors: List[String], sizes: List[String] )

  loadFromMySQLDatabase

  def loadFromMySQLDatabase = {

    val connection: Connection = DriverManager.getConnection(url, username, password)
    try {
      Class.forName(driver)
      val statement = connection.createStatement
      val rs = statement.executeQuery("SELECT * FROM items")
      while (rs.next) {
        var item: Item = Item(rs.getString("name"), rs.getInt("age"), rs.getString("size"), rs.getString("color"))
        list.add(item)

      }

    } catch {
      case e: Exception => e.printStackTrace
        println("Couldn't access database")
    } finally {
      connection.close()
    }
    println(list)

  }
  def saveToDB = {
    val connection: Connection = DriverManager.getConnection(url, username, password)
    try {
      Class.forName(driver)
      /*val statement = connection.createStatement
      val rs = statement.executeQuery("SELECT * FROM items")
      while (rs.next) {
        var item: Item = Item(rs.getString("name"), rs.getInt("age"), rs.getString("color"), rs.getString("size"))
        list.add(item)

      }*/
      var ordersQuery: String = "INSERT INTO orders(timestamp) VALUES(?)"
      val ordersStatement: PreparedStatement = connection.prepareStatement(ordersQuery)
      ordersStatement.setObject(1, new Timestamp(System.currentTimeMillis()))






    } catch {
      case e: Exception => e.printStackTrace
        println("Couldn't access database")
    } finally {
      connection.close()
    }
    println(list)
  }



}
