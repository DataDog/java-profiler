---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 07:03:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 900 |
| Sample Rate | 15.00/sec |
| Health Score | 938% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 32-56 cores)</summary>

```
1790161156 56
1790161161 56
1790161166 32
1790161171 32
1790161176 32
1790161181 32
1790161186 32
1790161191 32
1790161196 32
1790161201 32
1790161206 32
1790161211 32
1790161216 32
1790161221 32
1790161226 32
1790161231 32
1790161236 32
1790161241 32
1790161246 32
1790161251 32
```
</details>

---

