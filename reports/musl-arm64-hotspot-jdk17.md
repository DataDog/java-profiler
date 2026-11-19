---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 02:47:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1795074179 27
1795074184 27
1795074189 27
1795074194 27
1795074199 27
1795074204 27
1795074209 27
1795074214 27
1795074219 27
1795074224 27
1795074229 27
1795074234 27
1795074239 27
1795074244 27
1795074249 22
1795074254 22
1795074259 22
1795074264 22
1795074269 22
1795074274 22
```
</details>

---

