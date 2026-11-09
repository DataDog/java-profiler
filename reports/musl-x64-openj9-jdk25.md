---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 06:39:12 EST

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
| CPU Cores (end) | 55 |
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
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 51-55 cores)</summary>

```
1794224069 51
1794224074 51
1794224079 51
1794224084 51
1794224089 51
1794224094 53
1794224099 53
1794224104 53
1794224109 53
1794224114 53
1794224119 53
1794224124 53
1794224129 53
1794224134 53
1794224139 53
1794224144 53
1794224149 53
1794224154 55
1794224159 55
1794224164 55
```
</details>

---

