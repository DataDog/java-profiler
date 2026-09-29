---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 13:06:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 11 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (4 unique values: 85-96 cores)</summary>

```
1790701243 87
1790701248 87
1790701253 87
1790701258 87
1790701263 85
1790701268 85
1790701273 85
1790701278 85
1790701283 85
1790701288 85
1790701293 94
1790701298 94
1790701303 94
1790701308 94
1790701313 94
1790701318 94
1790701323 94
1790701328 96
1790701333 96
1790701338 96
```
</details>

---

