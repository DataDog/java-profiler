---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 07:19:37 EST

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
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795004137 64
1795004142 64
1795004147 64
1795004152 64
1795004157 64
1795004162 64
1795004167 64
1795004172 64
1795004177 64
1795004182 64
1795004187 64
1795004192 64
1795004197 64
1795004202 64
1795004207 64
1795004212 64
1795004217 64
1795004222 64
1795004227 64
1795004232 64
```
</details>

---

