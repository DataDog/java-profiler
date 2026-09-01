---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-01 05:49:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788255962 64
1788255967 64
1788255972 64
1788255977 64
1788255982 64
1788255987 64
1788255992 64
1788255997 64
1788256002 64
1788256007 64
1788256012 64
1788256017 64
1788256022 64
1788256027 64
1788256032 64
1788256037 64
1788256042 64
1788256047 64
1788256052 64
1788256057 64
```
</details>

---

