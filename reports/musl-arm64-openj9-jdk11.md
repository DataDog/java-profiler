---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:43:45 EST

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 12 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 11 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794998174 51
1794998179 51
1794998184 51
1794998189 51
1794998194 51
1794998199 51
1794998204 51
1794998209 51
1794998214 51
1794998219 51
1794998224 51
1794998229 51
1794998234 51
1794998239 51
1794998244 51
1794998249 51
1794998254 51
1794998259 51
1794998264 51
1794998270 51
```
</details>

---

