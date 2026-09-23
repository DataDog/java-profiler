---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 05:40:12 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (4 unique values: 40-47 cores)</summary>

```
1790156084 47
1790156089 46
1790156094 46
1790156099 46
1790156104 46
1790156109 46
1790156114 46
1790156119 46
1790156124 42
1790156129 42
1790156134 40
1790156139 40
1790156144 40
1790156149 40
1790156154 40
1790156159 40
1790156164 46
1790156169 46
1790156174 46
1790156179 46
```
</details>

---

