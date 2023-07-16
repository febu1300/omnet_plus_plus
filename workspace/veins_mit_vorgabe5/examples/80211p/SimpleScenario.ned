import org.car2x.veins.nodes.Wifi;
import org.car2x.veins.base.connectionManager.ConnectionManager;
import org.car2x.veins.base.modules.BaseWorldUtility;
import org.car2x.veins.modules.world.annotations.AnnotationManager;
import org.car2x.veins.modules.obstacle.ObstacleControl;

network SimpleScenario
{
    parameters:
        double playgroundSizeX @unit(m); // x size of the area the nodes are in (in meters)
        double playgroundSizeY @unit(m); // y size of the area the nodes are in (in meters)
        double playgroundSizeZ @unit(m); // z size of the area the nodes are in (in meters)
        @display("bgb=991,671");
    submodules:
        obstacles: ObstacleControl {
            @display("p=603,487");
        }
        connectionManager: ConnectionManager {
            parameters:
                @display("p=737,65;i=abstract/multicast");
        }
        world: BaseWorldUtility {
            parameters:
                playgroundSizeX = playgroundSizeX;
                playgroundSizeY = playgroundSizeY;
                playgroundSizeZ = playgroundSizeZ;
                @display("p=383,97;i=misc/globe");
        }
        node[5]: Wifi {
            @display("p=336,272;b=10,10,oval");
        }
        annotations: AnnotationManager {
            @display("p=882,327");
        }
    connections allowunconnected:
}
