var app = new function() {
    this.el = document.getElementById('items');
    this.items = [];
    this.Count = function(data) {
        var el   = document.getElementById('counter');
        var name = 'item';
        if (data) {
            if (data > 1) {
                name = 'items';
            }
            el.innerHTML = data + ' ' + name ;
        } else {
            el.innerHTML = 'No ' + name;
        }
    };

    this.FetchAll = function() {
        var data = '';
        if (this.items.length > 0) {
            for (i = 0; i < this.items.length; i++) {
                data += '<tr>';
                data += '<td>' + this.items[i].name + '</td>';
                data += '<td>' + this.items[i].age + '</td>';
                data += '<td>' + this.items[i].color + '</td>';
                data += '<td>' + this.items[i].size + '</td>';
                data += '<td><button onclick="app.Delete(' + i + ')">Delete</button></td>';
                data += '</tr>';
            }
        }
        this.Count(this.items.length);
        return this.el.innerHTML = data;
    };
    this.Add = function () {
        el1 = document.getElementById('add-name');
        el2  = document.getElementById('add-age');
        el3 = document.getElementById('add-color');
        el4 = document.querySelector('input[name="size"]:checked');
        // Get the value
        var order = {
            name: el1.value.toString().toUpperCase(),
            age: el2.value,
            color: el3.value.toString().toUpperCase(),
            size: el4.value.toString().toUpperCase()

        };
        if (order.name && order.age) {
            // Add the new value
            this.items.push(order);
            // Reset input value
            el1.value = '';
            el2.value = '';
            // Dislay the new list
            this.FetchAll();
        }
    };

    this.Delete = function (item) {
        // Delete the current row
        this.items.splice(item, 1);
        // Display the new list
        this.FetchAll();
    };
    this.Clear = function () {
        for (i = 0; i < this.items.length; i++) {
            var a1 = this.items[i].name;
            var a2 = this.items[i].age;
            var a3 = this.items[i].color;
            var a4 = this.items[i].size;
        }
        //var a = this.items[0].size;
        //this.items[0].name = a;
        //this.items = [];
        this.items =[];
        this.FetchAll();
    }

};
app.FetchAll();
function CloseInput() {
    document.getElementById('spoiler').style.display = 'none';
}