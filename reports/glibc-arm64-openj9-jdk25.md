---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 05:26:29 EDT

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
| CPU Cores (start) | 40 |
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
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1789982427 40
1789982432 40
1789982437 48
1789982442 48
1789982447 48
1789982452 48
1789982457 48
1789982462 48
1789982467 48
1789982472 48
1789982477 48
1789982482 48
1789982487 48
1789982492 48
1789982497 48
1789982502 48
1789982507 48
1789982512 48
1789982517 48
1789982522 48
```
</details>

---

