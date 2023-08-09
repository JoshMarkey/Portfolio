using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class MonsterMouseOver : MonoBehaviour
{
    bool fade = false;
    [SerializeField] Animator anim;
    private void OnMouseOver()
    {
        if (!fade)
        {
            anim.SetTrigger("Start");
            fade = true;
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.CompareTag("Player"))
        {
            if (!fade)
            {
                anim.SetTrigger("Start");
                fade = true;
            }
        }
    }

        IEnumerator co()
    {
        yield return new WaitForSeconds(0.01f);
        anim.ResetTrigger("Start");
    }
}
