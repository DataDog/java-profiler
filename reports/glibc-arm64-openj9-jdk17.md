---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-01 07:20:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 10 |
| Allocations | 175 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (5 unique values: 33-43 cores)</summary>

```
1790853368 33
1790853373 33
1790853378 33
1790853383 38
1790853388 38
1790853393 38
1790853398 38
1790853403 40
1790853408 40
1790853413 40
1790853418 40
1790853423 42
1790853428 42
1790853433 42
1790853438 42
1790853443 42
1790853448 42
1790853453 42
1790853458 42
1790853463 42
```
</details>

---

