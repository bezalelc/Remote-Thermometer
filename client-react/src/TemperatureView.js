import { ref, set } from "firebase/database";
import { useFirebase } from "./FirebaseContext";
import AlarmPlayer from "./AlarmPlayer";
import './style/TemperatureView.css'

const Temperature = ({ probId, probData }) => {
    const { firebaseDB, userId } = useFirebase()
    const dbRefDestTemperature = ref(firebaseDB, `/UsersData/${userId}/${probId}/destTemperature`)

    const changeDestTemperatur = destTemperature_ => {
        set(dbRefDestTemperature, destTemperature_);
    }

    return (
        <div className="temperature-view" >
            <div className="temperature-view-container" >
                <span className="temperature-view-temperature">Temperatur: {parseFloat(probData.temperature).toFixed(2)}</span>
                <span className="temperature-view-deg-sing">&deg;</span>
                <span className="temperature-view-c-sing">C</span>
            </div>
            <div className="temperature-view-set-temperature">
                <span className="temperature-view-dest">Dest temperature:</span>
                <div className="temperature-view-dest-buttons">
                    <button onClick={() => changeDestTemperatur(parseInt(probData.destTemperature) + 1)}>+</button>
                    <span className="temperature-view-dest-current">{probData.destTemperature}</span>
                    <button onClick={() => changeDestTemperatur(parseInt(probData.destTemperature) - 1)}>-</button>
                </div>
            </div>
            <AlarmPlayer probId={probId} currentVal={probData.temperature} destVal={probData.destTemperature} />
        </div>
    );
}

export default Temperature;