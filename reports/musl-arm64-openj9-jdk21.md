---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:43:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1793187384 40
1793187389 40
1793187394 40
1793187399 40
1793187404 40
1793187409 35
1793187414 35
1793187419 35
1793187424 35
1793187429 35
1793187434 35
1793187439 35
1793187444 35
1793187449 35
1793187454 35
1793187459 35
1793187464 35
1793187469 38
1793187474 38
1793187479 38
```
</details>

---

