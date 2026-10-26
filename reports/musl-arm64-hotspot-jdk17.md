---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 06:57:16 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 7 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 914 |
| Sample Rate | 15.23/sec |
| Health Score | 952% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793012009 46
1793012014 46
1793012019 46
1793012024 46
1793012029 46
1793012034 46
1793012040 46
1793012045 46
1793012050 51
1793012055 51
1793012060 51
1793012065 51
1793012070 51
1793012075 51
1793012080 51
1793012085 51
1793012090 51
1793012095 51
1793012100 51
1793012105 51
```
</details>

---

