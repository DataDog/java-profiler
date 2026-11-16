---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 12:34:14 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 68-74 cores)</summary>

```
1794850189 68
1794850194 68
1794850199 68
1794850204 70
1794850209 70
1794850214 70
1794850219 70
1794850224 70
1794850229 72
1794850234 72
1794850239 72
1794850244 72
1794850249 70
1794850254 70
1794850259 72
1794850264 72
1794850269 72
1794850274 72
1794850279 72
1794850284 72
```
</details>

---

