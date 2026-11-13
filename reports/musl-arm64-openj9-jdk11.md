---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:45:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1107 |
| Sample Rate | 18.45/sec |
| Health Score | 1153% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794573761 51
1794573766 51
1794573771 51
1794573776 51
1794573781 51
1794573786 51
1794573791 51
1794573796 51
1794573801 51
1794573806 51
1794573811 51
1794573816 51
1794573821 51
1794573826 51
1794573831 51
1794573836 51
1794573841 51
1794573846 51
1794573851 51
1794573856 51
```
</details>

---

