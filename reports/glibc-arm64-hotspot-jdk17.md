---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 06:32:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 15 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 36-41 cores)</summary>

```
1794914934 38
1794914939 38
1794914944 38
1794914949 38
1794914954 38
1794914959 38
1794914964 38
1794914969 38
1794914974 38
1794914979 38
1794914984 38
1794914989 38
1794914994 38
1794914999 41
1794915004 41
1794915009 41
1794915014 41
1794915019 41
1794915024 41
1794915029 41
```
</details>

---

