---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 09:57:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 63-76 cores)</summary>

```
1795186291 63
1795186296 63
1795186301 63
1795186306 63
1795186311 67
1795186316 67
1795186321 67
1795186326 67
1795186331 67
1795186336 67
1795186341 67
1795186346 67
1795186351 67
1795186356 67
1795186361 67
1795186366 76
1795186371 76
1795186376 76
1795186381 76
1795186386 76
```
</details>

---

