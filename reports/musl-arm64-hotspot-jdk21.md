---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 17:11:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 10 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (5 unique values: 46-59 cores)</summary>

```
1793657040 46
1793657045 49
1793657050 49
1793657055 49
1793657060 53
1793657065 53
1793657070 54
1793657075 54
1793657080 54
1793657085 54
1793657090 54
1793657095 54
1793657100 54
1793657105 54
1793657110 54
1793657115 54
1793657120 54
1793657125 54
1793657130 54
1793657135 54
```
</details>

---

