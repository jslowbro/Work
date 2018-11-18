var app = angular.module('OrderFormApp', []);

app.controller('mainCtrl', function($scope, $http) {


    $scope.colors = ["RED", "BLUE", "GREEN"];
    $scope.colorValue = "RED";
    $scope.sizeList = ["S", "M", "L", "XL"];
    $scope.sizeValue = "S";
    $scope.master = {name: "", age: ""};

    $scope.itemlist = [];
    $scope.stock = [];



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

    $scope.getStock = function () {
        var req = {
            method: 'GET',
            url: 'http://localhost:9000/getStock',
            headers: {
                'Content-Type': 'application/json'
            }
        };
        $http(req).then(function(response){
            console.log("Successful GET Request");
            $scope.stock = response.data;
            console.log($scope.stock)
        }, function(){
            console.log("Failed GET Request")
        });
    };

    $scope.getStock();

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

    $scope.canSendData = function () {
        return $scope.itemlist.length === 0
    };

});
