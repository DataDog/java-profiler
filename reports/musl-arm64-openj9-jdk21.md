---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 10:05:25 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 9 |
| Allocations | 139 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 974 |
| Sample Rate | 16.23/sec |
| Health Score | 1014% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1792591214 49
1792591219 49
1792591224 49
1792591229 49
1792591234 49
1792591239 49
1792591244 54
1792591249 54
1792591254 54
1792591259 54
1792591264 54
1792591269 54
1792591274 54
1792591279 54
1792591284 54
1792591289 54
1792591294 54
1792591299 54
1792591304 54
1792591309 54
```
</details>

---

