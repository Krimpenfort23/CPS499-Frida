from __future__ import print_function
import frida
import sys

session = frida.attach("ShoppingCart")
script = session.create_script("""
send('Preping for Attachment...');
var price = 0;
var incoming_balance = 0;
Interceptor.attach(Module.getExportByName(null, 'getPrice'), 
{
    onLeave: function(retval) {
        send('Inspecting Purchase...');
        console.log("price of item was $" + retval.toInt32());
        price = retval.toInt32();
    }
});

Interceptor.attach(Module.getExportByName(null, 'setBalance'), 
{
    onEnter: function(args) 
    {
        send('Inspecting Balance...');
        console.log("balance is $" + args[1].toInt32());
        incoming_balance = args[1].toInt32();
        if (incoming_balance < 0)
        {
            send('Invalid Purchase! Fixing Balance...');
            console.log("adding $" + price + " back to the balance"); 
            var new_balance = incoming_balance + price;
            args[1] = ptr(new_balance);
        }
    }
});
""")

# Here's some message handling..
# [ It's a little bit more meaningful to read as output :-D
#   Errors get [!] and messages get [i] prefixes. ]
def on_message(message, data):
    if message['type'] == 'error':
        print("[!] " + message['stack'])
    elif message['type'] == 'send':
        print("[i] " + message['payload'])
    else:
        print(message)
script.on('message', on_message)
script.load()
sys.stdin.read()