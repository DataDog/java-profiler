---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 04:49:17 EDT

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
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1792658597 43
1792658602 43
1792658607 43
1792658612 43
1792658617 43
1792658622 43
1792658627 43
1792658632 43
1792658637 43
1792658642 43
1792658647 43
1792658652 38
1792658657 38
1792658662 38
1792658667 38
1792658672 38
1792658677 38
1792658682 38
1792658687 38
1792658692 38
```
</details>

---

