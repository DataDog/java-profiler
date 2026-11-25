---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:36:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 345 |
| Sample Rate | 5.75/sec |
| Health Score | 359% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 10 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 12-14 cores)</summary>

```
1795620723 14
1795620728 14
1795620733 14
1795620738 14
1795620743 14
1795620748 14
1795620753 14
1795620758 14
1795620763 14
1795620768 14
1795620773 14
1795620778 14
1795620783 14
1795620788 14
1795620793 14
1795620798 14
1795620803 14
1795620808 14
1795620813 14
1795620818 14
```
</details>

---

