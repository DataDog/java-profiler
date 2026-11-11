---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 00:08:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 8 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794373431 38
1794373436 38
1794373441 38
1794373446 38
1794373451 38
1794373456 38
1794373461 43
1794373466 43
1794373471 43
1794373476 43
1794373481 43
1794373486 43
1794373491 43
1794373496 43
1794373501 43
1794373506 43
1794373511 43
1794373516 43
1794373521 43
1794373526 43
```
</details>

---

