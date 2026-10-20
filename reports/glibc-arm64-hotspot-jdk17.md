---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 16:39:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 34 |
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
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1792528446 39
1792528451 39
1792528456 39
1792528461 39
1792528466 39
1792528471 39
1792528476 39
1792528481 39
1792528486 39
1792528491 39
1792528496 39
1792528501 39
1792528506 39
1792528511 39
1792528516 39
1792528521 34
1792528526 34
1792528531 34
1792528536 34
1792528541 34
```
</details>

---

