---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 09:35:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1792675550 84
1792675556 84
1792675561 84
1792675566 86
1792675571 86
1792675576 86
1792675581 86
1792675586 86
1792675591 86
1792675596 86
1792675601 86
1792675606 86
1792675611 86
1792675616 86
1792675621 84
1792675626 84
1792675631 84
1792675636 84
1792675641 84
1792675646 84
```
</details>

---

