---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-28 10:34:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 38 |

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
1790605883 64
1790605888 35
```
</details>

---

