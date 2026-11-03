---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:25:56 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793722758 48
1793722763 48
1793722768 48
1793722773 48
1793722778 48
1793722783 48
1793722788 48
1793722793 48
1793722798 48
1793722803 48
1793722808 48
1793722813 48
1793722818 48
1793722823 48
1793722828 48
1793722833 48
1793722838 48
1793722843 48
1793722848 48
1793722853 48
```
</details>

---

