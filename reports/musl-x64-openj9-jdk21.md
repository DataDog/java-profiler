---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:18:51 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 46-57 cores)</summary>

```
1795641199 46
1795641204 46
1795641209 46
1795641214 46
1795641219 46
1795641224 46
1795641229 46
1795641234 46
1795641239 46
1795641244 46
1795641249 46
1795641254 46
1795641259 57
1795641264 57
1795641269 57
1795641274 57
1795641279 57
1795641284 57
1795641289 57
1795641294 57
```
</details>

---

