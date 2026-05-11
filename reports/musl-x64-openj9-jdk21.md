---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-11 11:23:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 811 |
| Sample Rate | 13.52/sec |
| Health Score | 845% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 84-91 cores)</summary>

```
1778512698 91
1778512703 89
1778512708 89
1778512713 89
1778512718 84
1778512723 84
1778512728 84
1778512733 84
1778512738 84
1778512743 84
1778512748 84
1778512753 84
1778512758 84
1778512763 84
1778512768 86
1778512773 86
1778512778 86
1778512783 86
1778512788 86
1778512793 86
```
</details>

---

