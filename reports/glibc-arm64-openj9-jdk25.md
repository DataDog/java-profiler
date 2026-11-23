---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 10:10:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 11 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795446272 64
1795446277 64
1795446282 64
1795446287 64
1795446292 64
1795446297 64
1795446302 64
1795446307 64
1795446312 64
1795446317 64
1795446322 64
1795446327 64
1795446332 64
1795446337 64
1795446342 64
1795446347 64
1795446352 64
1795446357 64
1795446362 64
1795446367 64
```
</details>

---

