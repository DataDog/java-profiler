---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:44:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1794584412 46
1794584417 45
1794584422 45
1794584427 45
1794584432 45
1794584437 46
1794584442 46
1794584447 46
1794584452 46
1794584457 46
1794584462 46
1794584467 46
1794584472 46
1794584477 46
1794584482 46
1794584487 46
1794584492 46
1794584497 46
1794584502 46
1794584507 46
```
</details>

---

