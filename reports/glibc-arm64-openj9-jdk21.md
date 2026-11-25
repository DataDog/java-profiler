---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:02:39 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 14 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795618594 28
1795618599 28
1795618604 28
1795618609 28
1795618614 28
1795618619 28
1795618624 33
1795618629 33
1795618635 33
1795618640 33
1795618645 33
1795618650 33
1795618655 33
1795618660 33
1795618665 33
1795618670 33
1795618675 33
1795618680 33
1795618685 33
1795618690 33
```
</details>

---

