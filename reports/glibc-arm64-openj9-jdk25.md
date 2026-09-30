---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 07:31:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1790767667 40
1790767672 40
1790767678 40
1790767683 40
1790767688 40
1790767693 40
1790767698 40
1790767703 40
1790767708 40
1790767713 40
1790767718 40
1790767723 40
1790767728 40
1790767733 40
1790767738 40
1790767743 40
1790767748 40
1790767753 40
1790767758 40
1790767763 40
```
</details>

---

