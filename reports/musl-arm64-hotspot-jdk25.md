---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 08:02:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795093083 64
1795093088 64
1795093093 64
1795093098 64
1795093103 64
1795093108 64
1795093113 64
1795093118 64
1795093123 64
1795093128 64
1795093133 64
1795093138 64
1795093143 64
1795093148 64
1795093153 64
1795093158 64
1795093163 64
1795093168 64
1795093173 64
1795093178 64
```
</details>

---

