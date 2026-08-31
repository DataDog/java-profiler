---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-30 21:25:12 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 12 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 63-83 cores)</summary>

```
1788139151 83
1788139156 83
1788139161 83
1788139166 83
1788139171 83
1788139176 83
1788139181 83
1788139186 83
1788139191 83
1788139196 83
1788139201 83
1788139206 83
1788139211 83
1788139216 83
1788139221 83
1788139226 83
1788139231 83
1788139236 63
1788139241 63
1788139246 63
```
</details>

---

