---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 14:37:04 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (5 unique values: 39-48 cores)</summary>

```
1790361207 43
1790361212 43
1790361217 41
1790361222 41
1790361227 41
1790361232 41
1790361237 41
1790361242 41
1790361247 41
1790361252 41
1790361257 41
1790361262 41
1790361267 41
1790361272 41
1790361277 41
1790361282 41
1790361287 39
1790361292 39
1790361297 48
1790361302 48
```
</details>

---

