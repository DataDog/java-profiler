---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 12:33:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795022934 64
1795022939 64
1795022944 64
1795022949 64
1795022954 64
1795022959 64
1795022964 64
1795022969 64
1795022974 64
1795022979 64
1795022984 64
1795022989 64
1795022994 64
1795022999 64
1795023004 64
1795023009 64
1795023014 64
1795023019 64
1795023024 64
1795023029 64
```
</details>

---

