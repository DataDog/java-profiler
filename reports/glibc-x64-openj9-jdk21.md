---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-08 20:29:10 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 12 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 82-90 cores)</summary>

```
1794187507 82
1794187512 82
1794187517 82
1794187522 86
1794187527 86
1794187532 88
1794187537 88
1794187542 88
1794187547 88
1794187552 88
1794187557 88
1794187562 88
1794187567 88
1794187572 88
1794187577 88
1794187582 88
1794187587 88
1794187592 88
1794187597 88
1794187602 90
```
</details>

---

