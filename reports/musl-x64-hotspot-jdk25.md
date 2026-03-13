---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-13 12:15:37 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 11 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 13 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 31-49 cores)</summary>

```
1773418126 49
1773418131 44
1773418136 44
1773418141 44
1773418146 44
1773418151 31
1773418156 31
1773418161 31
1773418166 31
1773418171 31
1773418176 31
1773418181 31
1773418186 31
1773418191 31
1773418196 31
1773418201 31
1773418206 31
1773418211 31
1773418216 31
1773418221 31
```
</details>

---

