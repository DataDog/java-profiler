---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-24 08:33:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 76-77 cores)</summary>

```
1777033672 77
1777033677 77
1777033682 76
1777033687 76
1777033692 76
1777033697 76
1777033703 76
1777033708 76
1777033713 76
1777033718 76
1777033723 76
1777033728 76
1777033733 76
1777033738 76
1777033743 76
1777033748 76
1777033753 76
1777033758 76
1777033763 76
1777033768 76
```
</details>

---

