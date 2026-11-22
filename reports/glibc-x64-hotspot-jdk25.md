---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 05:47:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 360 |
| Sample Rate | 6.00/sec |
| Health Score | 375% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795344230 28
1795344235 28
1795344240 28
1795344245 28
1795344250 28
1795344255 28
1795344260 28
1795344265 28
1795344270 28
1795344275 33
1795344280 33
1795344285 33
1795344290 33
1795344295 33
1795344300 33
1795344305 33
1795344310 33
1795344315 33
1795344320 33
1795344325 33
```
</details>

---

