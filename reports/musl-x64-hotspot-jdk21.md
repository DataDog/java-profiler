---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 12:41:40 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 54-66 cores)</summary>

```
1794331986 66
1794331991 66
1794331996 66
1794332001 66
1794332006 66
1794332011 66
1794332016 66
1794332021 64
1794332026 64
1794332031 64
1794332036 64
1794332041 64
1794332046 64
1794332051 64
1794332056 56
1794332061 56
1794332066 54
1794332071 54
1794332076 54
1794332081 54
```
</details>

---

