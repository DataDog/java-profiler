---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-15 09:57:53 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 13 |
| Allocations | 168 |

<details>
<summary>CPU Timeline (3 unique values: 53-64 cores)</summary>

```
1792072298 53
1792072303 53
1792072308 53
1792072313 64
1792072318 64
1792072323 54
1792072328 54
1792072333 54
1792072338 54
1792072343 54
1792072348 54
1792072353 54
1792072358 54
1792072363 54
1792072368 54
1792072373 54
1792072378 54
1792072383 54
1792072388 54
1792072393 54
```
</details>

---

