---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-11-20 11:32:45 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795192119 50
1795192124 50
1795192129 50
1795192134 50
1795192139 50
1795192144 50
1795192149 50
1795192154 50
1795192159 50
1795192164 50
1795192169 50
1795192174 50
1795192179 50
1795192184 50
1795192189 50
1795192194 50
1795192199 50
1795192204 50
1795192209 50
1795192214 50
```
</details>

---

