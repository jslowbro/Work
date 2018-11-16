var app = angular.module('OrderFormApp', []);

app.controller('mainCtrl', function($scope, $http) {


    //initializing all the data, might switch to pulling it from DB later
    $scope.colors = ["RED", "BLUE", "GREEN"];
    $scope.colorValue = "RED";
    $scope.sizeList = ["S", "M", "L", "XL"];
    $scope.sizeValue = "S";
    $scope.master = {name: "", age: ""};
    $scope.itemlist = [];

    $scope.testData = function () {
        console.log($scope.colorValue);
        console.log($scope.sizeValue);
        console.log($scope.user.name);
        console.log($scope.user.age);
    };

    $scope.addItem = function() {
        //pushing item on the list
        var item = {name: angular.copy($scope.user.name),
                    age: angular.copy($scope.user.age),
                    size: angular.copy($scope.sizeValue),
                    color: angular.copy($scope.colorValue)};

        $scope.itemlist.push(item);
        //clearing form
        $scope.user = angular.copy($scope.master);
    };



    $scope.sendData = function () {
        //setting up the request
        var req = {
            method: 'POST',
            url: 'http://localhost:9000/postitems',
            headers: {
                'Content-Type': 'application/json'
            },
            data: JSON.stringify($scope.itemlist)
        };
        //actual request
        $http(req).then(function(){
            console.log("Successful POST Request")
        }, function(){
            console.log("Failed POST Request")

        });
        //clear items since they have been sent
        $scope.itemlist = [];
    };



});
