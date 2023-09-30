import { ref, set } from "firebase/database";
import { useFirebase } from "./FirebaseContext";
import AlarmPlayer from "./AlarmPlayer";
import TimePicker from "react-time-picker";
import 'react-time-picker/dist/TimePicker.css';
import 'react-clock/dist/Clock.css';
import './style/TimeView.css'

const TimeView = ({ probId, probData }) => {
    const { firebaseDB, userId } = useFirebase()
    const dbRefDestTime = ref(firebaseDB, `/UsersData/${userId}/${probId}/destTime`)

    const convertMillisToTime = (startTime, currentTime) => {
        // console.log(probId, 'convertMillisToTime', startTime, currentTime,millisToTime(parseInt(currentTime) - parseInt(startTime)))
        return millisToTime(parseInt(currentTime) - parseInt(startTime))
    };

    const millisToTime = millis => {
        
        // console.log(probId, 'millisToTime', millis)
        if (millis !== null && millis !== undefined && millis !== 0) {
            const seconds = Math.floor(parseInt(millis) / 1000);
            const hours = Math.floor(seconds / 3600).toString().padStart(2, '0')
            const minutes = Math.floor((seconds % 3600) / 60).toString().padStart(2, '0')
            // const remainingSeconds = (seconds % 60).toString().padStart(2, '0')
            return `${hours}:${minutes}`;
        } else {
            return null;
        }
    }

    const handleTimeChange = (newTime) => {
        if (newTime !== null && newTime !== undefined) {
            const [hours, minutes] = newTime.split(':');
            const totalMilliseconds = parseInt(hours) * 60 * 60 * 1000 + parseInt(minutes) * 60 * 1000;
            set(dbRefDestTime, totalMilliseconds);
        } else {
            set(dbRefDestTime, 0);
        }
    }

    return (
        <div className="time-view">
            <div className="time-view-time">
                Time: {convertMillisToTime(probData.startTime, probData.currentTime)}
            </div>
            <div className="time-view-set-timer">
                <span className="time-view-set-text">Set time alert</span>
                <div className="time-view-picker">
                    <TimePicker
                        onChange={handleTimeChange}
                        value={millisToTime(probData.destTime)}
                        format="HH:mm" // Format to display the time
                        disableClock
                        className="time-view-time-picker"
                    />
                </div>
            </div>
            <AlarmPlayer probId={probId} currentVal={probData.currentTime} destVal={probData.destTime > 0 ? probData.destTime : Infinity} />
        </div>
    );
}

export default TimeView;