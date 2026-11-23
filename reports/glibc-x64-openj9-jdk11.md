---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 10:10:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (5 unique values: 45-54 cores)</summary>

```
1795446247 54
1795446252 52
1795446257 52
1795446262 52
1795446267 52
1795446272 52
1795446277 50
1795446282 50
1795446287 50
1795446292 50
1795446297 50
1795446302 50
1795446307 50
1795446312 50
1795446317 52
1795446322 52
1795446327 52
1795446332 52
1795446337 52
1795446342 52
```
</details>

---

