---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 05:09:43 EST

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 857 |
| Sample Rate | 14.28/sec |
| Health Score | 892% |
| Threads | 11 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (3 unique values: 55-64 cores)</summary>

```
1795082626 57
1795082631 57
1795082636 57
1795082641 57
1795082646 57
1795082651 55
1795082656 55
1795082661 64
1795082666 64
1795082671 64
1795082676 64
1795082681 64
1795082686 64
1795082692 64
1795082697 64
1795082702 64
1795082707 64
1795082712 64
1795082717 64
1795082722 64
```
</details>

---

