---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 17:38:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 9 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 39-51 cores)</summary>

```
1793309687 39
1793309692 39
1793309697 39
1793309702 39
1793309707 39
1793309712 39
1793309717 39
1793309722 39
1793309727 51
1793309732 51
1793309737 51
1793309742 51
1793309747 51
1793309752 51
1793309757 51
1793309762 51
1793309767 46
1793309772 46
1793309777 46
1793309782 46
```
</details>

---

