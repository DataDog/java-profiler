---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:57:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 9 |
| Allocations | 178 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (5 unique values: 51-59 cores)</summary>

```
1795431226 51
1795431231 51
1795431236 51
1795431241 51
1795431246 51
1795431251 53
1795431256 53
1795431261 53
1795431266 53
1795431271 53
1795431276 53
1795431281 56
1795431286 56
1795431291 56
1795431296 58
1795431301 58
1795431306 58
1795431311 59
1795431316 59
1795431321 59
```
</details>

---

