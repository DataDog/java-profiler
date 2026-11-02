---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 17:11:44 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 14 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (1 unique values: 35-35 cores)</summary>

```
1793656956 35
1793656961 35
1793656966 35
1793656971 35
1793656976 35
1793656981 35
1793656986 35
1793656991 35
1793656996 35
1793657001 35
1793657006 35
1793657011 35
1793657016 35
1793657021 35
1793657027 35
1793657032 35
1793657037 35
1793657042 35
1793657047 35
1793657052 35
```
</details>

---

