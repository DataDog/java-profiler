---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 12:28:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 869 |
| Sample Rate | 14.48/sec |
| Health Score | 905% |
| Threads | 12 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 65-84 cores)</summary>

```
1792772652 84
1792772657 84
1792772662 84
1792772667 84
1792772672 84
1792772677 84
1792772682 84
1792772687 84
1792772692 84
1792772697 84
1792772703 84
1792772708 84
1792772713 84
1792772718 65
1792772723 65
1792772728 65
1792772733 65
1792772738 65
1792772743 65
1792772748 65
```
</details>

---

