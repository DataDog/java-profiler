---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 07:26:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 54-58 cores)</summary>

```
1792408984 54
1792408989 54
1792408994 54
1792408999 54
1792409004 54
1792409009 54
1792409014 54
1792409019 54
1792409024 54
1792409029 54
1792409034 54
1792409039 58
1792409044 58
1792409049 58
1792409054 58
1792409059 58
1792409064 58
1792409069 58
1792409074 58
1792409079 58
```
</details>

---

