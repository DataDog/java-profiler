---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 04:02:13 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1778572557 42
1778572562 42
1778572567 42
1778572572 42
1778572577 42
1778572582 42
1778572587 42
1778572592 42
1778572597 42
1778572602 42
1778572607 42
1778572612 42
1778572617 42
1778572622 42
1778572627 42
1778572632 42
1778572637 42
1778572642 42
1778572647 42
1778572652 47
```
</details>

---

