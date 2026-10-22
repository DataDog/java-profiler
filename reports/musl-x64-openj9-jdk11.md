---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:01:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1792684397 64
1792684402 64
1792684407 64
1792684412 64
1792684417 64
1792684422 64
1792684427 64
1792684432 64
1792684437 64
1792684442 64
1792684447 64
1792684452 64
1792684457 64
1792684462 64
1792684467 64
1792684472 64
1792684477 64
1792684482 64
1792684488 47
1792684493 47
```
</details>

---

