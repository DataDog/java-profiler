---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-23 05:47:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 11 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (4 unique values: 27-34 cores)</summary>

```
1787478200 34
1787478205 34
1787478210 34
1787478215 34
1787478220 34
1787478225 34
1787478230 34
1787478235 34
1787478240 34
1787478245 34
1787478250 34
1787478255 34
1787478260 34
1787478265 34
1787478270 34
1787478275 34
1787478280 34
1787478285 32
1787478290 32
1787478295 32
```
</details>

---

