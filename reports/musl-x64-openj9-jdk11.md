---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 13:49:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 11 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 86-94 cores)</summary>

```
1793295783 90
1793295788 90
1793295793 90
1793295798 90
1793295803 92
1793295808 92
1793295813 92
1793295818 92
1793295823 92
1793295828 92
1793295833 92
1793295838 92
1793295843 92
1793295848 92
1793295853 94
1793295858 94
1793295863 94
1793295868 94
1793295873 94
1793295878 94
```
</details>

---

