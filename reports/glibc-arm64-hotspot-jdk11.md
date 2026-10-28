---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 06:30:16 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 13 |
| Allocations | 199 |

<details>
<summary>CPU Timeline (3 unique values: 46-53 cores)</summary>

```
1793183141 46
1793183146 46
1793183151 46
1793183156 46
1793183161 46
1793183166 46
1793183171 46
1793183176 46
1793183181 46
1793183186 46
1793183191 51
1793183196 51
1793183201 51
1793183206 51
1793183211 51
1793183216 51
1793183221 51
1793183226 51
1793183231 51
1793183236 51
```
</details>

---

