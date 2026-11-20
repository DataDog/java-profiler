---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 09:53:26 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 14 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795186114 50
1795186119 50
1795186124 50
1795186129 50
1795186134 50
1795186139 50
1795186144 50
1795186149 50
1795186154 50
1795186159 50
1795186164 50
1795186169 50
1795186174 50
1795186179 50
1795186184 50
1795186189 50
1795186194 50
1795186199 50
1795186204 50
1795186209 50
```
</details>

---

