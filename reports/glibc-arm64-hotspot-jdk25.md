---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 05:40:09 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1790156135 48
1790156140 48
1790156145 48
1790156150 48
1790156155 45
1790156160 45
1790156165 45
1790156170 45
1790156175 45
1790156180 45
1790156185 45
1790156190 45
1790156195 45
1790156200 45
1790156205 45
1790156210 45
1790156215 40
1790156220 40
1790156225 40
1790156230 40
```
</details>

---

