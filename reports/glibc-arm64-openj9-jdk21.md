---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:37:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 10 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (4 unique values: 41-51 cores)</summary>

```
1794832332 49
1794832337 49
1794832342 49
1794832347 49
1794832352 49
1794832357 49
1794832362 49
1794832367 49
1794832372 49
1794832377 49
1794832382 49
1794832387 49
1794832392 49
1794832397 49
1794832402 51
1794832407 51
1794832412 46
1794832417 46
1794832422 46
1794832427 46
```
</details>

---

