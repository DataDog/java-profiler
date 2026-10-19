---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 05:55:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 11 |
| Allocations | 187 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 27-28 cores)</summary>

```
1792403424 27
1792403429 27
1792403434 27
1792403439 27
1792403444 28
1792403449 28
1792403454 28
1792403459 28
1792403464 28
1792403469 28
1792403474 28
1792403479 28
1792403484 28
1792403489 28
1792403494 28
1792403499 28
1792403504 28
1792403509 28
1792403514 28
1792403519 28
```
</details>

---

