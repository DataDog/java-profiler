---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 05:04:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 29-37 cores)</summary>

```
1793178011 31
1793178016 31
1793178021 31
1793178026 29
1793178031 29
1793178036 29
1793178041 29
1793178046 32
1793178051 32
1793178056 32
1793178061 32
1793178066 32
1793178071 32
1793178076 32
1793178081 32
1793178086 37
1793178091 37
1793178096 37
1793178101 37
1793178106 37
```
</details>

---

