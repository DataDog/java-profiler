---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 06:38:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791541838 32
1791541843 30
1791541848 30
1791541853 30
1791541858 30
1791541863 30
1791541868 30
1791541873 30
1791541878 30
1791541883 30
1791541888 30
1791541893 30
1791541898 30
1791541903 30
1791541908 30
1791541913 32
1791541918 32
1791541923 32
1791541928 32
1791541933 32
```
</details>

---

