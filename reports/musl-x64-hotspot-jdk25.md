---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:23:36 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (4 unique values: 65-73 cores)</summary>

```
1795195149 73
1795195154 73
1795195159 73
1795195164 73
1795195169 73
1795195174 73
1795195179 73
1795195184 73
1795195189 73
1795195194 70
1795195199 70
1795195204 70
1795195209 70
1795195214 68
1795195219 68
1795195224 68
1795195229 70
1795195234 70
1795195239 70
1795195244 70
```
</details>

---

