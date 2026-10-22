---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 09:57:29 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 8 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 27-29 cores)</summary>

```
1792677034 27
1792677039 27
1792677044 27
1792677049 27
1792677054 27
1792677059 27
1792677064 27
1792677069 27
1792677075 27
1792677080 29
1792677085 29
1792677090 29
1792677095 29
1792677100 29
1792677105 29
1792677110 29
1792677115 29
1792677120 29
1792677125 29
1792677130 29
```
</details>

---

