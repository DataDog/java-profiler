---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:31:53 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 189 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 48-60 cores)</summary>

```
1795012031 60
1795012036 60
1795012041 60
1795012046 60
1795012051 60
1795012056 60
1795012061 60
1795012066 60
1795012071 60
1795012076 60
1795012081 60
1795012087 60
1795012092 60
1795012097 60
1795012102 60
1795012107 60
1795012112 60
1795012117 60
1795012122 60
1795012127 48
```
</details>

---

