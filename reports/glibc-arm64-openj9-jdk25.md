---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:02:24 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1789995400 17
1789995405 17
1789995410 17
1789995415 17
1789995420 17
1789995425 17
1789995430 17
1789995435 17
1789995440 17
1789995445 15
1789995450 15
1789995455 15
1789995460 15
1789995465 15
1789995470 15
1789995475 15
1789995480 15
1789995485 15
1789995490 15
1789995495 15
```
</details>

---

