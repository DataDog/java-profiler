---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-24 08:33:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 77-81 cores)</summary>

```
1777033663 81
1777033668 81
1777033673 81
1777033678 81
1777033683 81
1777033688 81
1777033693 81
1777033698 81
1777033703 81
1777033708 81
1777033713 81
1777033718 81
1777033723 81
1777033728 81
1777033733 81
1777033738 77
1777033743 77
1777033748 77
1777033753 77
1777033758 77
```
</details>

---

