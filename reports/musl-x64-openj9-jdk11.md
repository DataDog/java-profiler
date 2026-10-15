---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-15 03:56:30 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 51-70 cores)</summary>

```
1792050678 51
1792050683 51
1792050688 51
1792050693 51
1792050698 53
1792050703 53
1792050708 53
1792050713 53
1792050718 53
1792050723 53
1792050728 53
1792050733 53
1792050738 53
1792050743 53
1792050748 70
1792050753 70
1792050758 70
1792050763 70
1792050768 53
1792050773 53
```
</details>

---

