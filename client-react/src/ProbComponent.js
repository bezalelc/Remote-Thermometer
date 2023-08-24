// import ProbSummery from './ProbSummery'
// import ProbSettingMode from './ProbSettingMode'
import './style/ProbComponent.css';
import { useFirebase } from "./FirebaseContext";
import TemperatureView from './TemperatureView';
import TimeView from './TimeView';

const ProbComponent = ({ probId, itemIdFocus, setItemIdFocus }) => {
    const { data } = useFirebase()

    return (
        <div key={probId} className="prob-data-container">
            <div className='prob-component-title'>Prob {probId.match(/\d+/)[0]}</div>
            <TemperatureView probId={probId} probData={data[probId]} />
            <TimeView probId={probId} probData={data[probId]} />
            {/* <ProbSummery probData={data[probId]} probId={probId} itemIdFocus={itemIdFocus} setItemIdFocus={setItemIdFocus} />
            <ProbSettingMode probData={data[probId]} probId={probId} /> */}
        </div >
    );
}

export default ProbComponent;