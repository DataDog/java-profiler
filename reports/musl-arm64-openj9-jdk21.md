---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 13:06:01 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1790701257 41
1790701262 41
1790701267 41
1790701272 41
1790701277 41
1790701282 41
1790701287 43
1790701292 43
1790701297 48
1790701302 48
1790701307 48
1790701312 48
1790701317 48
1790701322 48
1790701327 48
1790701332 48
1790701337 48
1790701342 48
1790701347 48
1790701352 48
```
</details>

---

