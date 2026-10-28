---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 12:39:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1793205317 11
1793205322 11
1793205327 11
1793205332 11
1793205337 11
1793205342 11
1793205347 11
1793205352 11
1793205357 11
1793205362 11
1793205367 11
1793205372 11
1793205377 11
1793205382 11
1793205387 11
1793205392 32
1793205397 32
1793205402 32
1793205407 32
1793205412 32
```
</details>

---

