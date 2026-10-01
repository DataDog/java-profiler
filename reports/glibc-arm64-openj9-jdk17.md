---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-01 07:40:05 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 364 |
| Sample Rate | 6.07/sec |
| Health Score | 379% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 14 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790854486 43
1790854491 43
1790854496 43
1790854501 43
1790854506 43
1790854511 43
1790854516 43
1790854521 43
1790854526 43
1790854531 43
1790854536 43
1790854541 43
1790854546 45
1790854551 45
1790854556 45
1790854561 45
1790854566 45
1790854571 45
1790854576 45
1790854581 45
```
</details>

---

