---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:03:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 860 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 89-93 cores)</summary>

```
1794567541 89
1794567546 89
1794567551 89
1794567556 89
1794567561 89
1794567566 89
1794567571 89
1794567576 89
1794567581 89
1794567586 89
1794567591 91
1794567596 91
1794567601 91
1794567606 91
1794567611 91
1794567616 93
1794567621 93
1794567626 93
1794567631 93
1794567636 93
```
</details>

---

