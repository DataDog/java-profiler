---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-29 09:48:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 22.33/sec |
| Health Score | 1396% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 901 |
| Sample Rate | 30.03/sec |
| Health Score | 1877% |
| Threads | 13 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 81-86 cores)</summary>

```
1769697755 82
1769697760 82
1769697765 82
1769697770 86
1769697775 86
1769697780 81
1769697785 81
1769697790 81
1769697795 81
1769697800 81
1769697805 81
1769697810 81
1769697815 81
1769697820 81
1769697825 81
1769697830 81
1769697835 81
1769697840 81
1769697845 81
1769697850 81
```
</details>

---

