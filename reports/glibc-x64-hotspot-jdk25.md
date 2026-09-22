---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:32:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (5 unique values: 86-96 cores)</summary>

```
1790093848 93
1790093853 93
1790093858 93
1790093863 94
1790093868 94
1790093873 94
1790093878 94
1790093883 95
1790093888 95
1790093893 95
1790093898 95
1790093903 95
1790093908 95
1790093913 95
1790093918 95
1790093923 95
1790093928 95
1790093933 95
1790093938 96
1790093943 96
```
</details>

---

