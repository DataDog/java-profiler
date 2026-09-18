---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 03:37:49 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1789716685 94
1789716690 94
1789716695 96
1789716700 96
1789716705 96
1789716710 96
1789716715 96
1789716720 96
1789716725 96
1789716730 96
1789716735 94
1789716740 94
1789716745 94
1789716750 94
1789716755 94
1789716760 92
1789716765 92
1789716770 94
1789716775 94
1789716780 94
```
</details>

---

