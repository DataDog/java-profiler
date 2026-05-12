---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 04:02:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1143 |
| Sample Rate | 19.05/sec |
| Health Score | 1191% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 87-92 cores)</summary>

```
1778572561 87
1778572566 87
1778572571 87
1778572576 87
1778572581 87
1778572586 87
1778572591 87
1778572596 87
1778572601 87
1778572606 87
1778572611 87
1778572617 87
1778572622 87
1778572627 92
1778572632 92
1778572637 92
1778572642 92
1778572647 92
1778572652 92
1778572657 92
```
</details>

---

