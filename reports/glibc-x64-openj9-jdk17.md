---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 09:39:41 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 300 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 61-96 cores)</summary>

```
1790602496 61
1790602501 61
1790602506 61
1790602511 63
1790602516 63
1790602521 63
1790602526 63
1790602531 63
1790602536 63
1790602541 63
1790602546 63
1790602551 63
1790602556 63
1790602561 63
1790602566 63
1790602571 96
1790602576 96
1790602581 85
1790602586 85
1790602591 85
```
</details>

---

