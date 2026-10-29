---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 16:31:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 27-38 cores)</summary>

```
1793305633 38
1793305638 38
1793305643 27
1793305648 27
1793305653 27
1793305658 27
1793305663 27
1793305668 27
1793305673 27
1793305678 27
1793305683 27
1793305688 27
1793305693 27
1793305698 27
1793305703 27
1793305708 27
1793305713 27
1793305718 27
1793305723 27
1793305728 27
```
</details>

---

