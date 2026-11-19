---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:27:33 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 869 |
| Sample Rate | 14.48/sec |
| Health Score | 905% |
| Threads | 11 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (2 unique values: 50-60 cores)</summary>

```
1795112602 60
1795112608 60
1795112613 60
1795112618 60
1795112623 60
1795112628 60
1795112633 60
1795112638 60
1795112643 60
1795112648 60
1795112653 60
1795112658 60
1795112663 60
1795112668 60
1795112673 60
1795112678 60
1795112683 60
1795112688 60
1795112693 60
1795112698 60
```
</details>

---

