---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 08:26:30 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (5 unique values: 38-55 cores)</summary>

```
1790857344 38
1790857349 38
1790857354 38
1790857359 38
1790857364 38
1790857369 38
1790857374 41
1790857379 41
1790857384 41
1790857389 41
1790857394 41
1790857399 41
1790857404 41
1790857409 55
1790857414 55
1790857419 55
1790857424 55
1790857429 55
1790857434 55
1790857439 50
```
</details>

---

