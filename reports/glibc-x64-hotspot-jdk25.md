---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-01 07:50:41 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 39-53 cores)</summary>

```
1790855156 39
1790855161 39
1790855166 39
1790855171 39
1790855176 39
1790855181 39
1790855186 39
1790855191 45
1790855196 45
1790855201 45
1790855206 45
1790855211 45
1790855216 45
1790855221 45
1790855226 45
1790855231 53
1790855236 53
1790855241 53
1790855246 53
1790855251 53
```
</details>

---

