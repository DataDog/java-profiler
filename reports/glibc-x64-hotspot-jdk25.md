---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:16:26 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 74-81 cores)</summary>

```
1795108278 74
1795108283 74
1795108288 74
1795108293 74
1795108298 74
1795108303 74
1795108308 74
1795108313 74
1795108318 74
1795108323 74
1795108328 74
1795108333 76
1795108338 76
1795108343 76
1795108348 76
1795108353 76
1795108358 76
1795108363 79
1795108368 79
1795108373 79
```
</details>

---

