---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:16:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 895 |
| Sample Rate | 14.92/sec |
| Health Score | 932% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 72-78 cores)</summary>

```
1795108263 72
1795108268 74
1795108273 74
1795108278 74
1795108283 74
1795108288 74
1795108293 74
1795108298 76
1795108303 76
1795108308 76
1795108313 76
1795108318 76
1795108323 76
1795108328 76
1795108333 76
1795108338 76
1795108343 76
1795108348 76
1795108353 76
1795108358 76
```
</details>

---

