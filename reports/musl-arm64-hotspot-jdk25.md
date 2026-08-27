---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-27 16:16:20 EDT

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 9-14 cores)</summary>

```
1787854935 9
1787854940 14
1787854945 14
1787854950 14
1787854955 14
1787854960 10
1787854965 10
1787854970 10
1787854975 10
1787854980 10
1787854985 10
1787854990 10
1787854995 10
1787855000 10
1787855005 10
1787855010 10
1787855015 10
1787855020 10
1787855025 10
1787855030 10
```
</details>

---

