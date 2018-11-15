package controllers

import javax.inject.{Inject, Singleton}
import models.Item
import play.api.libs.json.Json
import play.api.mvc.{AbstractController, ControllerComponents}

@Singleton
class APIController @Inject() (cc: ControllerComponents, af: AssetsFinder) (implicit assetsFinder: AssetsFinder)
  extends AbstractController(cc)  {

  //handling Jsons of

  implicit val jsonwriter = Json.writes[Item]

  implicit val jsonreader = Json.reads[Item]

  // APIs

  def getListOfAllItems() = {
    TODO
  }

  def getListOfItems(orderId: Int) = {
    TODO
  }

  def getListOfAllOrders() = {
    TODO
  }

  def postListOfItems() = {
    TODO
  }

  //TODO
  //Api's form stock managment

  def getStockInfo() = {
    TODO
  }

  def upateStockInfo() = {
    TODO
  }

}
