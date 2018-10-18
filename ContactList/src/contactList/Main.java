package contactList;

import dataModel.ContactStorage;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;


public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("../resources/gui/mainWindow.fxml"));
        primaryStage.setTitle("Contact List App");
        primaryStage.setScene(new Scene(root, 800, 600));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }


    @Override
    public void stop() throws Exception {
        if(ContactStorage.getInstance().getLoadtype().equals("XML")){
            ContactStorage.getInstance().saveContactsXML();
        } else if(ContactStorage.getInstance().getLoadtype().equals("Database")){
            ContactStorage.getInstance().saveContactsDB();
        }

    }


}
