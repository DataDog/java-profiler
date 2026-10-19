---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 05:55:46 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 54-64 cores)</summary>

```
1792403407 54
1792403412 64
1792403417 64
1792403422 64
1792403427 64
1792403432 64
1792403437 64
1792403442 64
1792403447 64
1792403452 64
1792403457 64
1792403462 64
1792403467 64
1792403472 64
1792403477 64
1792403482 64
1792403487 64
1792403492 64
1792403497 64
1792403502 64
```
</details>

---

