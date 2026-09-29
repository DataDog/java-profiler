---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 13:06:01 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 12 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (6 unique values: 38-48 cores)</summary>

```
1790701223 43
1790701228 43
1790701233 48
1790701238 48
1790701243 48
1790701248 48
1790701253 48
1790701258 48
1790701263 47
1790701268 47
1790701273 47
1790701278 47
1790701283 42
1790701288 42
1790701293 42
1790701298 42
1790701303 42
1790701308 42
1790701313 38
1790701318 38
```
</details>

---

