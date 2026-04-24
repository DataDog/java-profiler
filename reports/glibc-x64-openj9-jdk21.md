---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-24 08:33:44 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 18-19 cores)</summary>

```
1777033637 18
1777033642 18
1777033647 18
1777033652 18
1777033657 18
1777033662 18
1777033667 18
1777033672 19
1777033677 19
1777033682 19
1777033687 19
1777033692 19
1777033697 19
1777033702 19
1777033707 19
1777033712 19
1777033717 19
1777033722 19
1777033727 19
1777033732 19
```
</details>

---

