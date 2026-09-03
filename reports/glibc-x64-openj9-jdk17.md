---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-03 00:57:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1788411226 96
1788411231 96
1788411236 96
1788411241 96
1788411246 96
1788411251 94
1788411256 94
1788411261 94
1788411266 94
1788411271 94
1788411276 94
1788411281 94
1788411286 94
1788411291 96
1788411296 96
1788411301 96
1788411306 96
1788411311 96
1788411316 96
1788411321 94
```
</details>

---

