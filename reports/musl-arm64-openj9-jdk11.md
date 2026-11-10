---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:40:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 11 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 34-51 cores)</summary>

```
1794324922 51
1794324927 51
1794324932 51
1794324937 51
1794324942 51
1794324947 51
1794324952 51
1794324957 51
1794324962 51
1794324967 51
1794324972 51
1794324977 34
1794324982 34
1794324987 34
1794324992 34
1794324997 34
1794325002 34
1794325007 34
1794325012 34
1794325017 34
```
</details>

---

