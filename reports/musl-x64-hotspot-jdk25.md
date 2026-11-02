---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 11:04:43 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1793635103 86
1793635108 86
1793635113 86
1793635118 88
1793635123 88
1793635128 88
1793635133 88
1793635139 88
1793635144 88
1793635149 88
1793635154 88
1793635159 88
1793635164 88
1793635169 88
1793635174 88
1793635179 88
1793635184 88
1793635189 88
1793635194 88
1793635199 88
```
</details>

---

