---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:27:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 894 |
| Sample Rate | 14.90/sec |
| Health Score | 931% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 55-58 cores)</summary>

```
1795112609 58
1795112614 58
1795112619 58
1795112624 58
1795112629 55
1795112634 55
1795112639 55
1795112644 55
1795112649 55
1795112654 55
1795112659 55
1795112664 55
1795112669 55
1795112674 55
1795112679 55
1795112684 55
1795112689 55
1795112694 55
1795112699 55
1795112704 55
```
</details>

---

