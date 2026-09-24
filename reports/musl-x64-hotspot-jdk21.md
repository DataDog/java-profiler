---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 05:34:56 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 42-67 cores)</summary>

```
1790242167 46
1790242172 46
1790242177 46
1790242182 46
1790242187 46
1790242192 46
1790242197 46
1790242202 67
1790242207 67
1790242212 67
1790242217 67
1790242222 45
1790242227 45
1790242232 45
1790242237 45
1790242242 45
1790242247 45
1790242252 45
1790242257 45
1790242262 45
```
</details>

---

