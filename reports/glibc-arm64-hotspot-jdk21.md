---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-14 08:53:55 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1786711728 46
1786711733 46
1786711738 46
1786711743 46
1786711748 46
1786711753 46
1786711758 46
1786711763 46
1786711768 46
1786711773 48
1786711778 48
1786711783 48
1786711788 48
1786711793 48
1786711798 48
1786711803 48
1786711808 48
1786711813 48
1786711818 48
1786711823 48
```
</details>

---

