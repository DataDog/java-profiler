---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-22 13:05:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 862 |
| Sample Rate | 14.37/sec |
| Health Score | 898% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1787418111 47
1787418116 47
1787418121 47
1787418126 47
1787418131 47
1787418136 47
1787418141 47
1787418146 49
1787418152 49
1787418157 49
1787418162 49
1787418167 51
1787418172 51
1787418177 51
1787418182 51
1787418187 51
1787418192 51
1787418197 51
1787418202 51
1787418207 51
```
</details>

---

