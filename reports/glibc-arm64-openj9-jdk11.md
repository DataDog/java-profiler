---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:43:20 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 332 |
| Sample Rate | 5.53/sec |
| Health Score | 346% |
| Threads | 13 |
| Allocations | 173 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793187399 30
1793187404 30
1793187409 30
1793187414 30
1793187419 30
1793187424 30
1793187429 30
1793187434 30
1793187439 30
1793187444 30
1793187449 30
1793187454 30
1793187459 30
1793187464 30
1793187469 30
1793187474 30
1793187479 30
1793187484 30
1793187489 30
1793187494 30
```
</details>

---

