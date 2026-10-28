---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 06:30:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 220 |
| Sample Rate | 3.67/sec |
| Health Score | 229% |
| Threads | 13 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793183073 48
1793183078 46
1793183083 46
1793183088 46
1793183093 46
1793183098 46
1793183103 46
1793183108 46
1793183113 46
1793183118 46
1793183123 46
1793183128 46
1793183133 46
1793183138 46
1793183143 46
1793183148 46
1793183153 46
1793183158 46
1793183163 46
1793183168 46
```
</details>

---

