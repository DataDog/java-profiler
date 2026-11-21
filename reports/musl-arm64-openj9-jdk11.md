---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-21 05:47:04 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 11 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1795257769 19
1795257774 19
1795257779 19
1795257784 19
1795257789 24
1795257794 24
1795257799 24
1795257804 24
1795257809 24
1795257814 24
1795257819 24
1795257824 24
1795257829 24
1795257834 24
1795257839 24
1795257844 24
1795257849 24
1795257854 24
1795257859 24
1795257864 24
```
</details>

---

