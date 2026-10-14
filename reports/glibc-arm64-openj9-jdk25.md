---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 04:32:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 10 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 19-32 cores)</summary>

```
1791966462 32
1791966467 32
1791966472 32
1791966477 32
1791966482 32
1791966487 32
1791966492 32
1791966497 32
1791966502 32
1791966507 32
1791966512 32
1791966517 32
1791966522 32
1791966527 32
1791966532 32
1791966537 32
1791966542 32
1791966547 32
1791966552 32
1791966557 32
```
</details>

---

