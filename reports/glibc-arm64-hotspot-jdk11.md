---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:32:52 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1790093853 49
1790093858 49
1790093863 49
1790093868 49
1790093873 49
1790093878 49
1790093883 49
1790093888 49
1790093893 49
1790093898 49
1790093903 49
1790093908 49
1790093914 49
1790093919 64
1790093924 64
1790093929 64
1790093934 64
1790093939 64
1790093944 64
1790093949 44
```
</details>

---

