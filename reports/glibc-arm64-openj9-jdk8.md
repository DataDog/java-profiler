---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-22 09:44:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 24-34 cores)</summary>

```
1792676372 24
1792676377 24
1792676382 24
1792676387 24
1792676392 27
1792676397 27
1792676402 27
1792676407 27
1792676412 27
1792676417 27
1792676422 27
1792676427 29
1792676432 29
1792676437 34
1792676442 34
1792676447 34
1792676452 34
1792676457 34
1792676462 34
1792676467 34
```
</details>

---

