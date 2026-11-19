---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 08:48:43 EST

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
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 11 |
| Allocations | 101 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795095812 50
1795095817 50
1795095822 50
1795095827 50
1795095832 50
1795095837 50
1795095842 50
1795095847 50
1795095852 50
1795095857 50
1795095862 50
1795095867 50
1795095872 50
1795095877 50
1795095882 50
1795095887 50
1795095892 50
1795095897 50
1795095902 50
1795095907 50
```
</details>

---

