---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 12:20:41 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 11 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778516097 64
1778516102 64
1778516107 64
1778516112 64
1778516117 64
1778516122 64
1778516127 64
1778516132 64
1778516137 64
1778516142 64
1778516147 64
1778516152 64
1778516157 64
1778516162 64
1778516167 64
1778516172 64
1778516177 64
1778516182 64
1778516187 64
1778516192 64
```
</details>

---

