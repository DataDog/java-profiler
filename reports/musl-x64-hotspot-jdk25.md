---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 12:34:16 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (4 unique values: 31-38 cores)</summary>

```
1794850157 33
1794850162 33
1794850167 33
1794850172 33
1794850177 33
1794850182 33
1794850187 33
1794850192 33
1794850197 31
1794850202 31
1794850207 31
1794850212 31
1794850217 31
1794850222 31
1794850227 31
1794850232 31
1794850237 36
1794850242 36
1794850247 38
1794850252 38
```
</details>

---

