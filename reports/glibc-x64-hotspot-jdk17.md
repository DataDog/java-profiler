---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-27 07:43:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 79-83 cores)</summary>

```
1793101163 83
1793101168 83
1793101173 83
1793101178 83
1793101183 83
1793101188 83
1793101193 83
1793101198 83
1793101203 83
1793101208 83
1793101213 83
1793101218 83
1793101223 83
1793101228 83
1793101233 83
1793101238 83
1793101243 83
1793101248 83
1793101253 83
1793101258 81
```
</details>

---

