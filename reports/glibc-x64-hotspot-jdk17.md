---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:30:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (6 unique values: 50-81 cores)</summary>

```
1795112639 52
1795112644 52
1795112649 68
1795112654 68
1795112659 68
1795112664 68
1795112669 68
1795112674 76
1795112679 76
1795112684 76
1795112689 76
1795112694 76
1795112699 76
1795112704 76
1795112709 76
1795112714 81
1795112719 81
1795112724 81
1795112729 81
1795112734 81
```
</details>

---

