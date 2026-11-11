---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 12:40:21 EST

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 14 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 11-28 cores)</summary>

```
1794418592 11
1794418597 11
1794418602 11
1794418607 11
1794418612 11
1794418617 11
1794418622 11
1794418627 11
1794418632 11
1794418637 11
1794418643 11
1794418648 11
1794418653 11
1794418658 28
1794418663 28
1794418668 28
1794418673 28
1794418678 28
1794418683 28
1794418688 28
```
</details>

---

