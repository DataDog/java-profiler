---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 13:22:09 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 28-64 cores)</summary>

```
1795025907 28
1795025912 28
1795025917 28
1795025922 28
1795025927 28
1795025932 64
1795025937 64
1795025942 64
1795025947 64
1795025952 64
1795025957 64
1795025962 64
1795025967 64
1795025972 64
1795025977 64
1795025982 64
1795025987 64
1795025992 64
1795025997 64
1795026002 64
```
</details>

---

