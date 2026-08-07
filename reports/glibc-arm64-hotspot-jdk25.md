---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-07 07:56:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 14 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786103484 48
1786103489 48
1786103494 53
1786103499 53
1786103504 53
1786103509 53
1786103514 53
1786103519 53
1786103524 53
1786103529 53
1786103534 53
1786103539 53
1786103544 53
1786103549 53
1786103554 53
1786103559 53
1786103564 53
1786103569 53
1786103574 53
1786103579 53
```
</details>

---

