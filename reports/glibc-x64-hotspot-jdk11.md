---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 06:18:58 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 976 |
| Sample Rate | 16.27/sec |
| Health Score | 1017% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 68-73 cores)</summary>

```
1790244847 73
1790244852 73
1790244857 73
1790244862 73
1790244867 73
1790244873 73
1790244878 73
1790244883 73
1790244888 73
1790244893 71
1790244898 71
1790244903 71
1790244908 71
1790244913 71
1790244918 71
1790244923 71
1790244928 68
1790244933 68
1790244938 68
1790244943 68
```
</details>

---

