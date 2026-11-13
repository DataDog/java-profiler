---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-11-13 09:46:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1794580867 92
1794580872 92
1794580877 90
1794580882 90
1794580887 90
1794580892 90
1794580897 90
1794580902 90
1794580907 90
1794580912 92
1794580917 92
1794580922 92
1794580927 92
1794580932 92
1794580937 92
1794580942 92
1794580947 92
1794580952 92
1794580957 92
1794580962 94
```
</details>

---

