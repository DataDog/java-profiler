---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:00:41 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1793721212 43
1793721217 43
1793721222 43
1793721227 43
1793721232 43
1793721237 43
1793721242 43
1793721247 42
1793721252 42
1793721257 42
1793721262 42
1793721267 42
1793721272 42
1793721277 42
1793721282 42
1793721287 42
1793721292 42
1793721297 42
1793721302 42
1793721307 42
```
</details>

---

