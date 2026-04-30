---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-30 10:12:30 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 36-46 cores)</summary>

```
1777558035 36
1777558040 36
1777558045 36
1777558050 36
1777558055 36
1777558060 36
1777558065 41
1777558070 41
1777558075 41
1777558080 41
1777558085 41
1777558090 41
1777558095 46
1777558100 46
1777558105 46
1777558110 46
1777558115 46
1777558120 46
1777558125 46
1777558130 46
```
</details>

---

