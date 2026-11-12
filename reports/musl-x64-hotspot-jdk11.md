---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:57:03 EST

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
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 9 |
| Allocations | 567 |

<details>
<summary>CPU Timeline (3 unique values: 26-32 cores)</summary>

```
1794509518 30
1794509523 30
1794509528 30
1794509533 30
1794509538 30
1794509543 30
1794509548 32
1794509553 32
1794509558 26
1794509563 26
1794509568 26
1794509573 26
1794509578 26
1794509583 26
1794509588 26
1794509593 26
1794509598 26
1794509603 26
1794509608 26
1794509613 26
```
</details>

---

