using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShrineDontDestroy : MonoBehaviour
{
    public bool collected = false;
    private void Start()
    {
        DontDestroyOnLoad(this);
    }
    
}
