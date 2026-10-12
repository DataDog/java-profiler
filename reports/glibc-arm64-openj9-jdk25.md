---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-12 03:26:24 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1791789782 36
1791789787 36
1791789792 36
1791789797 36
1791789802 36
1791789807 36
1791789812 36
1791789817 36
1791789822 36
1791789827 36
1791789832 36
1791789837 36
1791789842 36
1791789847 36
1791789852 36
1791789857 36
1791789862 36
1791789867 36
1791789872 36
1791789877 36
```
</details>

---

