---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:09:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1794495886 59
1794495891 59
1794495896 59
1794495901 59
1794495906 59
1794495911 61
1794495916 61
1794495921 61
1794495926 61
1794495931 61
1794495937 61
1794495942 61
1794495947 61
1794495952 61
1794495957 61
1794495962 61
1794495967 61
1794495972 61
1794495977 61
1794495982 61
```
</details>

---

