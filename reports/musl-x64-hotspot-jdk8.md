---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 05:18:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 62-66 cores)</summary>

```
1795083184 64
1795083189 64
1795083194 62
1795083199 62
1795083204 62
1795083209 62
1795083214 65
1795083219 65
1795083224 65
1795083229 65
1795083234 65
1795083239 65
1795083244 65
1795083249 65
1795083254 65
1795083259 65
1795083264 65
1795083269 65
1795083274 65
1795083279 66
```
</details>

---

