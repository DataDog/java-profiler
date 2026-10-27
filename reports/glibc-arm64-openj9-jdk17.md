---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 07:43:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 317 |
| Sample Rate | 5.28/sec |
| Health Score | 330% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1793101163 9
1793101168 9
1793101173 9
1793101178 9
1793101183 9
1793101188 9
1793101193 9
1793101198 9
1793101203 9
1793101208 9
1793101213 9
1793101218 9
1793101223 9
1793101228 9
1793101233 9
1793101238 9
1793101243 9
1793101248 9
1793101253 9
1793101258 9
```
</details>

---

