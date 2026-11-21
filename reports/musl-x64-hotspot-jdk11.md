---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-21 00:02:15 EST

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 913 |
| Sample Rate | 15.22/sec |
| Health Score | 951% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 18-51 cores)</summary>

```
1795237094 18
1795237099 18
1795237104 18
1795237109 18
1795237114 18
1795237119 18
1795237124 18
1795237129 51
1795237134 51
1795237139 18
1795237144 18
1795237149 18
1795237154 18
1795237159 18
1795237164 18
1795237169 18
1795237174 18
1795237179 18
1795237184 18
1795237189 18
```
</details>

---

