---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 08:33:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 341 |
| Sample Rate | 5.68/sec |
| Health Score | 355% |
| Threads | 12 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 27-39 cores)</summary>

```
1793017778 39
1793017783 39
1793017788 39
1793017793 39
1793017798 39
1793017803 39
1793017808 39
1793017813 39
1793017818 39
1793017823 39
1793017828 39
1793017833 39
1793017838 39
1793017843 39
1793017848 39
1793017853 39
1793017858 39
1793017863 39
1793017868 39
1793017873 39
```
</details>

---

