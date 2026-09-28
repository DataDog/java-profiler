---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 14:12:54 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 13 |
| Allocations | 187 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790618941 38
1790618946 38
1790618951 38
1790618956 38
1790618961 38
1790618966 38
1790618971 38
1790618976 38
1790618981 38
1790618986 43
1790618991 43
1790618996 43
1790619001 43
1790619006 43
1790619011 43
1790619016 43
1790619021 43
1790619026 43
1790619031 43
1790619036 43
```
</details>

---

