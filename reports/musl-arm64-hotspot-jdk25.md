---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-04 14:55:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788547855 64
1788547860 64
1788547865 64
1788547870 64
1788547875 59
1788547880 59
1788547885 59
1788547890 59
1788547895 59
1788547900 59
1788547905 59
1788547910 59
1788547915 59
1788547920 59
1788547925 64
1788547930 64
1788547935 64
1788547940 64
1788547945 64
1788547950 64
```
</details>

---

