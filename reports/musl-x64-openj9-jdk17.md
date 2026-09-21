---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 00:57:38 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 976 |
| Sample Rate | 16.27/sec |
| Health Score | 1017% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 53-96 cores)</summary>

```
1789966358 53
1789966363 53
1789966368 53
1789966373 55
1789966378 55
1789966383 55
1789966388 55
1789966393 53
1789966398 53
1789966403 53
1789966408 53
1789966413 53
1789966418 53
1789966423 53
1789966428 53
1789966433 53
1789966438 53
1789966443 96
1789966448 96
1789966453 96
```
</details>

---

