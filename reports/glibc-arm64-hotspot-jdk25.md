---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 07:31:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (4 unique values: 29-33 cores)</summary>

```
1790767648 29
1790767653 29
1790767658 29
1790767663 29
1790767668 29
1790767673 29
1790767678 29
1790767683 29
1790767688 29
1790767693 29
1790767698 29
1790767703 29
1790767708 29
1790767713 29
1790767718 29
1790767723 29
1790767728 31
1790767733 31
1790767738 31
1790767743 31
```
</details>

---

