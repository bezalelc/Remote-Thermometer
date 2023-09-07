import { useState } from "react";
import './style/ConfigField.css'

const ConfigField = ({ type, mapValues, postData }) => {
    const [name, setName] = useState('')
    const [password, setPassword] = useState('')

    return (
        <div key={`config-field-${type}`} className="config-filed-container">
            <form key={`config-field-${type}-name`} className="config-field config-field-name" onSubmit={(e) => e.preventDefault()}>
                <label className='config-field-input'>{mapValues.name.message}</label>
                <input type={mapValues.name.inputType} placeholder={mapValues.name.placeholder} onChange={event => setName(event.target.value)} required />
                {/* <button onClick={() => postData(mapValues.name.id, name)}>Update</button> */}
                <a href={`http://192.168.4.1:80/config?${encodeURIComponent(mapValues?.name?.id)}=${encodeURIComponent(name)}`} target="_blank" rel="noopener noreferrer" className='config-field-link'>
                    Update
                </a>
            </form>
            <form key={`config-field-${type}-password`} className="config-field config-field-password" onSubmit={(e) => e.preventDefault()} required>
                <label>{mapValues.password.message}</label>
                <input className='config-field-password-input' placeholder="password" onChange={event => setPassword(event.target.value)} />
                {/* <button onClick={() => postData(mapValues.password.id, password)}>Update</button> */}
                <a href={`http://192.168.4.1:80/config?${encodeURIComponent(mapValues?.password?.id)}=${encodeURIComponent(password)}`} target="_blank" rel="noopener noreferrer" className='config-field-link'>
                    Update
                </a>
            </form>
        </div>
    );
}

export default ConfigField;