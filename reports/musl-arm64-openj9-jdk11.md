---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:23:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 14 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790093853 50
1790093858 50
1790093863 50
1790093868 50
1790093873 50
1790093878 50
1790093883 50
1790093888 50
1790093893 50
1790093898 50
1790093903 50
1790093908 50
1790093913 50
1790093918 50
1790093923 50
1790093928 50
1790093934 50
1790093939 50
1790093944 50
1790093949 50
```
</details>

---

