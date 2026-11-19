---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 08:02:14 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795093146 50
1795093151 50
1795093156 50
1795093161 50
1795093166 50
1795093171 50
1795093176 50
1795093181 50
1795093186 50
1795093191 50
1795093196 50
1795093201 50
1795093206 50
1795093211 50
1795093216 50
1795093221 50
1795093226 50
1795093231 50
1795093236 50
1795093241 50
```
</details>

---

