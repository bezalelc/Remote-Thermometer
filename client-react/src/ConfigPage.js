import ConfigField from './ConfigField';
import './style/ConfigPage.css'

const ConfigPage = () => {
    const configMap = {
        wifi: {
            name: {
                id: '0',
                message: 'Update your home WiFi name',
                placeholder: 'name',
                inputType: 'text',
                note: ''
            },
            password: {
                id: '1',
                message: 'Update your home WiFi password',
                placeholder: 'password',
                inputType: 'password',
                note: ''
            }
        },
        ap: {
            name: {
                id: '2',
                message: 'Set the WiFi access point name of the Termometer',
                placeholder: 'WiFi name',
                inputType: 'text',
                note: ''
            },
            password: {
                id: '3',
                message: 'Set the WiFi access point password of the Termometer',
                placeholder: 'password',
                inputType: 'password',
                note: ''
            }
        },
        user: {
            name: {
                id: '4',
                message: 'Update your email',
                placeholder: 'email',
                inputType: 'email',
                note: ''
            },
            password: {
                id: '5',
                message: 'Update your password account',
                placeholder: 'password',
                inputType: 'password',
                note: ''
            }
        }
    }


    const postData = (dataTypeId, data) => {
        const url = `http://192.168.4.1:80/config?${dataTypeId}=${data}`;
        fetch(url, {
            method: 'GET',
            // body: dataTypeId + data,
        })
            .then(res => {
                if (res.ok) {

                } else {

                }
                console.log("res\n", res)
            })
            .catch(error => console.log("error\n", error))

    };



    return (
        <div className="config-container">
            <div className="config-title">Thermometer configuration</div>
            <div className="config-instruction">
                <b>instruction:{' '}</b>
                <p>- Torn on configuration mode in the thermometer</p>
                <p>- Search for the thermometer's hotspot in your device and connect</p>
                <p>- Update one of those fields and click Update</p>
            </div>
            <div className='config-fields'>
                <ConfigField type='wifi' mapValues={configMap.wifi} postData={postData} />
                <ConfigField type='ap' mapValues={configMap.ap} postData={postData} />
                <ConfigField type='user' mapValues={configMap.user} postData={postData} />
            </div>
        </div>
    );
}

export default ConfigPage;