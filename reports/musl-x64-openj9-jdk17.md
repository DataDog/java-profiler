---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 04:38:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 63-87 cores)</summary>

```
1786523592 67
1786523597 67
1786523602 87
1786523607 87
1786523612 87
1786523617 63
1786523622 63
1786523627 63
1786523632 63
1786523637 63
1786523642 63
1786523647 63
1786523652 63
1786523657 63
1786523662 63
1786523667 63
1786523672 63
1786523677 63
1786523682 63
1786523687 63
```
</details>

---

