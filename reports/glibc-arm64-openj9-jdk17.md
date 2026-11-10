---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 13:30:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1794334870 48
1794334875 48
1794334880 48
1794334885 48
1794334890 48
1794334895 48
1794334900 48
1794334905 48
1794334910 48
1794334915 48
1794334920 48
1794334925 48
1794334930 48
1794334935 48
1794334940 48
1794334945 48
1794334950 48
1794334955 48
1794334960 28
1794334965 28
```
</details>

---

