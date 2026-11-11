---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 19:36:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 12 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 48-56 cores)</summary>

```
1794357158 48
1794357163 48
1794357168 48
1794357173 48
1794357178 48
1794357183 48
1794357188 48
1794357193 48
1794357198 48
1794357203 48
1794357209 48
1794357214 48
1794357219 48
1794357224 48
1794357229 48
1794357234 48
1794357239 56
1794357244 56
1794357249 56
1794357254 56
```
</details>

---

