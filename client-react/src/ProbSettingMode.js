import { useState, useRef, useEffect } from "react";
import { ref, set } from "firebase/database";
import { useFirebase } from "./FirebaseContext";
import './style/ProbSettingMode.css'



const ProbSettingMode = ({ probData, probKey, itemIdFocus }) => {
    const { firebaseDB, userId } = useFirebase()

    // const [isInSettingMode, setIsInSettingMode] = useState(true)
    // const componentRef = useRef(null);

    // useEffect(() => {
    //     const isFocused = document.activeElement === componentRef.current;

    //     if (isFocused) {
    //         setIsInSettingMode(!isInSettingMode)
    //         console.log(`My component ${key} is focused.`);
    //     } else {
    //         setIsInSettingMode(false)
    //         console.log(`My component ${key} is not focused.`);
    //     }
    // }, []);

    const changeDestTemperatur = (mapKey, destTemperature_) => {
        const dbRefDestTemperature = ref(firebaseDB, `/UsersData/${userId}/${mapKey}/destTemperature`)
        set(dbRefDestTemperature, destTemperature_);
    }

    return (
        <div className="prob-setting-container">
            <div className="prob-setting-title">Prob setting</div>
            <div className="prob-setting" >
                <div className="prob-setting-set-temperature">
                    <span className="prob-setting-text">Dest temperature</span>
                    <div className="prob-setting-themperature-buttons">
                        <button onClick={() => { changeDestTemperatur(probKey, parseInt(probData.destTemperature) + 1) }}>+</button>
                        <span className="prob-setting-themperature-buttons-current">{probData.destTemperature}</span>
                        <button onClick={() => { changeDestTemperatur(probKey, parseInt(probData.destTemperature) - 1) }}>-</button>
                    </div>
                </div>
                <div className="prob-setting-set-temperature">
                    <span className="prob-setting-text">Set timer</span>
                    <div className="prob-setting-themperature-buttons">
                        <button onClick={() => { changeDestTemperatur(probKey, parseInt(probData.destTemperature) + 1) }}>+</button>
                        <span className="prob-setting-themperature-buttons-current">{probData.destTemperature}</span>
                        <button onClick={() => { changeDestTemperatur(probKey, parseInt(probData.destTemperature) - 1) }}>-</button>
                    </div>
                </div>
            </div>
        </div>
    );
}

export default ProbSettingMode;