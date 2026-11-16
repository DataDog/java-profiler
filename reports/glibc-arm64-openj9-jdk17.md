---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 12:06:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1794848477 64
1794848482 64
1794848487 64
1794848492 64
1794848497 64
1794848502 64
1794848507 64
1794848512 64
1794848517 64
1794848522 64
1794848527 59
1794848532 59
1794848537 59
1794848542 59
1794848547 59
1794848552 59
1794848557 59
1794848562 59
1794848567 59
1794848572 59
```
</details>

---

