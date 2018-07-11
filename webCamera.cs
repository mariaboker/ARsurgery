using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class webCamera : MonoBehaviour
{
    public GameObject webPlane;

    void Start()
    {
        WebCamDevice[] devices = WebCamTexture.devices;
        for (int i = 0; i < devices.Length; i++)
        {
            Debug.Log(i + " " + devices[i].name);
        }

        Renderer rend = this.GetComponentInChildren<Renderer>();

        WebCamTexture webcamTexture = new WebCamTexture(devices[1].name);//, Screen.width, Screen.height);
        webPlane.GetComponent<MeshRenderer>().material.mainTexture = webcamTexture;

        // rend.material.mainTexture = webcamTexture; if you dont wanna use a plane, try this

        webcamTexture.Play();
    }

    //public RawImage background;

    //private void Start()
    //{
    //    WebCamDevice[] devices = WebCamTexture.devices;

    //    Renderer rend = this.GetComponentInChildren<Renderer>();

    //    WebCamTexture webCamRaw = new WebCamTexture(devices[0].name, Screen.width, Screen.height);
    //    background.GetComponent<MeshRenderer>().material.mainTexture = webCamRaw;

    //    webCamRaw.Play();
    //}

}
