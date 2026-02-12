---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-12 13:12:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 21-32 cores)</summary>

```
1770919593 32
1770919598 32
1770919603 32
1770919608 32
1770919613 32
1770919618 32
1770919623 32
1770919628 27
1770919633 27
1770919638 27
1770919643 27
1770919648 27
1770919653 27
1770919658 27
1770919663 27
1770919668 27
1770919673 27
1770919678 25
1770919683 25
1770919688 25
```
</details>

---

