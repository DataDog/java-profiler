---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-04 05:47:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (6 unique values: 20-47 cores)</summary>

```
1791106970 47
1791106975 47
1791106980 47
1791106985 30
1791106990 30
1791106995 32
1791107000 32
1791107005 32
1791107010 22
1791107015 22
1791107020 22
1791107025 22
1791107030 22
1791107035 22
1791107040 22
1791107045 22
1791107050 20
1791107055 20
1791107060 20
1791107065 20
```
</details>

---

