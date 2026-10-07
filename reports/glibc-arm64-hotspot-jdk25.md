---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-07 11:19:19 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1791385863 36
1791385868 36
1791385873 36
1791385878 36
1791385883 36
1791385888 48
1791385893 48
1791385898 48
1791385903 48
1791385908 48
1791385913 48
1791385918 48
1791385923 48
1791385928 48
1791385933 48
1791385938 48
1791385943 48
1791385948 48
1791385953 48
1791385958 48
```
</details>

---

