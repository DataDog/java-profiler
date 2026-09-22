---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 13:14:48 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1790097021 64
1790097026 64
1790097031 64
1790097036 64
1790097041 64
1790097046 64
1790097051 64
1790097056 64
1790097061 64
1790097066 64
1790097071 64
1790097076 49
1790097081 49
1790097086 49
1790097091 49
1790097097 49
1790097102 49
1790097107 49
1790097112 49
1790097117 49
```
</details>

---

