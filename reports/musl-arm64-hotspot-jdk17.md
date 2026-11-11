---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:53:37 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 11 |
| Allocations | 30 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 11 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (3 unique values: 46-51 cores)</summary>

```
1794433739 51
1794433744 51
1794433749 50
1794433754 50
1794433759 50
1794433764 50
1794433769 50
1794433774 50
1794433779 51
1794433784 51
1794433789 51
1794433794 51
1794433799 51
1794433804 51
1794433809 51
1794433814 51
1794433819 51
1794433824 51
1794433829 51
1794433834 51
```
</details>

---

