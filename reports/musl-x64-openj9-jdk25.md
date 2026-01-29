---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 11:12:25 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 21.97/sec |
| Health Score | 1373% |
| Threads | 12 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1119 |
| Sample Rate | 37.30/sec |
| Health Score | 2331% |
| Threads | 12 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 84-88 cores)</summary>

```
1769702695 86
1769702700 86
1769702705 88
1769702710 88
1769702715 84
1769702720 84
1769702725 84
1769702730 84
1769702735 84
1769702740 84
1769702745 84
1769702750 84
1769702755 84
1769702760 84
1769702765 84
1769702770 84
1769702775 84
1769702780 84
1769702785 84
1769702790 84
```
</details>

---

