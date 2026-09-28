---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 09:39:39 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 9 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790602531 46
1790602536 46
1790602541 46
1790602546 46
1790602551 46
1790602556 46
1790602561 46
1790602566 46
1790602571 46
1790602576 48
1790602581 48
1790602586 48
1790602591 48
1790602596 48
1790602601 48
1790602606 48
1790602612 48
1790602617 48
1790602622 48
1790602627 48
```
</details>

---

