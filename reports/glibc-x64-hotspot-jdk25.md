---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-13 12:15:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 10 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 74-96 cores)</summary>

```
1773418127 75
1773418132 75
1773418137 96
1773418142 96
1773418147 96
1773418152 96
1773418157 79
1773418162 79
1773418167 79
1773418172 79
1773418177 79
1773418182 79
1773418187 79
1773418192 79
1773418197 79
1773418202 79
1773418207 79
1773418212 79
1773418217 74
1773418222 74
```
</details>

---

