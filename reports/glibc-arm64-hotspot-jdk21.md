---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 13:05:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790701297 32
1790701302 32
1790701307 32
1790701312 32
1790701317 32
1790701322 32
1790701327 32
1790701332 32
1790701337 32
1790701342 32
1790701347 32
1790701352 32
1790701357 32
1790701362 32
1790701367 32
1790701372 32
1790701377 32
1790701382 32
1790701387 32
1790701392 32
```
</details>

---

