---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 07:40:05 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 14 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1794918838 29
1794918843 29
1794918848 24
1794918853 24
1794918858 24
1794918863 24
1794918868 24
1794918873 24
1794918878 24
1794918883 24
1794918888 29
1794918893 29
1794918898 29
1794918903 29
1794918908 29
1794918913 29
1794918918 34
1794918923 34
1794918928 34
1794918933 34
```
</details>

---

