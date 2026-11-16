---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 21:12:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 10 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794794876 94
1794794881 94
1794794886 94
1794794891 94
1794794896 94
1794794901 96
1794794906 96
1794794911 96
1794794916 96
1794794921 96
1794794926 96
1794794931 96
1794794936 96
1794794941 96
1794794946 94
1794794951 94
1794794957 94
1794794962 94
1794794967 94
1794794972 94
```
</details>

---

