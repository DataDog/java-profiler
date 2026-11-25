---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:18:49 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795641204 34
1795641209 34
1795641214 34
1795641219 34
1795641224 34
1795641229 34
1795641234 34
1795641239 34
1795641244 34
1795641249 34
1795641254 34
1795641259 34
1795641264 34
1795641269 34
1795641274 34
1795641279 29
1795641284 29
1795641289 29
1795641294 29
1795641299 29
```
</details>

---

