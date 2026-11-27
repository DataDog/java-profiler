---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 10:59:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 36 |
| Sample Rate | 0.60/sec |
| Health Score | 37% |
| Threads | 11 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (2 unique values: 21-33 cores)</summary>

```
1795794886 21
1795794891 21
1795794896 21
1795794901 21
1795794906 21
1795794911 21
1795794916 21
1795794921 21
1795794926 21
1795794931 21
1795794936 21
1795794941 21
1795794946 21
1795794951 21
1795794956 21
1795794961 21
1795794966 33
1795794971 33
1795794976 33
1795794981 33
```
</details>

---

