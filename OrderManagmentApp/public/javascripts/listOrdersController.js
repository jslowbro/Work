var app = angular.module('ShowOrdersApp', []);


app.controller('mainCtrl', function($scope, $http) {

    console.log("Hello world");

    $scope.orderlist = [];


    $scope.getOrders = function () {
        //prep the request
        var req = {
            method: 'GET',
            url: 'http://localhost:9000/getListOfOrders',
            headers: {
                'Content-Type': 'application/json'
            }

        };
        //send request
        $http(req).then(function(response){
            console.log("Successful GET Request");
            console.log(response.data);
            $scope.orderlist = response.data
        }, function(){
            console.log("Failed GET Request")
        });
    };


    $scope.getOrderDetails = function (id) {
        console.log("You want to see the detals of order No." + id);
        var req = {
            method: 'GET',
            url: 'http://localhost:9000/getListOfItems/' + id ,
            headers: {
                'Content-Type': 'application/json'
            }

        };
        $http(req).then(function(response){
            console.log("Successful GET Request");
            console.log(response.data);
        }, function(){
            console.log("Failed GET Request")
        });
    };




});
