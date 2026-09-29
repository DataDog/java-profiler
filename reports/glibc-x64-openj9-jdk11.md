---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 11:52:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1086 |
| Sample Rate | 18.10/sec |
| Health Score | 1131% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1790696788 79
1790696793 79
1790696798 79
1790696803 79
1790696808 79
1790696813 79
1790696818 79
1790696823 79
1790696828 79
1790696833 79
1790696838 79
1790696843 79
1790696848 79
1790696853 81
1790696858 81
1790696863 81
1790696868 81
1790696873 81
1790696878 81
1790696883 81
```
</details>

---

