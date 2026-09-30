---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 15:17:25 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 8 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1790795608 48
1790795613 48
1790795618 48
1790795623 48
1790795628 48
1790795633 48
1790795638 48
1790795643 48
1790795648 28
1790795653 28
1790795658 28
1790795663 28
1790795668 28
1790795673 28
1790795678 28
1790795684 28
1790795689 28
1790795694 28
1790795699 28
1790795704 28
```
</details>

---

