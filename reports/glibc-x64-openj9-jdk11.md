---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:58:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 78-83 cores)</summary>

```
1795431229 80
1795431234 80
1795431239 80
1795431244 80
1795431249 80
1795431254 80
1795431259 80
1795431264 78
1795431269 78
1795431274 78
1795431279 78
1795431284 78
1795431289 78
1795431294 78
1795431299 78
1795431304 78
1795431309 83
1795431314 83
1795431319 83
1795431324 83
```
</details>

---

