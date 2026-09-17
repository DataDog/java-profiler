---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:27:27 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 334 |
| Sample Rate | 5.57/sec |
| Health Score | 348% |
| Threads | 13 |
| Allocations | 162 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1789680071 23
1789680076 23
1789680081 23
1789680086 23
1789680091 23
1789680096 23
1789680101 23
1789680106 23
1789680111 23
1789680116 23
1789680121 23
1789680126 23
1789680131 23
1789680136 28
1789680141 28
1789680146 28
1789680151 28
1789680156 28
1789680161 28
1789680166 28
```
</details>

---

