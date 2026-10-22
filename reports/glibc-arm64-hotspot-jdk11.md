---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:00:04 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 13 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (3 unique values: 39-48 cores)</summary>

```
1792670104 39
1792670109 39
1792670114 39
1792670119 39
1792670124 39
1792670129 39
1792670134 39
1792670139 39
1792670144 39
1792670149 46
1792670154 46
1792670159 46
1792670164 46
1792670170 46
1792670175 46
1792670180 46
1792670185 46
1792670190 48
1792670195 48
1792670200 48
```
</details>

---

