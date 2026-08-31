---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-30 21:22:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 323 |
| Sample Rate | 5.38/sec |
| Health Score | 336% |
| Threads | 10 |
| Allocations | 130 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 14 |
| Allocations | 89 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1788139087 29
1788139092 29
1788139097 29
1788139102 29
1788139107 29
1788139112 29
1788139117 29
1788139122 29
1788139127 29
1788139132 29
1788139137 29
1788139142 29
1788139147 29
1788139152 29
1788139157 29
1788139162 34
1788139167 34
1788139172 29
1788139177 29
1788139182 29
```
</details>

---

