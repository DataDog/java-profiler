---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 04:29:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1790238298 50
1790238303 50
1790238308 50
1790238313 50
1790238318 45
1790238323 45
1790238328 45
1790238333 45
1790238338 45
1790238343 45
1790238348 45
1790238353 45
1790238358 45
1790238363 45
1790238368 45
1790238373 45
1790238378 45
1790238383 45
1790238388 45
1790238393 45
```
</details>

---

