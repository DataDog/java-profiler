---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-19 05:56:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 45-53 cores)</summary>

```
1792403508 45
1792403513 45
1792403518 45
1792403523 45
1792403528 45
1792403533 45
1792403538 45
1792403543 45
1792403548 45
1792403553 45
1792403558 45
1792403563 45
1792403568 45
1792403573 45
1792403578 45
1792403583 45
1792403588 45
1792403593 45
1792403598 45
1792403603 53
```
</details>

---

