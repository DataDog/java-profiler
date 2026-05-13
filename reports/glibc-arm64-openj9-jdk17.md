---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-13 07:32:03 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 12 |
| Allocations | 107 |

<details>
<summary>CPU Timeline (2 unique values: 32-36 cores)</summary>

```
1778671580 32
1778671585 32
1778671590 36
1778671595 36
1778671600 36
1778671605 36
1778671610 36
1778671615 36
1778671620 36
1778671625 36
1778671630 36
1778671635 36
1778671640 36
1778671645 36
1778671650 36
1778671655 36
1778671660 36
1778671665 36
1778671670 36
1778671675 36
```
</details>

---

