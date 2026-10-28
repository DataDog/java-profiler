---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 20:01:53 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1793145461 29
1793145466 29
1793145471 29
1793145476 29
1793145481 29
1793145486 29
1793145491 29
1793145496 29
1793145501 29
1793145506 29
1793145511 29
1793145516 29
1793145521 29
1793145526 29
1793145531 29
1793145536 29
1793145541 29
1793145546 29
1793145551 29
1793145556 29
```
</details>

---

