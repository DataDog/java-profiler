---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 10:44:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 281 |
| Sample Rate | 4.68/sec |
| Health Score | 292% |
| Threads | 14 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794843622 46
1794843627 46
1794843632 46
1794843637 51
1794843642 51
1794843647 51
1794843652 51
1794843657 51
1794843662 51
1794843667 51
1794843672 51
1794843677 51
1794843682 51
1794843687 51
1794843693 51
1794843698 51
1794843703 51
1794843708 51
1794843713 51
1794843718 51
```
</details>

---

