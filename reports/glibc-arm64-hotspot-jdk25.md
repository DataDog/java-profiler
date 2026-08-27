---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-27 09:40:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (4 unique values: 57-62 cores)</summary>

```
1787837725 59
1787837730 59
1787837735 59
1787837740 59
1787837745 59
1787837750 57
1787837755 57
1787837760 59
1787837765 59
1787837770 59
1787837775 59
1787837780 59
1787837785 59
1787837790 62
1787837795 62
1787837800 57
1787837805 57
1787837810 57
1787837815 57
1787837820 57
```
</details>

---

