---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:15:25 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (5 unique values: 68-82 cores)</summary>

```
1795108263 76
1795108268 76
1795108273 76
1795108278 76
1795108283 76
1795108288 76
1795108293 76
1795108298 76
1795108303 76
1795108308 76
1795108313 76
1795108318 76
1795108323 76
1795108328 76
1795108333 79
1795108338 79
1795108343 82
1795108348 82
1795108353 82
1795108358 82
```
</details>

---

