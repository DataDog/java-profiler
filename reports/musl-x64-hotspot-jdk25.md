---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 10:59:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (4 unique values: 69-80 cores)</summary>

```
1795794891 74
1795794896 74
1795794901 74
1795794906 71
1795794911 71
1795794916 71
1795794921 71
1795794926 71
1795794931 71
1795794936 71
1795794941 71
1795794946 69
1795794951 69
1795794956 69
1795794961 69
1795794966 69
1795794971 69
1795794976 69
1795794981 69
1795794986 69
```
</details>

---

