---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 07:52:39 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 12 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 65-69 cores)</summary>

```
1787226541 65
1787226546 65
1787226551 65
1787226556 65
1787226561 65
1787226566 65
1787226571 65
1787226576 65
1787226581 65
1787226586 67
1787226591 67
1787226596 67
1787226601 67
1787226606 67
1787226611 67
1787226616 67
1787226621 69
1787226626 69
1787226631 69
1787226636 69
```
</details>

---

