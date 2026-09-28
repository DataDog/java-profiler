---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-28 10:34:15 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (4 unique values: 32-64 cores)</summary>

```
1790605793 63
1790605798 63
1790605803 63
1790605808 63
1790605813 63
1790605818 63
1790605823 63
1790605828 63
1790605833 63
1790605838 63
1790605843 63
1790605848 63
1790605853 63
1790605858 63
1790605863 63
1790605868 63
1790605873 64
1790605878 64
1790605883 35
1790605888 35
```
</details>

---

