---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 04:33:10 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 11 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 13 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (5 unique values: 65-87 cores)</summary>

```
1773217608 70
1773217613 70
1773217618 70
1773217623 70
1773217628 74
1773217633 74
1773217638 74
1773217643 74
1773217648 74
1773217653 74
1773217658 74
1773217663 74
1773217668 74
1773217673 74
1773217678 65
1773217683 65
1773217688 65
1773217693 87
1773217698 87
1773217703 87
```
</details>

---

