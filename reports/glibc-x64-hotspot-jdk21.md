---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 00:07:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (5 unique values: 30-56 cores)</summary>

```
1794546189 35
1794546194 35
1794546199 35
1794546204 35
1794546209 35
1794546214 35
1794546219 39
1794546224 39
1794546229 39
1794546234 39
1794546239 41
1794546244 41
1794546249 39
1794546254 39
1794546259 39
1794546264 39
1794546269 39
1794546274 39
1794546279 41
1794546284 41
```
</details>

---

