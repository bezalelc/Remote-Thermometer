import './style/ProbComponent.css';
import { useFirebase } from "./FirebaseContext";
import TemperatureView from './TemperatureView';
import TimeView from './TimeView';

const ProbComponent = ({ probId }) => {
    const { data } = useFirebase()

    return (
        <div key={probId} className="prob-data-container">
            <div className='prob-component-title'>Prob {probId.match(/\d+/)[0]}</div>
            <TemperatureView probId={probId} probData={data[probId]} />
            <TimeView probId={probId} probData={data[probId]} />
        </div >
    );
}

export default ProbComponent;