---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-27 21:22:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 10 |
| Allocations | 193 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1790558277 13
1790558282 13
1790558287 13
1790558292 13
1790558297 13
1790558302 13
1790558307 13
1790558312 18
1790558317 18
1790558322 18
1790558327 18
1790558332 18
1790558337 18
1790558343 18
1790558348 18
1790558353 18
1790558358 18
1790558363 18
1790558368 18
1790558373 18
```
</details>

---

