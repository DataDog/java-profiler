---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 10:07:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 309 |
| Sample Rate | 5.15/sec |
| Health Score | 322% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795618901 64
1795618906 64
1795618911 64
1795618916 64
1795618921 64
1795618926 64
1795618931 64
1795618936 64
1795618941 64
1795618946 64
1795618951 64
1795618956 64
1795618961 64
1795618966 64
1795618971 47
1795618976 47
1795618981 47
1795618986 47
1795618991 47
1795618996 47
```
</details>

---

