---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 09:56:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (4 unique values: 15-22 cores)</summary>

```
1793890277 22
1793890282 22
1793890287 22
1793890292 22
1793890297 22
1793890302 22
1793890307 22
1793890312 22
1793890317 22
1793890322 22
1793890327 22
1793890332 22
1793890337 22
1793890342 22
1793890347 22
1793890352 17
1793890357 17
1793890362 17
1793890367 17
1793890372 17
```
</details>

---

