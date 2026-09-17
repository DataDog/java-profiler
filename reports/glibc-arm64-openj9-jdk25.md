---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 17:33:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 9 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 11 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1789680195 38
1789680200 43
1789680205 43
1789680210 43
1789680215 43
1789680220 45
1789680225 45
1789680230 43
1789680235 43
1789680240 43
1789680245 43
1789680250 43
1789680255 43
1789680260 43
1789680265 43
1789680270 43
1789680275 43
1789680280 43
1789680285 48
1789680290 48
```
</details>

---

