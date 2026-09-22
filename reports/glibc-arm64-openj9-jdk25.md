---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:52:08 EDT

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (4 unique values: 7-10 cores)</summary>

```
1790091803 9
1790091808 9
1790091813 9
1790091818 9
1790091823 9
1790091828 10
1790091833 10
1790091838 10
1790091843 10
1790091848 10
1790091853 10
1790091858 10
1790091863 10
1790091868 9
1790091873 9
1790091878 9
1790091883 9
1790091888 7
1790091893 7
1790091898 7
```
</details>

---

