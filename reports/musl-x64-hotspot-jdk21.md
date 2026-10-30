---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 11:47:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 78-82 cores)</summary>

```
1793374866 80
1793374871 80
1793374876 80
1793374881 80
1793374886 80
1793374891 80
1793374896 80
1793374901 80
1793374906 78
1793374911 78
1793374916 78
1793374921 78
1793374926 78
1793374931 78
1793374936 78
1793374941 78
1793374946 78
1793374951 78
1793374956 82
1793374961 82
```
</details>

---

