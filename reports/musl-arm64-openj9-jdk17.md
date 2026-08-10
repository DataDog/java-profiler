---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 09:14:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 350 |
| Sample Rate | 5.83/sec |
| Health Score | 364% |
| Threads | 12 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1786367356 40
1786367361 40
1786367366 40
1786367371 40
1786367377 48
1786367382 48
1786367387 48
1786367392 48
1786367397 48
1786367402 48
1786367407 48
1786367412 48
1786367417 48
1786367422 48
1786367427 48
1786367432 48
1786367437 48
1786367442 48
1786367447 48
1786367452 48
```
</details>

---

