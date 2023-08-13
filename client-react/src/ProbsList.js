import { useState } from "react";
import { useFirebase } from "./FirebaseContext";
import { ref, set } from "firebase/database";

const ProbsList = ({ probsData }) => {
    const { firebaseDB, userId } = useFirebase()
    const [itemIdFocus, setItemIdFocus] = useState(null)

    const convertMillisToTime = (startTime, currentTime) => {
        const seconds = Math.floor((parseInt(currentTime) - parseInt(startTime)) / 1000);
        if (!seconds) {
            return '0'
        }
        const hours = Math.floor(seconds / 3600).toString().padStart(2, '0')
        const minutes = Math.floor((seconds % 3600) / 60).toString().padStart(2, '0')
        const remainingSeconds = (seconds % 60).toString().padStart(2, '0')



        return `${hours !== '00' ? hours + ':' : ''}${minutes !== '00' ? minutes + ':' : ''}${remainingSeconds}`;
    };

    const changeDestTemperatur = (key, destTemperature_) => {
        const dbRefDestTemperature = ref(firebaseDB, `/UsersData/${userId}/${key}/destTemperature`)
        set(dbRefDestTemperature, destTemperature_);
    }

    const handleItemFocus = key => {
        console.log(key)
        setItemIdFocus(key === itemIdFocus ? null : key)
    }

    return (
        <div className="probs-data-container">
            {Object.keys(probsData).map(key => (
                <div key={key} className="prob-data-container" onFocus={() => console.log("focus1")}>
                    <div className="prob-data-summery" onFocus={() => console.log("focus2")}>
                        <div className="prob-list-title" onClick={key => handleItemFocus(key)}>Prob {key.match(/\d+/)[0]}</div>
                        <div className="prob-data-deg-container" onFocus={() => console.log("focus3")}>
                            <div className="home-temperature-container">
                                <span className="temperature">{parseFloat(probsData[key].temperature).toFixed(1)}</span>
                                <span className="temperature-sing">&deg;</span>
                                <span className="home-temperature-c">C</span>
                            </div>
                            <div className="home-dest-temperature-container">
                                <span className="temperature-separetor">/&nbsp;</span>
                                <span className="dest-temperature">{parseInt(probsData[key].destTemperature)}</span>
                                <span className="temperature-sing">&deg;</span>
                                <span className="home-dest-temperature-c">C</span>
                            </div>
                        </div>
                        <div className="prob-data-time-container">
                            {convertMillisToTime(probsData[key]["startTime"], probsData[key]["currentTime"])}
                        </div>
                    </div>
                    {itemIdFocus === key && < div className="prob-data-setting" >
                        <div className="prob-list-set-temperature-buttons">
                            <button onClick={() => { changeDestTemperatur(key, parseInt(probsData[key].destTemperature) + 1) }}>+</button>
                            <button onClick={() => { changeDestTemperatur(key, parseInt(probsData[key].destTemperature) - 1) }}>-</button>
                        </div>
                    </div>}
                </div>
            ))
            }
        </div >
    );
}

export default ProbsList;