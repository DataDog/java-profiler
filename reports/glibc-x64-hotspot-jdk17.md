---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:05:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 994 |
| Sample Rate | 16.57/sec |
| Health Score | 1036% |
| Threads | 11 |
| Allocations | 412 |

<details>
<summary>CPU Timeline (4 unique values: 62-71 cores)</summary>

```
1795449467 68
1795449472 68
1795449477 68
1795449482 68
1795449487 70
1795449492 70
1795449497 70
1795449502 62
1795449507 62
1795449512 62
1795449517 62
1795449522 62
1795449527 62
1795449532 62
1795449537 62
1795449542 62
1795449547 62
1795449552 71
1795449557 71
1795449562 71
```
</details>

---

