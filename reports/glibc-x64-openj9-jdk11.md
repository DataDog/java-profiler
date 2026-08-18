---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 08:24:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1787055601 94
1787055606 94
1787055611 92
1787055616 92
1787055621 92
1787055626 92
1787055631 92
1787055636 92
1787055641 92
1787055646 92
1787055651 92
1787055656 92
1787055661 92
1787055666 92
1787055671 92
1787055676 92
1787055681 92
1787055686 92
1787055691 92
1787055696 92
```
</details>

---

