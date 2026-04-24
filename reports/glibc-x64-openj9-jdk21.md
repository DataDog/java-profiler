---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-24 17:03:59 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 11 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (4 unique values: 69-82 cores)</summary>

```
1777064257 72
1777064262 72
1777064267 72
1777064272 72
1777064277 72
1777064282 72
1777064287 72
1777064292 72
1777064297 72
1777064302 72
1777064307 72
1777064312 72
1777064317 72
1777064322 74
1777064327 74
1777064332 74
1777064337 69
1777064342 69
1777064347 82
1777064352 82
```
</details>

---

