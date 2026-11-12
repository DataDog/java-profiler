---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 11:57:04 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 11 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 74-78 cores)</summary>

```
1794502086 76
1794502091 76
1794502096 76
1794502101 76
1794502106 78
1794502111 78
1794502116 78
1794502121 78
1794502126 76
1794502131 76
1794502136 76
1794502141 76
1794502146 76
1794502151 76
1794502156 76
1794502162 76
1794502167 76
1794502172 76
1794502177 76
1794502182 74
```
</details>

---

