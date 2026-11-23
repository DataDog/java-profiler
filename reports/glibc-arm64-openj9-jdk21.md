---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 08:37:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 12 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795440843 44
1795440848 44
1795440853 44
1795440858 44
1795440863 44
1795440868 44
1795440873 44
1795440878 64
1795440883 64
1795440888 64
1795440893 64
1795440898 64
1795440903 64
1795440908 64
1795440913 64
1795440918 64
1795440923 64
1795440928 64
1795440933 64
1795440938 64
```
</details>

---

