---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 00:08:04 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 947 |
| Sample Rate | 15.78/sec |
| Health Score | 986% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 33-43 cores)</summary>

```
1794287003 33
1794287008 33
1794287013 33
1794287018 33
1794287023 33
1794287028 33
1794287033 33
1794287038 33
1794287043 33
1794287048 33
1794287053 33
1794287058 33
1794287063 33
1794287068 33
1794287073 38
1794287078 38
1794287083 38
1794287088 38
1794287093 43
1794287098 43
```
</details>

---

