import { useState } from "react";
import { useFirebase } from "./FirebaseContext";
import { ref, set } from "firebase/database";
import ProbSummery from './ProbSummery'
import ProbSettingMode from './ProbSettingMode'
import './style/ProbsList.css';


const ProbsList = ({ probsData }) => {
    const [itemIdFocus, setItemIdFocus] = useState(null)

    return (
        <div className="probs-data-container">
            {Object.keys(probsData).map(probKey => (
                <div key={probKey} className="prob-data-container" >
                    <ProbSummery probData={probsData[probKey]} probKey={probKey} itemIdFocus={itemIdFocus} setItemIdFocus={setItemIdFocus} />
                    {itemIdFocus === probKey && <ProbSettingMode probData={probsData[probKey]} probKey={probKey} />}
                </div>
            ))}
        </div >
    );
}

export default ProbsList;