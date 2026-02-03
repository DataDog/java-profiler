---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 08:20:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 68-85 cores)</summary>

```
1770124374 68
1770124379 68
1770124384 68
1770124389 68
1770124394 68
1770124399 68
1770124404 68
1770124409 68
1770124414 68
1770124419 68
1770124424 68
1770124429 68
1770124434 70
1770124439 70
1770124444 85
1770124449 85
1770124454 85
1770124459 85
1770124464 85
1770124469 85
```
</details>

---

