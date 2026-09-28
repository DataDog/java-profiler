---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 09:39:40 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 213 |
| Sample Rate | 3.55/sec |
| Health Score | 222% |
| Threads | 10 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (5 unique values: 43-48 cores)</summary>

```
1790602540 43
1790602545 43
1790602550 43
1790602555 47
1790602560 47
1790602565 47
1790602570 47
1790602575 45
1790602580 45
1790602585 45
1790602590 45
1790602595 45
1790602600 45
1790602605 45
1790602610 45
1790602615 46
1790602620 46
1790602625 46
1790602630 46
1790602635 46
```
</details>

---

