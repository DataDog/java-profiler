---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-11 01:02:44 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 61-81 cores)</summary>

```
1791694718 61
1791694723 61
1791694728 61
1791694733 61
1791694738 61
1791694743 61
1791694748 61
1791694753 61
1791694758 61
1791694763 61
1791694768 61
1791694773 61
1791694778 61
1791694783 61
1791694788 61
1791694793 61
1791694798 61
1791694803 61
1791694808 61
1791694813 81
```
</details>

---

