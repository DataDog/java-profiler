---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-12 09:14:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1791810593 12
1791810598 12
1791810603 12
1791810608 12
1791810613 10
1791810618 10
1791810623 10
1791810628 10
1791810633 10
1791810638 10
1791810643 10
1791810648 10
1791810653 10
1791810658 10
1791810663 10
1791810668 10
1791810673 10
1791810678 10
1791810683 10
1791810688 10
```
</details>

---

