---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 08:37:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 12 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 14 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795440863 64
1795440868 64
1795440873 64
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
1795440933 59
1795440938 59
1795440944 59
1795440949 59
1795440954 59
1795440959 59
```
</details>

---

