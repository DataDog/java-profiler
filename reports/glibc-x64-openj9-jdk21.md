---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-05 15:44:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 8 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1772743226 25
1772743231 25
1772743236 25
1772743241 25
1772743246 25
1772743251 25
1772743256 25
1772743261 25
1772743266 25
1772743271 25
1772743276 30
1772743281 30
1772743286 30
1772743291 30
1772743296 30
1772743301 30
1772743306 30
1772743311 30
1772743316 30
1772743321 30
```
</details>

---

