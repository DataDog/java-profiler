---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 11:33:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 9 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 50-51 cores)</summary>

```
1794932942 51
1794932947 51
1794932952 51
1794932957 51
1794932962 51
1794932967 51
1794932972 51
1794932977 51
1794932982 51
1794932987 51
1794932992 51
1794932997 51
1794933002 50
1794933007 50
1794933013 50
1794933018 50
1794933023 50
1794933028 50
1794933033 50
1794933038 50
```
</details>

---

