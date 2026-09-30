---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 11:36:51 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 83-87 cores)</summary>

```
1790782314 87
1790782319 87
1790782324 87
1790782329 87
1790782334 87
1790782339 87
1790782344 87
1790782349 87
1790782354 87
1790782359 87
1790782364 83
1790782369 83
1790782374 83
1790782379 83
1790782384 85
1790782389 85
1790782394 85
1790782399 85
1790782404 85
1790782409 85
```
</details>

---

