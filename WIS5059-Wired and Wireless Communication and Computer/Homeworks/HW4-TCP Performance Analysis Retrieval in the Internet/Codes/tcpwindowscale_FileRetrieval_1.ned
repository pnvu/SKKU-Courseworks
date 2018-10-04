//
// author: Phan Nguyen Vu
// date: 6th June 2018
//

package inet.examples.inet.tcpwindowscale;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;
import ned.IdealChannel;


network tcpwindowscale_FileRetrieval_1
{
    parameters:
        @display("bgb=543,217");
    types:
    submodules:
        client: StandardHost {
            parameters:
                @display("p=50,100");
            gates:
                ethg[1];
        }
        server: StandardHost {
            parameters:
                @display("p=477,100;i=device/server");
            gates:
                ethg[1];                
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=42,24");
        }
        router1: Router {
            parameters:
                @display("p=173,100");
            gates:
                ethg[2];
        }
        router2: Router {
            parameters:
                @display("p=333,100");
            gates:
                ethg[2];
        }
    connections:
        client.ethg++ <--> FR_LocalPath_1 <--> router1.ethg++;
        router2.ethg++ <--> FR_LocalPath_1 <--> server.ethg++;
        router1.ethg++ <--> FR_InternetPath_1 <--> router2.ethg++;
}

channel FR_InternetPath_1 extends DatarateChannel
{
    parameters:
        datarate = 1Gbps;
        delay = 30ms;
        per = 0.02;
        ber = 0;
}

channel FR_LocalPath_1 extends DatarateChannel
{
    parameters:
        datarate = 1Gbps;
        delay = 0ms;
        per = 0;
        ber = 0;
}
