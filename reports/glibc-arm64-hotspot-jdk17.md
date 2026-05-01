---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-01 09:14:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 15 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777640938 64
1777640943 64
1777640948 64
1777640953 64
1777640958 64
1777640963 64
1777640968 64
1777640973 64
1777640978 64
1777640983 64
1777640988 59
1777640993 59
1777640998 59
1777641003 59
1777641008 59
1777641013 59
1777641018 59
1777641023 59
1777641028 59
1777641033 59
```
</details>

---

