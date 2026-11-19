---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:47:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 55-63 cores)</summary>

```
1795099256 63
1795099261 63
1795099266 63
1795099271 63
1795099276 63
1795099281 63
1795099286 63
1795099291 63
1795099296 63
1795099301 63
1795099306 61
1795099311 61
1795099316 61
1795099321 61
1795099326 61
1795099331 61
1795099336 61
1795099341 61
1795099346 61
1795099351 61
```
</details>

---

