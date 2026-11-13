---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 07:45:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (5 unique values: 60-69 cores)</summary>

```
1794573576 64
1794573581 64
1794573586 64
1794573591 64
1794573596 64
1794573601 64
1794573606 64
1794573611 60
1794573616 60
1794573621 60
1794573626 60
1794573631 62
1794573636 62
1794573641 62
1794573646 62
1794573651 62
1794573656 62
1794573661 62
1794573666 62
1794573671 67
```
</details>

---

