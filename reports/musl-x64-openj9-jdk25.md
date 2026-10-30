---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 11:07:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 64-69 cores)</summary>

```
1793372531 64
1793372536 64
1793372541 69
1793372546 69
1793372551 69
1793372556 69
1793372561 69
1793372566 69
1793372571 69
1793372577 69
1793372582 69
1793372587 69
1793372592 69
1793372597 69
1793372602 69
1793372607 69
1793372612 67
1793372617 67
1793372622 67
1793372627 67
```
</details>

---

