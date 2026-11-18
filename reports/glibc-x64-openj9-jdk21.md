---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:52:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (7 unique values: 64-82 cores)</summary>

```
1795013194 66
1795013199 66
1795013204 64
1795013209 64
1795013214 64
1795013219 64
1795013224 64
1795013229 64
1795013234 64
1795013239 67
1795013244 67
1795013249 69
1795013254 69
1795013259 76
1795013264 76
1795013269 76
1795013274 76
1795013279 76
1795013284 76
1795013289 76
```
</details>

---

