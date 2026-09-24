---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 05:51:59 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 12 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 42-72 cores)</summary>

```
1790243086 42
1790243091 42
1790243096 42
1790243101 42
1790243106 42
1790243111 42
1790243116 42
1790243121 42
1790243126 42
1790243131 72
1790243136 72
1790243141 55
1790243146 55
1790243151 55
1790243156 55
1790243161 55
1790243166 55
1790243172 55
1790243177 55
1790243182 55
```
</details>

---

