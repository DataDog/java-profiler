---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 11:39:40 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 9 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 12 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795537853 48
1795537858 48
1795537863 48
1795537868 48
1795537873 48
1795537878 48
1795537883 48
1795537888 48
1795537893 48
1795537898 64
1795537903 64
1795537908 64
1795537913 64
1795537918 64
1795537924 64
1795537929 64
1795537934 64
1795537939 64
1795537944 64
1795537949 64
```
</details>

---

