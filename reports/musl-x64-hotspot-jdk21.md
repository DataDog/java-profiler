---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 07:56:00 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 12 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 84-92 cores)</summary>

```
1794574164 92
1794574169 92
1794574174 92
1794574179 92
1794574184 90
1794574189 90
1794574194 90
1794574199 90
1794574204 90
1794574209 88
1794574214 88
1794574219 88
1794574224 84
1794574229 84
1794574234 84
1794574239 84
1794574244 84
1794574249 84
1794574254 86
1794574259 86
```
</details>

---

