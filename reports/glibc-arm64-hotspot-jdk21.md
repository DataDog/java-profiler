---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-11 01:02:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1791694713 18
1791694718 18
1791694723 18
1791694728 18
1791694733 18
1791694738 18
1791694743 18
1791694748 18
1791694753 18
1791694758 18
1791694763 18
1791694768 18
1791694773 18
1791694778 18
1791694783 18
1791694789 18
1791694794 18
1791694799 18
1791694804 18
1791694809 13
```
</details>

---

