---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 08:31:17 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 63-68 cores)</summary>

```
1795008276 65
1795008281 65
1795008286 65
1795008291 63
1795008296 63
1795008301 63
1795008306 63
1795008311 63
1795008316 63
1795008321 63
1795008326 63
1795008331 63
1795008336 63
1795008341 63
1795008346 63
1795008351 63
1795008356 68
1795008361 68
1795008366 68
1795008371 68
```
</details>

---

