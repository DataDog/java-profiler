---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 12:39:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 56-59 cores)</summary>

```
1793205317 56
1793205322 56
1793205327 56
1793205332 56
1793205337 56
1793205342 56
1793205347 56
1793205352 56
1793205357 57
1793205362 57
1793205367 57
1793205372 59
1793205377 59
1793205382 59
1793205387 59
1793205392 59
1793205397 59
1793205402 59
1793205407 59
1793205412 59
```
</details>

---

