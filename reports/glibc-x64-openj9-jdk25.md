---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 17:19:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 8 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 6-32 cores)</summary>

```
1786137223 6
1786137228 6
1786137233 6
1786137238 6
1786137243 6
1786137248 6
1786137253 32
1786137258 32
1786137263 32
1786137268 32
1786137273 32
1786137278 32
1786137283 32
1786137288 32
1786137293 32
1786137298 32
1786137303 32
1786137308 32
1786137313 32
1786137318 32
```
</details>

---

