---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 10:10:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 49-53 cores)</summary>

```
1795446198 49
1795446203 49
1795446208 51
1795446213 51
1795446218 51
1795446223 51
1795446228 51
1795446233 51
1795446238 51
1795446243 51
1795446248 51
1795446253 51
1795446258 51
1795446263 51
1795446268 51
1795446273 51
1795446278 51
1795446283 51
1795446288 51
1795446293 51
```
</details>

---

