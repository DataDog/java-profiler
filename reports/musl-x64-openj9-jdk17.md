---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 10:08:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (8 unique values: 51-73 cores)</summary>

```
1790172292 51
1790172297 51
1790172302 53
1790172307 53
1790172312 53
1790172317 63
1790172322 63
1790172327 65
1790172332 65
1790172337 67
1790172342 67
1790172347 67
1790172352 67
1790172357 67
1790172362 69
1790172367 69
1790172372 67
1790172377 67
1790172382 69
1790172387 69
```
</details>

---

