---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 11:20:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 63-68 cores)</summary>

```
1795796192 63
1795796197 63
1795796202 63
1795796207 63
1795796212 63
1795796217 63
1795796222 63
1795796227 63
1795796232 63
1795796237 63
1795796242 63
1795796247 63
1795796252 63
1795796257 63
1795796262 68
1795796267 68
1795796272 68
1795796277 68
1795796282 68
1795796287 66
```
</details>

---

