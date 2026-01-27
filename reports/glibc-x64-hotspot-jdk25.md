---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-27 10:22:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 17.90/sec |
| Health Score | 1119% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 27.30/sec |
| Health Score | 1706% |
| Threads | 12 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1769526893 32
1769526898 32
1769526903 23
1769526908 23
1769526913 23
1769526918 23
1769526923 23
1769526928 23
1769526933 23
1769526938 23
1769526943 23
1769526948 23
1769526953 23
1769526958 23
1769526963 23
1769526968 23
1769526973 23
1769526978 23
1769526983 23
1769526988 23
```
</details>

---

