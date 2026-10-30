---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 06:28:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 61-64 cores)</summary>

```
1793355813 61
1793355818 61
1793355823 61
1793355828 61
1793355833 61
1793355838 61
1793355843 61
1793355848 61
1793355853 61
1793355858 61
1793355863 63
1793355868 63
1793355873 63
1793355878 63
1793355883 63
1793355888 63
1793355893 61
1793355898 61
1793355903 61
1793355908 61
```
</details>

---

