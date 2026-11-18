---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:08:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 34-42 cores)</summary>

```
1794999762 42
1794999767 42
1794999772 42
1794999777 42
1794999782 42
1794999787 42
1794999792 42
1794999797 42
1794999802 42
1794999807 42
1794999812 42
1794999817 34
1794999822 34
1794999827 34
1794999832 34
1794999837 34
1794999842 34
1794999847 34
1794999852 34
1794999857 34
```
</details>

---

