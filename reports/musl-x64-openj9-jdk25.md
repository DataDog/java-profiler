---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-13 12:15:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 11 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 13 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 45-51 cores)</summary>

```
1773418126 51
1773418131 51
1773418136 51
1773418141 51
1773418146 51
1773418151 47
1773418156 47
1773418161 47
1773418166 47
1773418171 47
1773418176 47
1773418181 47
1773418186 47
1773418191 47
1773418196 47
1773418201 47
1773418206 47
1773418211 47
1773418216 47
1773418221 47
```
</details>

---

