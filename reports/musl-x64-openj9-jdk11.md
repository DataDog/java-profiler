---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 05:01:35 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (2 unique values: 54-57 cores)</summary>

```
1795168573 57
1795168578 57
1795168583 57
1795168588 57
1795168593 54
1795168598 54
1795168603 54
1795168608 54
1795168613 54
1795168619 54
1795168624 54
1795168629 54
1795168634 54
1795168639 54
1795168644 54
1795168649 54
1795168654 54
1795168659 54
1795168664 54
1795168669 54
```
</details>

---

