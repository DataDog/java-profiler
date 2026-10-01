---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-01 06:31:10 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (5 unique values: 39-50 cores)</summary>

```
1790850369 50
1790850374 50
1790850379 50
1790850384 50
1790850389 50
1790850394 50
1790850399 48
1790850404 48
1790850409 48
1790850414 48
1790850419 44
1790850424 44
1790850429 44
1790850434 44
1790850439 42
1790850444 42
1790850449 42
1790850454 42
1790850459 42
1790850464 39
```
</details>

---

