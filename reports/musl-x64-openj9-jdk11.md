---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-11 05:23:34 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (6 unique values: 45-74 cores)</summary>

```
1773220576 70
1773220581 74
1773220586 74
1773220591 48
1773220596 48
1773220601 50
1773220606 50
1773220611 50
1773220616 50
1773220621 50
1773220626 50
1773220631 50
1773220636 50
1773220641 45
1773220646 45
1773220651 45
1773220656 45
1773220661 45
1773220666 45
1773220671 45
```
</details>

---

