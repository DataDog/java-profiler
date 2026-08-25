---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-25 11:03:29 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787669823 64
1787669828 64
1787669833 64
1787669838 64
1787669843 64
1787669848 64
1787669853 64
1787669858 64
1787669863 64
1787669868 64
1787669873 64
1787669878 64
1787669883 64
1787669888 64
1787669893 64
1787669898 64
1787669903 64
1787669908 64
1787669913 64
1787669918 64
```
</details>

---

