---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:16:26 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1795108272 56
1795108277 56
1795108282 56
1795108287 56
1795108292 56
1795108297 56
1795108302 56
1795108307 56
1795108312 56
1795108317 56
1795108322 54
1795108328 54
1795108333 54
1795108338 54
1795108343 54
1795108348 56
1795108353 56
1795108358 64
1795108363 64
1795108368 64
```
</details>

---

