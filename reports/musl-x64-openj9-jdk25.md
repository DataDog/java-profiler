---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 06:37:22 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 34-73 cores)</summary>

```
1794396771 51
1794396776 51
1794396781 51
1794396786 51
1794396791 51
1794396796 51
1794396801 51
1794396806 51
1794396811 51
1794396816 73
1794396821 73
1794396826 73
1794396831 73
1794396836 40
1794396841 40
1794396846 40
1794396851 40
1794396856 40
1794396861 40
1794396866 37
```
</details>

---

