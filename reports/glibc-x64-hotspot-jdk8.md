---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 09:35:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 164 |
| Sample Rate | 2.73/sec |
| Health Score | 171% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 75-96 cores)</summary>

```
1792675551 75
1792675556 75
1792675561 75
1792675566 96
1792675571 96
1792675576 96
1792675581 96
1792675586 96
1792675591 96
1792675596 96
1792675601 96
1792675606 96
1792675611 96
1792675616 96
1792675621 96
1792675626 96
1792675631 96
1792675636 96
1792675641 96
1792675646 96
```
</details>

---

