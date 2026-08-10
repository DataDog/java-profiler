---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 09:32:23 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 860 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1786368442 37
1786368447 37
1786368452 37
1786368457 37
1786368462 43
1786368467 43
1786368472 43
1786368477 43
1786368482 43
1786368487 43
1786368492 43
1786368497 43
1786368502 43
1786368507 43
1786368512 43
1786368517 43
1786368522 43
1786368527 48
1786368532 48
1786368537 48
```
</details>

---

