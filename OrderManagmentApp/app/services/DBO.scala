package services

import java.sql._

import javax.inject.Inject
import models.{Item, Order}
import play.api.db._
import play.api.mvc.{BaseController, ControllerComponents}

class DBO @Inject()(db: Database, val controllerComponents: ControllerComponents) extends BaseController {

  /*val list: List[Item] = new ArrayList[Item]*/
  val url = "jdbc:mysql://localhost/shoesdb"
  val driver = "com.mysql.jdbc.Driver"
  val username = "root"
  val password = ""


  //loadFromMySQLDatabase

 /* def loadFromMySQLDatabase = {

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

  }*/

  def helloWorld = {
    val conn = db.getConnection()

    try{
      val statement = conn.createStatement()
      val rs = statement.executeQuery("SELECT * FROM items")

      while(rs.next()){
        val item: Item = Item(rs.getString("name"), rs.getInt("age"), rs.getString("size"), rs.getString("color"))
        println(item)
      }
    } catch {
      case e: Exception => e.printStackTrace()
    } finally {
      conn.close()
    }

  }

  def postItems(list: List[Item]) = {
    val conn = db.getConnection()

    try {
      //new Order
      val insertOrderPrepQuery = "INSERT INTO orders(timestamp) VALUES(?)"
      val statement1 = conn.prepareStatement(insertOrderPrepQuery)
      statement1.setTimestamp(1, new Timestamp(System.currentTimeMillis()))
      statement1.execute()
      //get new Order Id
      val getThatOrderId = "SELECT COUNT(*) FROM orders"
      val statement2 = conn.createStatement()
      val resultSet2 = statement2.executeQuery(getThatOrderId)
      resultSet2.next()
      val count = resultSet2.getInt(1)
      //adding List of Items assigned to an Order
      for(item <- list){
        val insertItemPrepQuery = "INSERT INTO items(name,age,size,color,order_id) VALUES(?,?,?,?,?)"
        val statement3 = conn.prepareStatement(insertItemPrepQuery)
        statement3.setString(1, item.name )
        statement3.setInt(2, item.age)
        statement3.setString(3, item.size )
        statement3.setString(4, item.color )
        statement3.setInt(5, count)
        statement3.execute()
      }

    } catch {
      case e: Exception => e printStackTrace()
    } finally {
      conn.close()
    }
  }

  def getOrderList: List[Order] = {
    val conn = db.getConnection()

    try {

    } catch {
      case e: Exception => e.printStackTrace()

    } finally
  }





}
