---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 06:49:08 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794483909 38
1794483914 38
1794483919 38
1794483924 38
1794483929 38
1794483934 38
1794483939 38
1794483944 38
1794483949 43
1794483954 43
1794483959 43
1794483964 43
1794483969 43
1794483974 43
1794483979 43
1794483984 43
1794483989 43
1794483994 43
1794483999 43
1794484004 43
```
</details>

---

