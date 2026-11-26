---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 11:54:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795711822 96
1795711827 96
1795711832 96
1795711837 96
1795711842 96
1795711847 96
1795711852 96
1795711857 96
1795711862 96
1795711867 96
1795711872 94
1795711877 94
1795711882 94
1795711887 94
1795711892 94
1795711897 94
1795711902 94
1795711907 94
1795711912 96
1795711917 96
```
</details>

---

