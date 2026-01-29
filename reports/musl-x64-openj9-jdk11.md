---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 11:12:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 22.43/sec |
| Health Score | 1402% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 864 |
| Sample Rate | 28.80/sec |
| Health Score | 1800% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (8 unique values: 57-94 cores)</summary>

```
1769702710 61
1769702715 63
1769702720 63
1769702725 61
1769702730 61
1769702735 61
1769702740 59
1769702745 59
1769702750 59
1769702755 59
1769702760 59
1769702765 59
1769702770 57
1769702775 57
1769702780 57
1769702785 85
1769702790 85
1769702795 87
1769702800 87
1769702805 89
```
</details>

---

