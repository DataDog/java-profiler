---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-23 11:05:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 62-75 cores)</summary>

```
1795449462 75
1795449467 75
1795449472 75
1795449477 75
1795449482 75
1795449487 75
1795449492 75
1795449497 67
1795449502 67
1795449507 67
1795449512 62
1795449517 62
1795449522 62
1795449527 62
1795449532 67
1795449537 67
1795449542 67
1795449547 67
1795449552 67
1795449557 67
```
</details>

---

