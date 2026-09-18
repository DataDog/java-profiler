---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:50:55 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 17-35 cores)</summary>

```
1789731878 35
1789731884 35
1789731889 35
1789731894 35
1789731899 35
1789731904 35
1789731909 35
1789731914 35
1789731919 35
1789731924 35
1789731929 35
1789731934 35
1789731939 35
1789731944 35
1789731949 35
1789731954 35
1789731959 35
1789731964 35
1789731969 35
1789731974 35
```
</details>

---

