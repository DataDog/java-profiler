---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:21:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 42-51 cores)</summary>

```
1795641274 51
1795641279 51
1795641284 51
1795641289 51
1795641294 51
1795641299 51
1795641304 51
1795641309 51
1795641314 42
1795641319 42
1795641324 42
1795641329 42
1795641334 42
1795641339 42
1795641344 42
1795641349 42
1795641354 42
1795641359 42
1795641364 42
1795641369 44
```
</details>

---

