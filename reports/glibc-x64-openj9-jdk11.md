---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:37:17 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1794832322 52
1794832327 52
1794832332 52
1794832337 52
1794832342 52
1794832347 52
1794832352 52
1794832357 52
1794832362 54
1794832367 54
1794832372 54
1794832377 54
1794832382 54
1794832387 54
1794832392 54
1794832397 54
1794832402 54
1794832407 54
1794832412 54
1794832417 54
```
</details>

---

