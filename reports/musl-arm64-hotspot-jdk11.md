---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:23:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
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
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 49 |

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
1790093933 50
1790093938 50
1790093943 50
1790093948 50
```
</details>

---

