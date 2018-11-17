package controllers

import java.sql.Timestamp
import java.util

import javax.inject._
import models._
import play.api.mvc._
import services.DBO
import play.api.libs.json
import play.api.libs.json.{JsResult, JsSuccess, JsValue, Json}
import views.html.main


/**
 * This controller creates an `Action` to handle HTTP requests to the
 * application's home page.
 */
@Singleton
class HomeController @Inject()(cc: ControllerComponents, af: AssetsFinder) (implicit assetsFinder: AssetsFinder)
  extends AbstractController(cc) {



  val itemlist = List(
    Item("Tom",20, "S", "BLUE"),
    Item("Tom",20, "M", "GREEN"),
    Item("Tom",20, "L","BLUE"),
    Item("Tom",20, "XL","BLUE")
  )



  /**
   * Create an Action to render an HTML page with a welcome message.
   * The configuration in the `routes` file means that this method
   * will be called when the application receives a `GET` request with
   * a path of `/`.
   */
  implicit val jsonwriterItem = Json.writes[Item]

  implicit val jsonreaderItem = Json.reads[Item]

  implicit val jsonwriterOrder = Json.writes[Order]


  def listItems2() = Action {
    Ok(views.html.Home.jsonTesting())
  }


  def createItemJson() = Action {
    val item: Item = Item("GGGGGG", 20, "XXXX", "XXXXX")
    val json = Json.toJson(item)
    Ok(json)
  }


  def getmainJs()= Action {
    Ok
  }

  def index = Action {
    Ok(views.html.index("Hello from default view"))
  }

  def welcome(name: String, lastName: String) = Action {
    Ok(views.html.Home.welcome(name,lastName))
  }


  def showOrderForm() = Action {
    Ok(views.html.orderManagment.orderFormDemo())
  }

  def items() = Action {
    val list = DBO.list
    Ok(views.html.itemindex(list))
  }

  def showListOfOrders = Action {
    Ok(views.html.orderManagment.listOrders())
  }

}
