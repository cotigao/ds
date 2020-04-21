function list() {
    this.head = null
    this.tail = null
}


list.prototype.add = function(val) {
    function Node() {
        this.value = val
        this.next = null
    }

    if(!this.head) {
        this.tail = this.head = new Node();
    } else {
        this.tail.next = new Node()
        this.tail = this.tail.next
    }
}


list.prototype.print = function() {
    for (let cur = this.head; cur; cur = cur.next) {
        console.log (cur.value)
    }
}

list.prototype.reverse = function() {
    function reverse(node, prev) {
        if(!node) {
            return null
        } else  {
            reverse(node.next, node)
        }

        node.next = prev
    }

    reverse(this.head, null)
    let tmp = this.head
    this.head = this.tail
    this.tail = tmp
}


var l = new list();

l.add(1)
l.add(2)
l.add(3)
l.add(4)
l.add(5)
l.print()

l.reverse()
l.print()


