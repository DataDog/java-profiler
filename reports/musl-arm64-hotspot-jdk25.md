---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 05:04:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (6 unique values: 36-46 cores)</summary>

```
1793177973 41
1793177978 41
1793177983 41
1793177988 41
1793177993 42
1793177998 42
1793178003 44
1793178008 44
1793178013 44
1793178018 44
1793178023 44
1793178028 44
1793178033 44
1793178038 44
1793178043 44
1793178048 44
1793178053 46
1793178058 46
1793178063 46
1793178068 39
```
</details>

---

