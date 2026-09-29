---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 04:21:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 421 |
| Sample Rate | 7.02/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1790669761 88
1790669766 88
1790669771 88
1790669776 88
1790669781 88
1790669786 88
1790669791 88
1790669796 88
1790669801 88
1790669806 88
1790669811 88
1790669816 96
1790669821 96
1790669826 96
1790669831 96
1790669836 96
1790669841 96
1790669846 96
1790669851 96
1790669856 96
```
</details>

---

