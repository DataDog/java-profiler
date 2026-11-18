---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:10:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 65-74 cores)</summary>

```
1795010768 67
1795010773 67
1795010778 65
1795010783 65
1795010788 65
1795010793 65
1795010798 65
1795010803 74
1795010808 74
1795010813 74
1795010818 74
1795010823 67
1795010828 67
1795010833 67
1795010838 72
1795010843 72
1795010848 72
1795010853 72
1795010858 72
1795010863 72
```
</details>

---

