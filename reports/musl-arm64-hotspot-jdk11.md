---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 11:54:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1795711812 32
1795711817 32
1795711822 32
1795711827 32
1795711832 32
1795711837 32
1795711842 32
1795711847 32
1795711852 32
1795711857 32
1795711862 32
1795711867 32
1795711872 32
1795711877 32
1795711882 30
1795711887 30
1795711892 30
1795711897 30
1795711902 30
1795711907 30
```
</details>

---

