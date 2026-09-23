---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:09:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790168626 43
1790168631 43
1790168636 43
1790168641 43
1790168646 43
1790168651 43
1790168656 43
1790168661 48
1790168666 48
1790168671 48
1790168676 48
1790168681 48
1790168686 48
1790168691 48
1790168696 48
1790168701 48
1790168706 48
1790168711 48
1790168716 48
1790168721 48
```
</details>

---

