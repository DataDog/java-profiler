---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 05:39:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795170708 50
1795170713 50
1795170718 50
1795170723 50
1795170728 50
1795170733 50
1795170738 50
1795170743 50
1795170748 50
1795170753 50
1795170758 50
1795170763 50
1795170768 50
1795170773 50
1795170778 50
1795170783 50
1795170788 50
1795170793 50
1795170798 50
1795170803 50
```
</details>

---

