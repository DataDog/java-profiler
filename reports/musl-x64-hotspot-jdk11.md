---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-14 11:42:13 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 79-84 cores)</summary>

```
1776180936 84
1776180941 84
1776180946 84
1776180951 82
1776180956 82
1776180961 82
1776180966 82
1776180971 84
1776180976 84
1776180981 84
1776180986 84
1776180991 84
1776180996 84
1776181001 79
1776181006 79
1776181011 79
1776181016 79
1776181021 79
1776181026 79
1776181032 79
```
</details>

---

