---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-06 05:53:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 7 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 8 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1772794077 30
1772794082 30
1772794087 30
1772794092 30
1772794097 30
1772794102 30
1772794107 30
1772794112 30
1772794117 30
1772794122 32
1772794127 32
1772794132 32
1772794137 32
1772794142 27
1772794147 27
1772794152 27
1772794157 27
1772794162 27
1772794167 27
1772794172 27
```
</details>

---

