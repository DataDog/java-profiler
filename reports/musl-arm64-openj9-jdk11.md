---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 09:45:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 39-40 cores)</summary>

```
1793281262 40
1793281267 40
1793281272 40
1793281277 40
1793281282 40
1793281287 40
1793281292 40
1793281297 40
1793281302 40
1793281307 40
1793281312 40
1793281317 40
1793281322 40
1793281327 40
1793281332 40
1793281337 40
1793281342 40
1793281347 40
1793281352 40
1793281357 40
```
</details>

---

