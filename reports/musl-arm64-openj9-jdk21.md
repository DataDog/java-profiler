---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 09:24:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 10 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795702817 64
1795702822 64
1795702827 64
1795702832 64
1795702837 64
1795702842 64
1795702847 64
1795702853 64
1795702858 64
1795702863 64
1795702868 64
1795702873 64
1795702878 64
1795702883 64
1795702888 64
1795702893 64
1795702898 64
1795702903 64
1795702908 64
1795702913 64
```
</details>

---

