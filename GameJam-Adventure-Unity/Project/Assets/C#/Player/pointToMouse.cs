using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class pointToMouse : MonoBehaviour
{

    private PlayerController parentScript;

    private void Start()
    {
        parentScript = this.transform.parent.gameObject.GetComponent<PlayerController>();
    }
    void Update()
    {
        //rotation
        Vector3 mousePos = Input.mousePosition;
        mousePos.z = 5.23f;

        Vector3 objectPos = Camera.main.WorldToScreenPoint(transform.position);
        mousePos.x = mousePos.x - objectPos.x;
        mousePos.y = mousePos.y - objectPos.y;
        if (parentScript.dir == 0)
        {
            mousePos.y *= -1;
            mousePos.x *= -1;
        }
        float angle = Mathf.Atan2(mousePos.y, mousePos.x) * Mathf.Rad2Deg;
        transform.rotation = Quaternion.Euler(new Vector3(0, 0, angle));
    }
}
