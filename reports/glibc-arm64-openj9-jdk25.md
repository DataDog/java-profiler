---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 07:41:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 8 |
| Allocations | 445 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 14 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794832730 46
1794832735 46
1794832740 46
1794832745 46
1794832750 46
1794832755 46
1794832760 46
1794832765 46
1794832770 46
1794832775 46
1794832780 46
1794832785 46
1794832790 46
1794832795 46
1794832800 46
1794832805 46
1794832810 46
1794832815 46
1794832820 48
1794832825 48
```
</details>

---

