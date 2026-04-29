---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-29 11:49:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 52-55 cores)</summary>

```
1777477251 54
1777477256 54
1777477261 54
1777477266 54
1777477271 52
1777477276 52
1777477281 52
1777477286 52
1777477291 54
1777477296 54
1777477301 54
1777477306 54
1777477311 54
1777477317 54
1777477322 54
1777477327 54
1777477332 54
1777477337 54
1777477342 55
1777477347 55
```
</details>

---

