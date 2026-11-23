---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 08:37:35 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 46-74 cores)</summary>

```
1795440748 74
1795440753 74
1795440758 46
1795440763 46
1795440768 46
1795440773 46
1795440778 46
1795440783 46
1795440788 46
1795440793 46
1795440798 46
1795440803 46
1795440808 46
1795440813 46
1795440819 46
1795440824 46
1795440829 46
1795440834 46
1795440839 46
1795440844 48
```
</details>

---

