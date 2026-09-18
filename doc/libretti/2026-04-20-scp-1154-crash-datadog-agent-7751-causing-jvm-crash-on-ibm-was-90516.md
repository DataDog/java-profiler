---
spec_id: REQ-SCP-1154
source: jira
source_ref: SCP-1154
title: "[Crash] Datadog Agent 7.75.1 causing JVM crash on IBM WAS 9.0.5.16 after installation"
status: implemented
clarity_score: null
created: 2026-04-20
implementing_session: impl-20260420-123402
implemented_pr: https://github.com/DataDog/java-profiler/pull/492
---

# [Crash] Datadog Agent 7.75.1 causing JVM crash on IBM WAS 9.0.5.16 after installation

## **Customer Issue Summary**

* **Environment**

    * Platform: IBM WebSphere Application Server (WAS)
    * WAS Version: 9.0.5.16
    * OS: RHEL 9.6
    * Java: OpenJDK 1.8.0_462
    * JVMs per server: 5
    * Agent versions involved:
    
        * Working: **7.75.1**
        * Failing (latest upgrade): **7.77.3**
        
    * Java Tracer version: **1.61.0**
    
* **Problem Description**

    * JVM crashes and restart failures occur across all WAS nodes
    * Issue started **after upgrading Datadog Agent**
    * No CPU or memory spikes observed
    * No application code changes
    * Removing Datadog Agent resolves the issue
    * Impact: **Release blocking (MyAMP application)**
    

## **Key Findings / Investigation (TL;DR)**

* Issue **reproduced and isolated**
* Root trigger identified as: `-Ddd.profiling.enabled=true`
* Behavior comparison:

    * OK : **Agent 7.75.1** → Profiling enabled → **Works fine**
    * KO: **Agent 7.77.3** → Profiling enabled → **JVM crash**
    * OK: **Agent 7.77.3** → Profiling disabled → **Stable**
    
* Additional validation:

    * Agent alone (no tracer/profiling) → stable
    * Confirms issue is **not core agent**, but likely:
    
        * Java tracer / profiler interaction
        * Profiler regression or incompatibility with WAS/JVM
        
    
* Scope:

    * All WAS nodes affected consistently
    * Reproducible on demand
    

## **Configuration Used**

* JVM arguments:

    * `-javaagent:/opt/datadog-agent/dd-java-agent.jar`
    * `-Ddd.service={}`
    * `-Ddd.version=9.0.5.16`
    * `-Ddd.logs.injection=true`
    * `-Ddd.profiling.enabled=true`
    * `-Ddd.env=`
    

## **Input Provided from the CX**

* Agent flare after reproduction :  
* Host where issue was reproduced:`i-06765a9af5f75256d` \[[partlow](https://support-admin.us1.prod.dog/admin/switch_handle_get/org_id/380139?next_url=%2Finfrastructure%3Fhost%3Di-06765a9af5f75256d%26tags%3Dapplicationname%253Aidam_tam_-_non-production&reason=zd-2818967)\] 
* Note:

    * Application was previously removed and not fully re-instrumented
    * Service visibility in APM currently limited
    
* **Not available:**

    * JVM crash dumps / hs_err logs
    * Full application logs at crash time
    

**Notes: this is very urgent as this is blocking their production release**

**(** <custom data-type="mention" data-id="id-0">@Reshmi Anand</custom> hey I’m tagging you here in case you took this one - it’s the case Agash saw with you in OH - thanks)
