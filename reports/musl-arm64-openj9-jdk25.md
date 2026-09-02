---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-02 11:55:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1788364255 46
1788364260 46
1788364265 46
1788364270 46
1788364275 46
1788364280 48
1788364285 48
1788364291 48
1788364296 48
1788364301 48
1788364306 48
1788364311 48
1788364316 43
1788364321 43
1788364326 43
1788364331 43
1788364336 43
1788364341 43
1788364346 43
1788364351 43
```
</details>

---

