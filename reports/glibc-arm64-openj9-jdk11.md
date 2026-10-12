---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-12 04:31:33 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 11 |
| Allocations | 191 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 12 |
| Allocations | 153 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791793648 48
1791793653 48
1791793658 48
1791793663 48
1791793668 48
1791793673 48
1791793678 48
1791793683 48
1791793688 48
1791793693 48
1791793698 48
1791793703 43
1791793708 43
1791793713 43
1791793718 43
1791793723 43
1791793728 43
1791793733 43
1791793738 43
1791793743 43
```
</details>

---

