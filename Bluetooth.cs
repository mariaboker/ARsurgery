using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class Bluetooth : MonoBehaviour {

    SerialPort serial;

	// Use this for initialization
	void Start () {

         serial = new SerialPort("COM6", 9600);
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}



public class Rotator : MonoBehaviour
{

    SerialPort serial = new SerialPort("COM6", 9600);
    void Update()
    {

        if (!serial.IsOpen)
            serial.Open();

        int rotation = int.Parse(serial.ReadLine());
        transform.localEulerAngles = new Vector3(0, rotation, 0);




    }
}

