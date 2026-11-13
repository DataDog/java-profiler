---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 13:50:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 14 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1794595538 43
1794595543 43
1794595548 43
1794595553 43
1794595558 43
1794595563 43
1794595568 43
1794595574 43
1794595579 43
1794595584 43
1794595589 40
1794595594 40
1794595599 40
1794595604 40
1794595609 43
1794595614 43
1794595619 43
1794595624 43
1794595629 43
1794595634 43
```
</details>

---

