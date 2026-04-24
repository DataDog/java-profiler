---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-24 08:31:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 12-64 cores)</summary>

```
1777033596 12
1777033601 48
1777033606 48
1777033611 48
1777033616 48
1777033621 48
1777033626 48
1777033631 48
1777033636 48
1777033641 48
1777033646 48
1777033651 48
1777033656 58
1777033661 58
1777033666 58
1777033671 58
1777033676 58
1777033681 58
1777033686 58
1777033691 58
```
</details>

---

