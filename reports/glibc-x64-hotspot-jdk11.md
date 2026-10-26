---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-25 21:27:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 82-96 cores)</summary>

```
1792977743 96
1792977748 96
1792977753 96
1792977758 96
1792977763 96
1792977768 96
1792977773 96
1792977778 96
1792977783 96
1792977788 96
1792977793 96
1792977798 96
1792977803 96
1792977808 96
1792977813 96
1792977818 96
1792977823 94
1792977828 94
1792977833 94
1792977838 94
```
</details>

---

