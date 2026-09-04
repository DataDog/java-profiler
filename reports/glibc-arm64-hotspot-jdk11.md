---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-04 14:55:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
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
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 38-46 cores)</summary>

```
1788547859 43
1788547864 43
1788547869 43
1788547874 38
1788547879 38
1788547884 38
1788547889 38
1788547894 43
1788547899 43
1788547905 38
1788547910 38
1788547915 43
1788547920 43
1788547925 43
1788547930 43
1788547935 43
1788547940 43
1788547945 43
1788547950 46
1788547955 46
```
</details>

---

