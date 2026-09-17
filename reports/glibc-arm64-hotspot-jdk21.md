---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 17:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 11 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789680081 43
1789680086 43
1789680091 43
1789680096 43
1789680101 43
1789680106 43
1789680111 43
1789680116 43
1789680121 43
1789680126 43
1789680131 43
1789680136 43
1789680141 43
1789680146 43
1789680151 48
1789680156 48
1789680161 48
1789680166 48
1789680171 48
1789680176 48
```
</details>

---

