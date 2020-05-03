//enum: Node can be Present or Absent
//For Node::Present, note how I can associate it with  data
enum Node {
    Present {
        left: Box<Node>,
        value: i32,
        right: Box<Node>,
    },
    Absent,
}

const STEP: usize = 5;

fn insert(node: &mut Node, val: i32) {
    //Pattern matching
    match node {
        //Deconstructing the mutable reference.
        //Here *node gets reborrowed, because it's fields are borrowed
        Node::Present {
            left,      //is &mut Box<Node>,
            ref value, //using immutable ref to avoid mutation
            right,     //is &mut Box<Node>
        } => {
            // recursively call the insert()
            if *value > val {
                insert(left, val);
            } else {
                insert(right, val);
            }
        }

        Node::Absent => {
            //Node::Absent, replace it with Node::Present
            //*node mutation is possible due to NLL
            *node = Node::Present {
                left: Box::new(Node::Absent),
                value: val,
                right: Box::new(Node::Absent),
            }
        }
    }
}

fn print(node: &Node, spaces: usize) {
    match node {
        Node::Present { left, value, right } => {
            print(right, spaces + STEP);
            println!("{}{}", " ".repeat(spaces), value);
            print(left, spaces + STEP);
        }
        _ => (),
    }
}

fn main() {
    // Initialize with Boxed (allocated on heap) Node as Absent
    let mut root = Box::new(Node::Absent);

    // Passing &mut Box<Node>. Although the insert() accepts &mut Node,
    // it works, because Box implements the Deref/DerefMut Trait i.e &Box<T>
    // can be used as &T (Note: Box remains borrowed for as long T remains borrowed)
    insert(&mut root, 18);

    insert(&mut root, 16);
    insert(&mut root, 14);
    insert(&mut root, 17);
    insert(&mut root, 13);
    insert(&mut root, 15);

    insert(&mut root, 19);
    insert(&mut root, 26);
    insert(&mut root, 22);
    insert(&mut root, 24);
    insert(&mut root, 28);

    print(&root, 0);
}
