---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 12:04:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793203131 30
1793203136 30
1793203141 30
1793203146 30
1793203151 30
1793203156 30
1793203161 30
1793203167 30
1793203172 30
1793203177 30
1793203182 32
1793203187 32
1793203192 32
1793203197 32
1793203202 32
1793203207 32
1793203212 32
1793203217 32
1793203222 32
1793203227 32
```
</details>

---

