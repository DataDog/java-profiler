---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 09:45:19 EDT

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 14 |
| Allocations | 191 |

<details>
<summary>CPU Timeline (3 unique values: 10-30 cores)</summary>

```
1793367677 10
1793367682 10
1793367687 10
1793367692 10
1793367697 10
1793367702 10
1793367707 10
1793367712 10
1793367717 10
1793367722 10
1793367728 10
1793367733 10
1793367738 10
1793367743 10
1793367748 10
1793367753 10
1793367758 10
1793367763 10
1793367768 10
1793367773 10
```
</details>

---

