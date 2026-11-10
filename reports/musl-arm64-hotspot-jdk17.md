---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 00:08:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 10 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 11 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794287018 43
1794287023 48
1794287028 48
1794287033 48
1794287038 48
1794287043 48
1794287048 48
1794287053 48
1794287058 48
1794287063 43
1794287068 43
1794287073 43
1794287078 43
1794287083 43
1794287088 43
1794287093 43
1794287098 43
1794287103 43
1794287108 43
1794287113 43
```
</details>

---

