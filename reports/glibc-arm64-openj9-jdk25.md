---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:00:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (4 unique values: 39-43 cores)</summary>

```
1793631355 39
1793631360 42
1793631365 42
1793631370 42
1793631375 42
1793631380 42
1793631385 42
1793631390 42
1793631395 42
1793631400 43
1793631405 43
1793631410 41
1793631415 41
1793631420 41
1793631425 41
1793631430 41
1793631435 41
1793631440 41
1793631445 41
1793631450 41
```
</details>

---

