var app = angular.module('ShowOrdersApp', []);


app.controller('mainCtrl', function($scope, $http) {

    console.log("Hello world");

    $scope.orderlist = [];


    $scope.getOrders = function () {
        var req = {
            method: 'GET',
            url: 'http://localhost:9000/getListOfOrders',
            headers: {
                'Content-Type': 'application/json'
            }

        };
        $http(req).then(function(response){
            console.log("Successful GET Request");
            console.log(response.data);
            $scope.orderlist = response.data
        }, function(){
            console.log("Failed GET Request")
        });
    };

    $scope.getOrders();













});
