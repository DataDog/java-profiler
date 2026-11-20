---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:23:35 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 588 |

<details>
<summary>CPU Timeline (6 unique values: 31-74 cores)</summary>

```
1795195141 44
1795195146 44
1795195151 44
1795195156 44
1795195161 44
1795195166 44
1795195171 72
1795195176 72
1795195181 72
1795195186 74
1795195191 74
1795195196 48
1795195201 48
1795195206 31
1795195211 31
1795195216 31
1795195221 31
1795195226 31
1795195231 31
1795195236 31
```
</details>

---

