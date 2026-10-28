---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 06:30:17 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 10 |
| Allocations | 97 |

<details>
<summary>CPU Timeline (4 unique values: 36-48 cores)</summary>

```
1793183047 41
1793183052 41
1793183057 41
1793183063 36
1793183068 36
1793183073 41
1793183078 41
1793183083 41
1793183088 41
1793183093 41
1793183098 41
1793183103 43
1793183108 43
1793183113 43
1793183118 43
1793183123 43
1793183128 43
1793183133 43
1793183138 48
1793183143 48
```
</details>

---

