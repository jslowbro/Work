package controllers

import java.sql.Timestamp

import javax.inject.{Inject, Singleton}
import models.{Item, Order}
import play.api.libs.json.Json
import play.api.mvc.{AbstractController, ControllerComponents}
import services.DBO

@Singleton
class APIController @Inject()(cc: ControllerComponents, af: AssetsFinder, dbo: DBO)(implicit assetsFinder: AssetsFinder)
  extends AbstractController(cc)  {

  //handling Jsons of

  implicit val jsonwriter = Json.writes[Item]

  implicit val jsonreader = Json.reads[Item]

  implicit val jsonwriterOrder = Json.writes[Order]


  //TODO DBOOOOOOOOOOOOOOOOOOOOOOOO
  val itemlist = List(
    Item("Tom",20, "S", "BLUE"),
    Item("Tom",20, "M", "GREEN"),
    Item("Tom",20, "L","BLUE"),
    Item("Tom",20, "XL","BLUE")
  )


  // APIs

  def getListOfAllItems() = {
    TODO
  }

  def getListOfItems(id: Int) = Action {
    println("Getting List of items for order No." + id)
    val json = Json.toJson(itemlist)
    Ok(json)
  }

  def getListOfOrders() = Action {
    //TODO get list from DBO
    /*val items =  List(Item("Sam",20,"S","BLUE"),
      Item("Sam",20,"S","BLUE"),
      Item("Sam",20,"S","BLUE"),
      Item("Sam",20,"S","BLUE"))

    val timestampString = new Timestamp(System.currentTimeMillis()).toString


    val list = List(
      Order(1, timestampString,items),
      Order(2, timestampString,items),
      Order(3, timestampString,items),
      Order(4, timestampString,items)
    )*/
    val list = dbo.getOrderList
    val json = Json.toJson(list)
    Ok(json)
  }

  def postListOfItems() = Action { implicit request =>
      //parsing Json to a list
      val json  = request.body.asJson.get
      val list: List[Item] = json.as[List[Item]]
      dbo.postItems(list)
      Ok
  }

  //TODO Api's for stock managment

  def getStockInfo() = {
    TODO
  }

  def upateStockInfo() = {
    TODO
  }

}
