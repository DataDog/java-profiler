---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ❌ FAIL

**Date:** 2026-11-20 08:32:55 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (1 unique values: 67-67 cores)</summary>

```
1795181243 67
1795181248 67
1795181253 67
1795181258 67
1795181263 67
1795181268 67
1795181273 67
1795181278 67
1795181283 67
1795181288 67
1795181293 67
1795181298 67
1795181303 67
1795181308 67
1795181313 67
1795181318 67
1795181323 67
1795181328 67
1795181333 67
1795181338 67
```
</details>

---

