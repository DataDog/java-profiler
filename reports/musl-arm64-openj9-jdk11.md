---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 08:41:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 897 |
| Sample Rate | 14.95/sec |
| Health Score | 934% |
| Threads | 8 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793799378 48
1793799383 48
1793799388 48
1793799393 48
1793799398 48
1793799403 48
1793799408 48
1793799413 48
1793799418 48
1793799423 48
1793799428 48
1793799433 48
1793799438 48
1793799443 48
1793799448 48
1793799453 48
1793799458 48
1793799463 48
1793799468 48
1793799473 48
```
</details>

---

