---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 17:11:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 12 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 30-64 cores)</summary>

```
1793656889 30
1793656894 30
1793656899 30
1793656904 30
1793656909 30
1793656914 30
1793656919 30
1793656924 30
1793656929 30
1793656934 30
1793656939 30
1793656944 30
1793656949 30
1793656954 30
1793656959 30
1793656964 30
1793656969 30
1793656974 30
1793656979 30
1793656984 64
```
</details>

---

