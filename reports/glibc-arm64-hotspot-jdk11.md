---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 14:59:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 9 |
| Allocations | 192 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 998 |
| Sample Rate | 16.63/sec |
| Health Score | 1039% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1793040953 48
1793040958 48
1793040963 48
1793040968 48
1793040973 48
1793040978 48
1793040983 48
1793040988 48
1793040993 48
1793040998 48
1793041003 48
1793041008 48
1793041013 48
1793041018 48
1793041023 48
1793041028 48
1793041033 48
1793041038 48
1793041043 48
1793041048 40
```
</details>

---

