---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-02 11:55:34 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 14-34 cores)</summary>

```
1788364273 24
1788364278 24
1788364283 24
1788364288 24
1788364293 24
1788364298 24
1788364303 24
1788364308 24
1788364313 24
1788364319 24
1788364324 24
1788364329 24
1788364334 24
1788364339 24
1788364344 24
1788364349 24
1788364354 14
1788364359 14
1788364364 14
1788364369 14
```
</details>

---

