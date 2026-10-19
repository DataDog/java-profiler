---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 05:55:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1792403413 41
1792403418 41
1792403423 41
1792403428 41
1792403433 46
1792403438 46
1792403443 46
1792403448 46
1792403453 46
1792403458 46
1792403463 46
1792403468 46
1792403473 46
1792403478 46
1792403483 46
1792403488 46
1792403493 46
1792403498 46
1792403503 46
1792403508 46
```
</details>

---

