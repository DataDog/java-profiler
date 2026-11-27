---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-27 13:25:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 32-37 cores)</summary>

```
1795803652 32
1795803658 32
1795803663 32
1795803668 32
1795803673 32
1795803678 32
1795803683 32
1795803688 32
1795803693 32
1795803698 32
1795803703 37
1795803708 37
1795803713 37
1795803718 37
1795803723 37
1795803728 37
1795803733 37
1795803738 37
1795803743 37
1795803748 37
```
</details>

---

