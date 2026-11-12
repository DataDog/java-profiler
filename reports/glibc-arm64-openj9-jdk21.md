---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 05:58:57 EST

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
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 14 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794480757 43
1794480762 43
1794480767 43
1794480772 48
1794480777 48
1794480782 48
1794480787 48
1794480792 48
1794480797 48
1794480802 48
1794480807 48
1794480812 48
1794480817 48
1794480822 48
1794480827 48
1794480832 48
1794480837 48
1794480842 48
1794480847 48
1794480852 48
```
</details>

---

