---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-29 09:48:27 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 19.63/sec |
| Health Score | 1227% |
| Threads | 10 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1112 |
| Sample Rate | 37.07/sec |
| Health Score | 2317% |
| Threads | 13 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 55-61 cores)</summary>

```
1769697770 61
1769697775 61
1769697780 61
1769697785 61
1769697790 61
1769697795 61
1769697800 61
1769697805 59
1769697810 59
1769697815 59
1769697820 59
1769697825 59
1769697830 59
1769697835 59
1769697840 59
1769697845 59
1769697850 59
1769697855 59
1769697860 59
1769697865 59
```
</details>

---

