---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 10:52:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 10 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 11 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790174759 50
1790174764 50
1790174769 50
1790174774 50
1790174780 50
1790174785 50
1790174790 50
1790174795 50
1790174800 50
1790174805 50
1790174810 50
1790174815 50
1790174820 50
1790174825 50
1790174830 50
1790174835 50
1790174840 50
1790174845 50
1790174850 50
1790174855 50
```
</details>

---

